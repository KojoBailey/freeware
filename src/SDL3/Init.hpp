#ifndef KOJO_SDL3_SDL_HPP
#define KOJO_SDL3_SDL_HPP

#include <SDL3/SDL_init.h>

#include <cstdint>

namespace sdl {

enum class InitFlag : std::uint32_t {
	Audio    = 0x00000010, // Implies Events.
	Video    = 0x00000020, // Implies Events. Initialise on main thread.
	Joystick = 0x00000200, // Implies Events.
	Haptic   = 0x00001000,
	Gamepad  = 0x00002000, // Implies Joystick.
	Events   = 0x00004000,
	Sensor   = 0x00008000, // Implies Events.
	Camera   = 0x00010000, // Implies Events.
};

constexpr auto operator|(InitFlag lhs, InitFlag rhs) -> InitFlag
{
	return static_cast<InitFlag>(
		static_cast<std::uint32_t>(lhs) | static_cast<std::uint32_t>(rhs)
	);

}

constexpr auto operator|=(InitFlag& lhs, InitFlag rhs) -> InitFlag
{
	lhs = lhs | rhs;
	return lhs;
}

void init(InitFlag flags)
{
	SDL_Init(static_cast<SDL_InitFlags>(flags));
}

void quit()
{
	SDL_Quit();
}

}

#endif
