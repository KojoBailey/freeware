#ifndef KOJO_SDL3_RECT_HPP
#define KOJO_SDL3_RECT_HPP

#include "Vec.hpp"

#include <SDL3/SDL_rect.h>

namespace sdl {

template<typename T>
struct Rect {
	Vec<T, 2> position{0, 0};
	Vec<T, 2> anchor{0, 0};
	Vec<T, 2> size;

	void anchorMiddle()
	{
		anchor.x = size.x / (T)2;
		anchor.y = size.y / (T)2;
	}

	[[nodiscard]] auto toSdlFRect() const -> SDL_FRect
	{
		return SDL_FRect{
			.x = position.x - anchor.x,
			.y = position.y - anchor.y,
			.w = size.x,
			.h = size.y,
		};
	}
};

}

#endif
