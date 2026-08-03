#pragma once

#include "pch.hpp"

class GameEngine;
class Renderer;

class IGame {
public:
	virtual ~IGame() = default;
	
	virtual auto init(GameEngine& engine) -> Result<Nothing> = 0;

    virtual auto update(GameEngine& engine, F64 deltaTime) -> Result<Nothing> = 0;
};
