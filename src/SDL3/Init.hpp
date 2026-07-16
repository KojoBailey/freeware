#pragma once

#include <SDL3/SDL_init.h>

#include <concepts>
#include <cstdint>

namespace sdl {

enum class ESubSystem : std::uint32_t {
	Audio    = 0x00000010, // Implies Events.
	Video    = 0x00000020, // Implies Events. Initialise on main thread.
	Joystick = 0x00000200, // Implies Events.
	Haptic   = 0x00001000,
	Gamepad  = 0x00002000, // Implies Joystick.
	Events   = 0x00004000,
	Sensor   = 0x00008000, // Implies Events.
	Camera   = 0x00010000, // Implies Events.
};

constexpr auto operator|(ESubSystem lhs, ESubSystem rhs) -> ESubSystem
{
	return static_cast<ESubSystem>(
		static_cast<std::uint32_t>(lhs) | static_cast<std::uint32_t>(rhs)
	);

}

constexpr auto operator|=(ESubSystem& lhs, ESubSystem rhs) -> ESubSystem
{
	lhs = lhs | rhs;
	return lhs;
}

template<std::same_as<ESubSystem>... Args>
void init(Args... flags)
{
	ESubSystem ored = (flags | ...);
	SDL_InitSubSystem(static_cast<SDL_InitFlags>(ored));
}

void quit()
{
	SDL_Quit();
}

}
