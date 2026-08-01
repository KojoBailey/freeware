#include "texture.hpp"

auto Texture::get() const -> SDL_Texture*
{
	return handle.get();
}

auto Texture::create(Renderer& renderer, const FilePath& path) -> Result<Texture>
{
	SDL_Texture* maybe_texture = IMG_LoadTexture(renderer.get(), path.c_str());
	if (maybe_texture == nullptr) {
		return std::unexpected{SDL_GetError()};
	}
	auto result = Texture{maybe_texture};
	return result;
}
