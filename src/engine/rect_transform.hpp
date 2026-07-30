#pragma once

#include "pch.hpp"

class RectTransform {
public:
	Vec2<F32> position;
	Vec2<F32> scale{ .x = 1.0, .y = 1.0 };
};
