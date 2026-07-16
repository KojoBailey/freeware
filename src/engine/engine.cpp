#include "engine.hpp"

void GameEngine::run()
{
	isRunning = true;
	
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
		
		renderer.clear();
		renderer.setDrawColor(200, 50, 50);
		renderer.draw();
	}

	SDL_Quit();
}