#pragma once

#include "../pch.hpp"

class RectTransform {
public:
	Vec2<F32> size;
	Vec2<F32> position;

	auto withSize(decltype(size) _size) -> RectTransform&;
	auto withPosition(decltype(position) _position) -> RectTransform&;
};
