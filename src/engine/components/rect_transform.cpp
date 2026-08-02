#include "rect_transform.hpp"

auto RectTransform::withSize(decltype(size) _size) -> RectTransform&
{
	size = _size;
	return *this;
}

auto RectTransform::withPosition(decltype(position) _position) -> RectTransform&
{
	position = _position;
	return *this;
}
