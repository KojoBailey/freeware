#include "SDL3/Init.hpp"
#include "SDL3/Window.hpp"
#include "SDL3/Renderer.hpp"
#include "SDL3/Event.hpp"

#include <cmath>
#include <expected>
#include <iostream>
#include <print>
#include <vector>

using namespace sdl;

enum MainResult : int {
	Ok = 0,
	Error = 1,
};

template<typename T>
auto unwrapOrExit(std::expected<T, std::string> maybe)
{
	if (not maybe.has_value()) {
		std::println(std::cerr, "[ERROR] {}", maybe.error());
		std::exit(MainResult::Error);
	}
	return std::move(*maybe);
}

int main()
{
	init(InitFlag::Video);

	constexpr Vec2<float> WINDOW_DIMENSIONS { .x = 1280, .y = 720 };
	auto window = unwrapOrExit(Window::create("FreeWare", WINDOW_DIMENSIONS));
	auto renderer = unwrapOrExit(Renderer::create(window));

	Texture desktop = unwrapOrExit(renderer.loadTexture("./assets/Windows_XP_Wallpaper.png"));
	constexpr float aspectRatio = 4.0f / 3.0f;
	const float desktopWidth = WINDOW_DIMENSIONS.y * aspectRatio;
	const Rect<float> desktopRect = {
		.x = (WINDOW_DIMENSIONS.x - desktopWidth) / 2.0f,
		.y = 0,
		.width = desktopWidth,
		.height = WINDOW_DIMENSIONS.y
	};

	constexpr float appLength = 70.0f;
	constexpr float appPadding = 40.0f;
	Texture app = unwrapOrExit(renderer.loadTexture("./assets/Vim.png"));
	Rect<float> appRect = {
		.width = appLength,
		.height = appLength
	};
	Vec2<float> appTarget;

	constexpr float gridLength = appLength + appPadding;

	Rect<float> selectionBox = {
		.width = gridLength,
		.height = gridLength
	};

	std::vector<Vec2<float>> apps;

	Event event;
	bool isRunning = true;

	while (isRunning) {
		while (event.poll()) {
			switch (event.get_type()) {
			case EventType::Quit:
				isRunning = false;
				break;
			case EventType::MouseButtonDown:
				if (event.get_mouse_button().get_button_type() == MouseButtonType::Left) {
					apps.emplace_back(appTarget.x, appTarget.y);
				}
				break;
			default: break;
			}
		}

		renderer.clear();

		renderer.render(desktop, desktopRect);

		float mouse_x, mouse_y;
		SDL_MouseButtonFlags buttons = SDL_GetMouseState(&mouse_x, &mouse_y);

		appTarget.x = std::floor((mouse_x - (appRect.width / 2.0f)) / gridLength) * gridLength;
		appTarget.x += gridLength / 2.0f;
		appTarget.y = std::floor((mouse_y - (appRect.height / 2.0f)) / gridLength) * gridLength;
		appTarget.y += gridLength / 2.0f;
		appRect.x += (appTarget.x - appRect.x) / 300.0f;
		appRect.y += (appTarget.y - appRect.y) / 300.0f;

		SDL_SetRenderDrawBlendMode(renderer.get(), SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(renderer.get(), 255, 255, 255, 100);
		selectionBox.x = appTarget.x - appPadding / 2.0f;
		selectionBox.y = appTarget.y - appPadding / 2.0f;

		for (auto& placedApp : apps) {
			auto placedAppRect = appRect;
			placedAppRect.x = placedApp.x;
			placedAppRect.y = placedApp.y;
			renderer.render(app, placedAppRect);
		}

		SDL_RenderFillRect(renderer.get(), (const SDL_FRect*)&selectionBox);
		renderer.render(app, appRect);

		renderer.setDrawColor(0, 0, 0);
		renderer.present();
	}

	quit();

	return MainResult::Ok;
}
