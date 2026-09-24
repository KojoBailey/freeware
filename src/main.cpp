#include "game/game.hpp"

auto main() -> CInt
{
	auto maybeEngine = GameEngine::create({
		.title = "FreeWare",
		.windowSize = {.x = 1280, .y = 720},
	});
	if (not maybeEngine.has_value()) {
		std::println(stderr , "GameEngine initialisation error:\n  {}" , maybeEngine.error());
		return 1;
	}
	GameEngine engine = std::move(*maybeEngine);

	if (Result result = engine.run<FreeWare>(); not result.has_value()) {
		std::println(stderr , "GameEngine runtime error:\n  {}" , result.error());
		return 1;
	}

	return 0;
}
