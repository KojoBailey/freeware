#pragma once

#include "../pch.hpp"

class RectRenderer {
public:
	Vec2<F32> scale{ .x = 1.0, .y = 1.0 };
	Vec2<F32> positionOffset{ .x = 0.0, .y = 0.0 };
	RGB color;

	auto withScale(decltype(scale) _scale) -> RectRenderer&;
	auto withPositionOffset(decltype(positionOffset) _positionOffset) -> RectRenderer&;
	auto withColor(decltype(color) _color) -> RectRenderer&;
};
