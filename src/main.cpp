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

	auto maybe_texture = sdl::Texture::create(game.get_renderer(), "/home/kojo/Pictures/Gyro.jpg");
	if (!maybe_texture.has_value()) {
		std::println(std::cerr, "[ERROR] {}", maybe_texture.error());
		return AppTerminationResult::Error;
	}
	sdl::Texture texture = std::move(*maybe_texture);

	while (!game.should_quit()) {
		game.check_should_quit();

		game.set_draw_color(255, 255, 255);
		game.clear();

		texture.render();

		game.present();
	}

	sdl::quit();
}
