#pragma once

#include "engine/pch.hpp"

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

class ComponentChecklist {
public:
	static constexpr USz count = 3;

	template<typename TComponent>
	void tick()
	{
		bitset.set(ComponentIndex<TComponent>::value);
	}

	template<typename TComponent>
	void untick()
	{
		bitset.reset(ComponentIndex<TComponent>::value);
	}

	template<typename TComponent>
	auto isTicked() -> Bool
	{
		return bitset[ComponentIndex<TComponent>::value];
	}

private:
	Bitset<count> bitset{false};
};

