#include "rect_renderer.hpp"

auto RectRenderer::withScale(decltype(scale) _scale) -> RectRenderer&
{
	scale = _scale;
	return *this;
}

auto RectRenderer::withPositionOffset(decltype(positionOffset) _positionOffset) -> RectRenderer&
{
	positionOffset = _positionOffset;
	return *this;
}

auto RectRenderer::withColor(decltype(color) _color) -> RectRenderer&
{
	color = _color;
	return *this;
}
