#pragma once

#include "util.hpp"
#include "window.hpp"

#include <SDL3/SDL_render.h>

class Renderer {
public:
	RGB backgroundColor;

	[[nodiscard]] static auto create(
		Window& window, 
		const char* name = nullptr
	) -> std::expected<Renderer, std::string>;

	auto get() const -> SDL_Renderer*;

	void setDrawColor(
		U8 red,
		U8 green,
		U8 blue,
		U8 alpha = SDL_ALPHA_OPAQUE
	);
	void setDrawColor(RGB rgb);

	void clear();

	void draw();

private:
    UniquePtr<SDL_Renderer,
        decltype([](SDL_Renderer* r) { SDL_DestroyRenderer(r); } )
    > handle;
};