#ifndef KOJO_FREEWARE_GAME_HPP
#define KOJO_FREEWARE_GAME_HPP

#include "sdl3/sdl.hpp"

class Game {
public:
	static auto create(std::string_view title, const int _width, const int _height)
		-> std::expected<Game, std::string>
	{
		Game result;

		auto maybe_window = sdl::Window::create(title, _width, _height);
		if (!maybe_window.has_value()) {
			return std::unexpected{maybe_window.error()};
		}
		result.window = std::move(*maybe_window);

		auto maybe_renderer = sdl::Renderer::create(result.window);
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

	auto get_renderer() -> sdl::Renderer&
	{
		return renderer;
	}

	auto get_width() -> int { return width; }
	auto get_height() -> int { return height; }

	auto get_width_float() -> float { return (float)width; }
	auto get_height_float() -> float { return (float)height; }

private:
	bool is_running;
	SDL_Event event;

	sdl::Window window;
	sdl::Renderer renderer;

	int width, height;
};

#endif
