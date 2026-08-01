#pragma once

#include "pch.hpp"

class GameEngine;
class Renderer;

class IGame {
public:
	virtual ~IGame() = default;
	
	virtual auto start(GameEngine& engine) -> Result<Nothing> = 0;

    virtual auto update(F64 deltaTime) -> Result<Nothing> = 0;
};
