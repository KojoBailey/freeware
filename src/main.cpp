#include "Game.hpp"

int main()
{
	while (not game.isFinished()) {
		game.update();
		game.draw();
	}

	game.quit();

	return MainResult::Ok;
}
