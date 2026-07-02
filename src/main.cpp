#include "sdl3/sdl.hpp"

#include <iostream>
#include <print>

enum AppTerminationResult : int {
	Ok = 0,
	Error = 1,
};

int main()
{
	sdl::init();

	auto maybe_game = sdl::Game::create("Desktop Defence", 1280, 720);
	if (!maybe_game.has_value()) {
		std::println(std::cerr, "[ERROR] {}", maybe_game.error());
		return AppTerminationResult::Error;
	}
	sdl::Game game = std::move(*maybe_game);

	auto maybe_texture = sdl::Texture::create(game.get_renderer(), "./assets/Windows_XP_Wallpaper.png");
	if (!maybe_texture.has_value()) {
		std::println(std::cerr, "[ERROR] {}", maybe_texture.error());
		return AppTerminationResult::Error;
	}
	sdl::Texture texture = std::move(*maybe_texture);

	constexpr float aspect_ratio = 4.0f / 3.0f;
	const float screen_height = game.get_height_float();
	const float background_width = screen_height * aspect_ratio;
	const sdl::Rect<float> rect = {
		.x = (game.get_width_float() - background_width) / 2.0f,
		.y = 0,
		.width = background_width,
		.height = screen_height
	};

	while (!game.should_quit()) {
		game.check_should_quit();

		// game.set_draw_color(255, 255, 255);
		game.clear();

		game.render(texture, rect);

		game.present();
	}

	sdl::quit();

	return AppTerminationResult::Ok;
}
