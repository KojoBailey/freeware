#ifndef KOJO_SDL3_RENDERER_HPP
#define KOJO_SDL3_RENDERER_HPP

#include "Window.hpp"
#include "texture.hpp"
#include "rect.hpp"

#include <SDL3/SDL_render.h>

#include <cstdint>

namespace sdl {

constexpr std::uint8_t ALPHA_OPAQUE = 255;
constexpr std::uint8_t ALPHA_TRANSPARENT = 0;

class Renderer {
public:
	static auto create(Window& window, const char* name = nullptr)
		-> std::expected<Renderer, std::string>
	{
		Renderer result;
		result.handle.reset(SDL_CreateRenderer(window.get(), name));
		if (result.handle == nullptr) {
			return std::unexpected{SDL_GetError()};
		}
		return result;
	}

	auto get() -> SDL_Renderer*
	{
		return handle.get();
	}

	void setDrawColor(std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha = ALPHA_OPAQUE)
	{
		SDL_SetRenderDrawColor(handle.get(), red, green, blue, alpha);
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

	auto loadTexture(const std::filesystem::path& file)
		-> std::expected<Texture, std::string>
	{
		SDL_Texture* result = IMG_LoadTexture(handle.get(), file.c_str());
		if (result == nullptr) {
			return std::unexpected{SDL_GetError()};
		}
		return Texture{result};
	}

private:
	std::unique_ptr<SDL_Renderer, decltype([](SDL_Renderer* w) { SDL_DestroyRenderer(w); })> handle;
};

}

#endif
