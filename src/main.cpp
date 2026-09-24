#include "game/game.hpp"

#define TRY_OR_ERR(x , err_msg)

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

	Result result = engine.run<FreeWare>();
	if (not result.has_value()) {
		std::println(stderr , "GameEngine runtime error:\n  {}" , result.error());
		return 1;
	}

	return 0;
}
