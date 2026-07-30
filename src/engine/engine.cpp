#include "engine.hpp"
#include "game_object.hpp"
#include "rect_transform.hpp"
#include "rect_renderer.hpp"

auto GameEngine::run() -> Result<Nothing>
{
	isRunning = true;
	
	game->start(*this);
	
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
				.x = rectTransform->position.x,
				.y = rectTransform->position.y,
				.w = rectRenderer.size.x,
				.h = rectRenderer.size.y,
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
	return GameObject{this};
}
