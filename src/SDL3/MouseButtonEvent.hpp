#ifndef KOJO_SDL3_MOUSE_BUTTON_EVENT_HPP
#define KOJO_SDL3_MOUSE_BUTTON_EVENT_HPP

#include <SDL3/SDL_events.h>
#include <cstdint>

namespace sdl {

enum MouseButtonType : std::uint8_t {
	Left   = 1,
	Middle = 2,
	Right  = 3,
	X1     = 4,
	X2     = 5,
};

class MouseButtonEvent {
public:
	MouseButtonEvent(SDL_MouseButtonEvent _mouse_button_data)
		: mouse_button_data(_mouse_button_data) {}

	auto get_button_type() -> MouseButtonType
	{
		return static_cast<MouseButtonType>(mouse_button_data.button);
	}

private:
	SDL_MouseButtonEvent mouse_button_data;
};

}

#endif
