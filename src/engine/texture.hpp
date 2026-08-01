#pragma once

#include "pch.hpp"
#include "renderer.hpp"

#include <SDL3_image/SDL_image.h>

class Texture {
	friend class GameEngine;

public:
	Texture() = default;

	auto get() const -> SDL_Texture*;
	
private:
	UniquePtr<SDL_Texture,
		decltype([](SDL_Texture* t) { SDL_DestroyTexture(t); })
	> handle;

	Texture(SDL_Texture* sdlTexture) : handle{sdlTexture} {}

	static auto create(Renderer& renderer, const FilePath& path) -> Result<Texture>;
};
