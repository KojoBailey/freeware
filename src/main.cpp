#include "game.hpp"

#include <iostream>
#include <print>

enum AppTerminationResult : int {
	Ok = 0,
	Error = 1,
};

int main()
{
	sdl::init();

	auto maybe_game = Game::create("Desktop Defence", 1280, 720);
	if (!maybe_game.has_value()) {
		std::println(std::cerr, "[ERROR] {}", maybe_game.error());
		return AppTerminationResult::Error;
	}
	Game game = std::move(*maybe_game);

	auto maybe_background = sdl::Texture::create(game.get_renderer(), "./assets/Windows_XP_Wallpaper.png");
	if (!maybe_background.has_value()) {
		std::println(std::cerr, "[ERROR] {}", maybe_background.error());
		return AppTerminationResult::Error;
	}
	sdl::Texture background = std::move(*maybe_background);

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

		game.get_renderer().render(background, rect);

		game.present();
	}

	sdl::quit();

	return AppTerminationResult::Ok;
}
