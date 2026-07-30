#include "game/game.hpp"

auto main() -> CInt
{
	auto maybeEngine = GameEngine::initGame<Game>(
		"FreeWare",
		{ .x = 1280, .y = 720 }
	);
	if (not maybeEngine.has_value()) {
		std::println(stderr, "GameEngine initialisation error:\n\t{}", maybeEngine.error());
		return 1;
	}
	GameEngine engine = std::move(*maybeEngine);

	auto result = engine.run();
	if (not result.has_value()) {
		std::println(stderr, "GameEngine runtime error:\n\t{}", result.error());
		return 1;
	}

	return 0;
}
