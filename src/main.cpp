#include "game.hpp"

#include <cmath>
#include <iostream>
#include <print>
#include <vector>

enum AppTerminationResult : int {
	Ok = 0,
	Error = 1,
};

template<typename T>
auto unwrap_or_exit(std::expected<T, std::string> maybe)
{
	if (not maybe.has_value()) {
		std::println(std::cerr, "[ERROR] {}", maybe.error());
		std::exit(AppTerminationResult::Error);
	}
	return std::move(*maybe);
}

template<typename T>
struct Vec2 { T x, y; };

int main()
{
	sdl::init();

	auto game = unwrap_or_exit(Game::create("Desktop Defence", 1280, 720));

	auto background = unwrap_or_exit(sdl::Texture::create(game.get_renderer(), "./assets/Windows_XP_Wallpaper.png"));
	constexpr float aspect_ratio = 4.0f / 3.0f;
	const float screen_height = game.get_height_float();
	const float background_width = screen_height * aspect_ratio;
	const sdl::Rect<float> background_rect = {
		.x = (game.get_width_float() - background_width) / 2.0f,
		.y = 0,
		.width = background_width,
		.height = screen_height
	};

	constexpr float app_size = 70.0f;
	constexpr float app_padding = 40.0f;
	auto app = unwrap_or_exit(sdl::Texture::create(game.get_renderer(), "./assets/Vim.png"));
	sdl::Rect<float> app_rect = {
		.width = app_size,
		.height = app_size
	};
	float app_target_x, app_target_y;

	constexpr float grid_size = app_size + app_padding;

	sdl::Rect<float> selection_box = {
		.width = grid_size,
		.height = grid_size
	};

	std::vector<Vec2<float>> apps;

	while (!game.should_quit()) {
		auto& event = game.event;
		while (SDL_PollEvent(&event)) {
			game.check_should_quit();

			if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
				if (event.button.button == SDL_BUTTON_LEFT) {
					apps.emplace_back(app_target_x, app_target_y);
				}
			}
		}

		game.clear();

		game.get_renderer().render(background, background_rect);

		float mouse_x, mouse_y;
		SDL_MouseButtonFlags buttons = SDL_GetMouseState(&mouse_x, &mouse_y);

		app_target_x = std::floor((mouse_x - (app_rect.width / 2.0f)) / grid_size) * grid_size;
		app_target_x += grid_size / 2.0f;
		app_target_y = std::floor((mouse_y - (app_rect.height / 2.0f)) / grid_size) * grid_size;
		app_target_y += grid_size / 2.0f;
		app_rect.x += (app_target_x - app_rect.x) / 300.0f;
		app_rect.y += (app_target_y - app_rect.y) / 300.0f;

		SDL_SetRenderDrawBlendMode(game.get_renderer().get(), SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(game.get_renderer().get(), 255, 255, 255, 100);
		selection_box.x = app_target_x - app_padding / 2.0f;
		selection_box.y = app_target_y - app_padding / 2.0f;

		for (auto& placed_app : apps) {
			auto placed_app_rect = app_rect;
			placed_app_rect.x = placed_app.x;
			placed_app_rect.y = placed_app.y;
			game.get_renderer().render(app, placed_app_rect);
		}

		SDL_RenderFillRect(game.get_renderer().get(), (const SDL_FRect*)&selection_box);
		game.get_renderer().render(app, app_rect);

		game.set_draw_color(0, 0, 0);
		game.present();
	}

	sdl::quit();

	return AppTerminationResult::Ok;
}
