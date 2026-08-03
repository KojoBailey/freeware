#pragma once

#include "rect_transform.hpp"
#include "rect_renderer.hpp"
#include "texture_renderer.hpp"

template<typename T>
struct ComponentIndex;

template<> struct ComponentIndex<RectTransform> {
	static constexpr USz value = 0;
};
template<> struct ComponentIndex<RectRenderer> {
	static constexpr USz value = 1;
};
template<> struct ComponentIndex<TextureRenderer> {
	static constexpr USz value = 2;
};

enum class ComponentType {
	RectTransform   = ComponentIndex<RectTransform>::value,
	RectRenderer    = ComponentIndex<RectRenderer>::value,
	TextureRenderer = ComponentIndex<TextureRenderer>::value,
};
