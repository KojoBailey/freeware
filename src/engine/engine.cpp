#include "engine.hpp"
#include "game_object.hpp"

void GameEngine::run()
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
		
		for (RectRenderer& rectRenderer : rectRenderers) {
			renderer.setDrawColor(rectRenderer.color);
			SDL_FRect sdlFRect = {
				.x = 20,
				.y = 20,
				.w = rectRenderer.size.x,
				.h = rectRenderer.size.y,
			};
			SDL_RenderFillRect(renderer.get(), &sdlFRect);
		}

		renderer.draw();
	}

	SDL_Quit();
}

auto GameEngine::createGameObject() -> GameObject
{
	return GameObject{this};
}