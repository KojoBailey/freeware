#ifndef KOJO_SDL3_TEXTURE_HPP
#define KOJO_SDL3_TEXTURE_HPP

#include <SDL3_image/SDL_image.h>

#include <filesystem>

namespace sdl {

class Renderer;

class Texture {
public:
	Texture(SDL_Texture* ptr) : handle{ptr} {}

	auto get() -> SDL_Texture*
	{
		return handle.get();
	}
	
private:
	std::unique_ptr<SDL_Texture, decltype([](SDL_Texture* t) { SDL_DestroyTexture(t); })> handle;
};

}

#endif
