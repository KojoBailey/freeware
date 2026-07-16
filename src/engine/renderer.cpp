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

auto Renderer::get() const -> SDL_Renderer*
{
	return handle.get();
}

void Renderer::setDrawColor(
	U8 red,
	U8 green,
	U8 blue,
	U8 alpha
)
{
	SDL_SetRenderDrawColor(handle.get(), red, green, blue, alpha);
}

void Renderer::clear()
{
	SDL_RenderClear(handle.get());
}

void Renderer::draw()
{
	SDL_RenderPresent(handle.get());
}