#include "engine.hpp"
#include "game_object.hpp"
#include "rect_transform.hpp"
#include "rect_renderer.hpp"

#include <SDL3/SDL_timer.h>

auto GameEngine::run() -> Result<Nothing>
{
	isRunning = true;
	
	game->start(*this);

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
		game->update(deltaTime);
		
		renderer.setDrawColor(0, 0, 0);
		renderer.clear();
		
		auto& rectRenderers = getPool<RectRenderer>();
		auto& rectTransforms = getPool<RectTransform>();
		
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

		renderer.draw();
	}

	SDL_Quit();
	
	return {};
}

auto GameEngine::createGameObject() -> GameObject
{
	return GameObject{this, lastEntityIndex++};
}
