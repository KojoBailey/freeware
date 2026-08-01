#pragma once

#include "../pch.hpp"
#include "../texture.hpp"

class TextureRenderer {
public:
	Vec2<F32> scale{ .x = 1.0, .y = 1.0 };
	Vec2<F32> positionOffset{ .x = 0.0, .y = 0.0 };
	SharedPtr<Texture> texture;
};
