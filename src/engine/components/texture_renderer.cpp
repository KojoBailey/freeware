#include "texture_renderer.hpp"

auto TextureRenderer::withScale(decltype(scale) _scale) -> TextureRenderer&
{
	scale = _scale;
	return *this;
}

auto TextureRenderer::withPositionOffset(decltype(positionOffset) _positionOffset) -> TextureRenderer&
{
	positionOffset = _positionOffset;
	return *this;
}

auto TextureRenderer::withTexture(decltype(texture) _texture) -> TextureRenderer&
{
	texture = _texture;
	return *this;
}
