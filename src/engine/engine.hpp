#pragma once

#include "util.hpp"
#include "i_game.hpp"
#include "renderer.hpp"

class GameEngine {
public:
	static auto init(
		StringView name,
		Vec2<U32> windowSize
	) -> Result<GameEngine>;
	
	void run();
	
private:
	UniquePtr<IGame> game;
	Window window;
    Renderer renderer;
};
