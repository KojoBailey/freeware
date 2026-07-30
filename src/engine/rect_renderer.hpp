#pragma once

#include "pch.hpp"

class RectRenderer {
public:
	Vec2<F32> scale{ .x = 1.0, .y = 1.0 };
	Vec2<F32> positionOffset;
	RGB color;
};
