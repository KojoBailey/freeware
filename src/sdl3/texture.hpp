#ifndef KOJO_SDL3_TEXTURE_HPP
#define KOJO_SDL3_TEXTURE_HPP

#include "renderer.hpp"

#include <SDL3_image/SDL_image.h>

#include <filesystem>

namespace sdl {

class Texture {
public:
	static auto create(Renderer& _renderer, const std::filesystem::path& file)
		-> std::expected<Texture, std::string>
	{
		Texture result;
		result.handle.reset(IMG_LoadTexture(_renderer.get(), file.c_str()));
		if (result.handle == nullptr) {
			return std::unexpected{SDL_GetError()};
		}
		result.renderer = &_renderer;
		return result;
	}

	auto get() -> SDL_Texture*
	{
		return handle.get();
	}

	void render()
	{
		SDL_FRect rect = { 0, 0, 1280, 720 };
		SDL_RenderTexture(renderer->get(), handle.get(), nullptr, &rect);
	}
	
private:
	std::unique_ptr<SDL_Texture, decltype([](SDL_Texture* t) { SDL_DestroyTexture(t); })> handle;
	Renderer* renderer;
};

}

#endif
