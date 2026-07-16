#pragma once

#include "util.hpp"
#include "window.hpp"

#include <SDL3/SDL_render.h>

class Renderer {
public:
	[[nodiscard]] static auto create(
		Window& window, 
		const char* name = nullptr
	) -> std::expected<Renderer, std::string>;

private:
    UniquePtr<SDL_Renderer,
        decltype([](SDL_Renderer* r) { SDL_DestroyRenderer(r); } )
    > handle;
};