#pragma once

#include "util.hpp"
#include "renderer.hpp"

class IGame {
public:
	virtual ~IGame() = 0;

    virtual void update(F32 deltaTime) = 0;

    virtual void render(Renderer& renderer) = 0;
};