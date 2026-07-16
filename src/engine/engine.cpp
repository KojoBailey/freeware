#include "engine.hpp"

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
		
		game->render(renderer);

		renderer.draw();
	}

	SDL_Quit();
}