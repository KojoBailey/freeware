#pragma once

#include "util.hpp"

class GameEngine;
class Renderer;

class IGame {
public:
	virtual ~IGame() = default;
	
	virtual void start(GameEngine& engine) = 0;

    virtual void update(F32 deltaTime) = 0;
};