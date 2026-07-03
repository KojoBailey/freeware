#ifndef KOJO_SDL3_MOUSE_HPP
#define KOJO_SDL3_MOUSE_HPP

#include "Vec.hpp"

#include <SDL3/SDL_mouse.h>
#include <cstdint>
#include <vector>

namespace sdl {

enum class MouseButtonType : std::uint8_t {
	Left   = 1,
	Middle = 2,
	Right  = 3,
	X1     = 4,
	X2     = 5,
};

struct MouseState {
	Vec<float, 2> position;
	std::vector<MouseButtonType> pressed_types; // TODO
};

inline auto getMouseState() -> MouseState
{
	float x, y;
	SDL_MouseButtonFlags _ = SDL_GetMouseState(&x, &y);
	return MouseState{
		.position = {
			.x = x,
			.y = y,
		},
	};
}

}

#endif
