#include "game.hpp"

int main()
{
	Game game;

	while (not game.isFinished()) {
		game.update();
		game.draw();
	}

	game.quit();

	return MainResult::Ok;
}
