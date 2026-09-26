#include "game/game.hpp"

auto main() -> CInt
{
	auto maybeEngine = GameEngine::create();
	if (not maybeEngine.has_value()) {
		std::println(stderr , "GameEngine create error:\n  {}" , maybeEngine.error());
		return 1;
	}
	GameEngine engine = std::move(*maybeEngine);

	if (Result result = engine.load(std::make_unique<FreeWare>()); not result.has_value()) {
		std::println(stderr , "GameEngine load error:\n  {}" , result.error());
		return 1;
	}
	if (Result result = engine.run(); not result.has_value()) {
		std::println(stderr , "GameEngine run error:\n  {}" , result.error());
		return 1;
	}

	return 0;
}
