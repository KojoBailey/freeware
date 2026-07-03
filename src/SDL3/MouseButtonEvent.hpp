#ifndef KOJO_SDL3_MOUSE_BUTTON_EVENT_HPP
#define KOJO_SDL3_MOUSE_BUTTON_EVENT_HPP

#include "Mouse.hpp"

#include <SDL3/SDL_events.h>
#include <cstdint>

namespace sdl {

class MouseButtonEvent {
public:
	MouseButtonEvent(SDL_MouseButtonEvent _mouseButtonData)
		: mouseButtonData(_mouseButtonData) {}

	auto getButtonType() -> MouseButtonType
	{
		return static_cast<MouseButtonType>(mouseButtonData.button);
	}

private:
	SDL_MouseButtonEvent mouseButtonData;
};

}

#endif
