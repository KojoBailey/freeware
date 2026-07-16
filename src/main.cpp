// #include "game.hpp"

#include "engine/engine.hpp"

auto main() -> CInt
{
	auto engine = UNWRAP_OR_EXIT(GameEngine::init(
			"FreeWare",
			{ 1280, 720 }
	));

	engine.run();
	
	return 0;
}