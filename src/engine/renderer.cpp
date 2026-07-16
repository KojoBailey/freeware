#include "renderer.hpp"

auto Renderer::create(
	Window& window, 
	const char* name
) -> std::expected<Renderer, std::string>
{
	Renderer result;
	result.handle.reset(SDL_CreateRenderer(window.get(), name));
	if (result.handle == nullptr) {
		return std::unexpected{SDL_GetError()};
	}
	return result;
}