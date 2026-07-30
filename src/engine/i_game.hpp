#pragma once

#include "pch.hpp"

class GameEngine;
class Renderer;

class IGame {
public:
	virtual ~IGame() = default;
	
	virtual void start(GameEngine& engine) = 0;

    virtual void update(F64 deltaTime) = 0;
};
