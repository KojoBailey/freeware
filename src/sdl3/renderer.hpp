#ifndef KOJO_SDL3_RENDERER_HPP
#define KOJO_SDL3_RENDERER_HPP

#include "window.hpp"
#include "texture.hpp"
#include "rect.hpp"

#include <cstdint>

namespace sdl {

class Renderer {
public:
	static auto create(Window& window)
		-> std::expected<Renderer, std::string>
	{
		Renderer result;
		result.handle.reset(SDL_CreateRenderer(window.get(), NULL));
		if (result.handle == nullptr) {
			return std::unexpected{SDL_GetError()};
		}
		return result;
	}

	auto get() -> SDL_Renderer*
	{
		return handle.get();
	}

	void set_draw_color(std::uint8_t red, std::uint8_t green, std::uint8_t blue)
	{
		SDL_SetRenderDrawColor(handle.get(), red, green, blue, 255);
	}

	void clear()
	{
		SDL_RenderClear(handle.get());
	}

	void present()
	{
		SDL_RenderPresent(handle.get());
	}

	void render(Texture& texture, const Rect<float>& rect)
	{
		SDL_RenderTexture(handle.get(), texture.get(), nullptr, (const SDL_FRect*)&rect);
	}
	
private:
	std::unique_ptr<SDL_Renderer, decltype([](SDL_Renderer* w) { SDL_DestroyRenderer(w); })> handle;
};

}

#endif
