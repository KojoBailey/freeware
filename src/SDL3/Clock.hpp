#ifndef KOJO_SDL3_CLOCK_HPP
#define KOJO_SDL3_CLOCK_HPP

#include <SDL3/SDL_timer.h>

namespace sdl {

class Clock {
public:
	[[nodiscard]] static auto getTicksSinceStart() -> std::uint64_t
	{
		return SDL_GetPerformanceCounter();
	}

	[[nodiscard]] static auto getFrequency() -> std::uint64_t
	{
		return SDL_GetPerformanceFrequency();
	}

	Clock()
	{
		offset = getTicksSinceStart();
	}

	[[nodiscard]] auto getTicks() const -> std::uint64_t
	{
		return getTicksSinceStart() - offset;
	}

	[[nodiscard]] auto getSeconds() const -> float
	{
		return (float)getTicks() / (float)getFrequency();
	}

private:
	std::uint64_t offset;
};

}

#endif
