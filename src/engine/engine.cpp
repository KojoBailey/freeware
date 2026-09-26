#include "engine.hpp"
#include "SDL3/SDL_mouse.h"
#include "engine/component_pool.hpp"
#include "game_object.hpp"

#include "components/rect_transform.hpp"
#include "components/rect_renderer.hpp"
#include "components/texture_renderer.hpp"

#include <SDL3/SDL_timer.h>

auto GameEngine::create() -> Result<GameEngine>
{
	SDL_InitSubSystem(SDL_INIT_AUDIO | SDL_INIT_VIDEO);

	return GameEngine{};
}

GameEngine::~GameEngine()
{
	SDL_Quit();
}

auto GameEngine::load(UniquePtr<IGame> game) -> Result<Nothing>
{
	this->window = TRY(Window::create(game->getTitle(), game->getWindowSize()));
	this->renderer = TRY(Renderer::create(this->window));	

	TRY(game->init(*this));
	this->game = std::move(game);

	return {};
}

auto GameEngine::processEvents() -> QuitStatus
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		this->_isLeftClickActive = false;

		switch (event.type) {
		case SDL_EVENT_QUIT:
			return QuitStatus::ShouldQuit;

		case SDL_EVENT_MOUSE_BUTTON_DOWN:
			if (event.button.button == SDL_BUTTON_LEFT) {
				this->_isLeftClickActive = true;
			}
			break;
		}
	}

	return QuitStatus::ShouldNotQuit;
}
	
auto GameEngine::run() -> Result<Nothing>
{
	U64 clockFrequency = SDL_GetPerformanceFrequency();
	U64 lastClock = SDL_GetPerformanceCounter();
	
	ComponentPool<RectTransform>&   rectTransforms   = this->getOrCreatePool<RectTransform>();
	ComponentPool<RectRenderer>&    rectRenderers    = this->getOrCreatePool<RectRenderer>();
	ComponentPool<TextureRenderer>& textureRenderers = this->getOrCreatePool<TextureRenderer>();

	while (true) {
		if (this->processEvents() == QuitStatus::ShouldQuit) break;

		U64 currentClock = SDL_GetPerformanceCounter();
		F64 deltaTime = (F64)(currentClock - lastClock) / (F64)clockFrequency;
		lastClock = currentClock;
		auto updateResult = this->game->update(*this, deltaTime);
		if (not updateResult.has_value()) {
			return Error(updateResult.error());
		}
		
		this->renderer.setDrawColor(0, 0, 0);
		this->renderer.clear();
		
		// TODO: Implement render order system.
		
		for (auto [handle, textureRenderer] : textureRenderers) {
			Maybe<Ref<RectTransform>> maybeRectTransform = rectTransforms.get(handle);
			if (not maybeRectTransform.has_value()) {
				return Error{"Tried to render TextureRenderer for GameObject without a RectTransform."};
			}
			RectTransform& rectTransform = std::move(*maybeRectTransform);
			SDL_FRect sdlFRect = {
				.x = rectTransform.position.x + textureRenderer.positionOffset.x,
				.y = rectTransform.position.y + textureRenderer.positionOffset.y,
				.w = rectTransform.size.x * textureRenderer.scale.x,
				.h = rectTransform.size.y * textureRenderer.scale.y,
			};
			SDL_RenderTexture(
				this->renderer.get(),
				textureRenderer.texture->get(),
				nullptr,
				&sdlFRect
			);
		}

		for (auto [handle, rectRenderer] : rectRenderers) {
			Maybe<Ref<RectTransform>> maybeRectTransform = rectTransforms.get(handle);
			if (not maybeRectTransform.has_value()) {
				return Error{"Tried to render RectRenderer for GameObject without a RectTransform."};
			}
			RectTransform& rectTransform = std::move(*maybeRectTransform);
			renderer.setDrawColor(rectRenderer.color);
			SDL_FRect sdlFRect = {
				.x = rectTransform.position.x + rectRenderer.positionOffset.x,
				.y = rectTransform.position.y + rectRenderer.positionOffset.y,
				.w = rectTransform.size.x * rectRenderer.scale.x,
				.h = rectTransform.size.y * rectRenderer.scale.y,
			};
			SDL_RenderFillRect(this->renderer.get() , &sdlFRect);
		}

		this->renderer.draw();
	}

	return {};
}

auto GameEngine::createGameObject() -> GameObject
{
	return GameObject{this, lastEntityIndex++};
}

auto GameEngine::registerGameObject() -> U32
{
	return lastEntityIndex++;
}

auto GameEngine::createTexture(const FilePath& path)
	-> Result<Texture> { return Texture::create(renderer, path); }

auto GameEngine::getMousePosition() -> Vec2<F32>
{
	Vec2<F32> mousePosition;
	auto _ = SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
	return mousePosition;
}

auto GameEngine::isLeftClickActive()
	-> Bool { return _isLeftClickActive; }
