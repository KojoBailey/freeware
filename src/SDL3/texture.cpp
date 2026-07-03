#include "renderer.hpp"

using namespace sdl;

auto Texture::create(Renderer& _renderer, const std::filesystem::path& file)
	-> std::expected<Texture, std::string>
{
	Texture result;
	result.handle.reset(IMG_LoadTexture(_renderer.get(), file.c_str()));
	if (result.handle == nullptr) {
		return std::unexpected{SDL_GetError()};
	}
	return result;
}
