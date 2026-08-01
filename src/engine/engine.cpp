#include "engine.hpp"
#include "game_object.hpp"
#include "components/rect_transform.hpp"
#include "components/rect_renderer.hpp"
#include "components/texture_renderer.hpp"

#include <SDL3/SDL_timer.h>

auto GameEngine::run() -> Result<Nothing>
{
	isRunning = true;
	
	auto startResult = game->start(*this);
	if (not startResult.has_value()) {
		return Error(startResult.error());
	}

	U64 clockFrequency = SDL_GetPerformanceFrequency();
	U64 lastClock = SDL_GetPerformanceCounter();
	
	while (isRunning) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_EVENT_QUIT:
				isRunning = false;
				break;
			default: break;
			}
		}

		U64 currentClock = SDL_GetPerformanceCounter();
		F64 deltaTime = (F64)(currentClock - lastClock) / (F64)clockFrequency;
		lastClock = currentClock;
		auto updateResult = game->update(deltaTime);
		if (not updateResult.has_value()) {
			return Error(updateResult.error());
		}
		
		renderer.setDrawColor(0, 0, 0);
		renderer.clear();
		
		auto& rectTransforms = getPool<RectTransform>();
		auto& rectRenderers = getPool<RectRenderer>();
		auto& textureRenderers = getPool<TextureRenderer>();
		
		for (auto [handle, rectRenderer] : rectRenderers.toIter()) {
			RectTransform* rectTransform = rectTransforms.get(handle);
			if (rectTransform == nullptr) {
				return Error("Tried to render RectRenderer for GameObject without a RectTransform.");
			}
			renderer.setDrawColor(rectRenderer.color);
			SDL_FRect sdlFRect = {
				.x = rectTransform->position.x + rectRenderer.positionOffset.x,
				.y = rectTransform->position.y + rectRenderer.positionOffset.y,
				.w = rectTransform->size.x * rectRenderer.scale.x,
				.h = rectTransform->size.y * rectRenderer.scale.y,
			};
			SDL_RenderFillRect(renderer.get(), &sdlFRect);
		}

		for (auto [handle, textureRenderer] : textureRenderers.toIter()) {
			RectTransform* rectTransform = rectTransforms.get(handle);
			if (rectTransform == nullptr) {
				return Error("Tried to render TextureRenderer for GameObject without a RectTransform.");
			}
			SDL_FRect sdlFRect = {
				.x = rectTransform->position.x + textureRenderer.positionOffset.x,
				.y = rectTransform->position.y + textureRenderer.positionOffset.y,
				.w = rectTransform->size.x * textureRenderer.scale.x,
				.h = rectTransform->size.y * textureRenderer.scale.y,
			};
			SDL_RenderTexture(renderer.get(), textureRenderer.texture->get(), nullptr, &sdlFRect);
		}

		renderer.draw();
	}

	SDL_Quit();
	
	return {};
}

auto GameEngine::createGameObject() -> GameObject
{
	return GameObject{this, lastEntityIndex++};
}

auto GameEngine::createTexture(const FilePath& path) -> Result<Texture>
{
	return Texture::create(renderer, path);
}
