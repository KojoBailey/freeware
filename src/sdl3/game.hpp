#ifndef KOJO_SDL3_GAME_HPP
#define KOJO_SDL3_GAME_HPP

#include "renderer.hpp"
#include "rect.hpp"
#include "texture.hpp"

namespace sdl {

class Game {
public:
	static auto create(std::string_view title, const int _width, const int _height)
		-> std::expected<Game, std::string>
	{
		Game result;

		auto maybe_window = Window::create(title, _width, _height);
		if (!maybe_window.has_value()) {
			return std::unexpected{maybe_window.error()};
		}
		result.window = std::move(*maybe_window);

		auto maybe_renderer = Renderer::create(result.window);
		if (!maybe_renderer.has_value()) {
			return std::unexpected{maybe_renderer.error()};
		}
		result.renderer = std::move(*maybe_renderer);

		result.is_running = true;

		result.width = _width;
		result.height = _height;

		return result;
	}

	auto should_quit() -> bool
	{
		return !is_running;
	}

	void check_should_quit()
	{
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				is_running = false;
			}
		}
	}

	void set_draw_color(std::uint8_t red, std::uint8_t green, std::uint8_t blue)
	{
		renderer.set_draw_color(red, green, blue);
	}

	void clear()
	{
		renderer.clear();
	}

	void present()
	{
		renderer.present();
	}

	auto get_renderer() -> Renderer&
	{
		return renderer;
	}

	void render(Texture& texture, const Rect<float>& rect)
	{
		SDL_RenderTexture(renderer.get(), texture.get(), nullptr, (const SDL_FRect*)&rect);
	}

	auto get_width() -> int { return width; }
	auto get_height() -> int { return height; }

	auto get_width_float() -> float { return (float)width; }
	auto get_height_float() -> float { return (float)height; }

private:
	bool is_running;
	SDL_Event event;

	Window window;
	Renderer renderer;

	int width, height;
};

}

#endif
