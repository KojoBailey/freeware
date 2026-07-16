#pragma once

#include "util.hpp"

#include <SDL3/SDL_error.h>
#include <SDL3/SDL_video.h>

class Window {
public:
	static auto create(
		std::string_view title,
		const Vec2<F32> size
	) -> Result<Window>;
    
	auto get() const -> SDL_Window*;

private:
	UniquePtr<SDL_Window,
		decltype([](SDL_Window* w) { SDL_DestroyWindow(w); } )
	> handle;
};