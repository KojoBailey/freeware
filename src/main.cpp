#include "engine/engine.hpp"
#include "game/game.hpp"

auto main() -> CInt
{
	UNWRAP_OR_EXIT(GameEngine::initGame<Game>(
			"FreeWare",
			{ 1280, 720 }
	))
		.run();
	
	return 0;
}