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
		return result;
	}

	auto get() -> SDL_Texture*
	{
		return handle.get();
	}
	
private:
	std::unique_ptr<SDL_Texture, decltype([](SDL_Texture* t) { SDL_DestroyTexture(t); })> handle;
};

}

#endif
