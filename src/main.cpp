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
auto unwrapOrExit(std::expected<T, std::string> maybe) -> T
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

	constexpr Vec<float, 2> WINDOW_SIZE { .x = 1280, .y = 720 };
	auto window = unwrapOrExit(Window::create("FreeWare", WINDOW_SIZE));
	auto renderer = unwrapOrExit(Renderer::create(window));

	Texture desktop = unwrapOrExit(renderer.loadTexture("./assets/Windows_XP_Wallpaper.png"));
	constexpr float aspectRatio = 4.0f / 3.0f;
	const float desktopWidth = WINDOW_SIZE.y * aspectRatio;
	const Rect<float> desktopRect = {
		.position = {
			.x = (WINDOW_SIZE.x - desktopWidth) / 2.0f,
			.y = 0,
		},
		.size = {
			.x = desktopWidth,
			.y = WINDOW_SIZE.y,
		},
	};

	constexpr float appLength = 70.0f;
	constexpr float appPadding = 40.0f;
	Texture app = unwrapOrExit(renderer.loadTexture("./assets/Vim.png"));
	Rect<float> appRect = {
		.size {
			.x = appLength,
			.y = appLength,
		},
	};
	appRect.anchorMiddle();
	Vec<float, 2> appTarget;

	constexpr float gridLength = appLength + appPadding;

	Rect<float> selectionBox = {
		.size {
			.x = gridLength * 0.9f,
			.y = gridLength * 0.9f,
		},
	};
	selectionBox.anchorMiddle();

	std::vector<Vec<float, 2>> apps;

	Event event;
	bool isRunning = true;

	while (isRunning) {
		while (event.poll()) {
			switch (event.getType()) {
			case EventType::Quit:
				isRunning = false;
				break;
			case EventType::MouseButtonDown:
				if (event.getMouseButton().getButtonType() == MouseButtonType::Left) {
					apps.emplace_back(appTarget.x, appTarget.y);

				}
				break;
			default: break;
			}
		}

		renderer.clear();

		renderer.render(desktop, desktopRect);

		Vec<float, 2> mousePos = getMouseState().position;

		appTarget.x = std::floor(mousePos.x / gridLength) * gridLength;
		appTarget.x += gridLength / 2.0f;
		appTarget.y = std::floor(mousePos.y / gridLength) * gridLength;
		appTarget.y += gridLength / 2.0f;
		appRect.position.x += (appTarget.x - appRect.position.x) / 300.0f;
		appRect.position.y += (appTarget.y - appRect.position.y) / 300.0f;

		renderer.setDrawBlendMode(BlendMode::Blend);
		renderer.setDrawColor(255, 255, 255, 100);
		selectionBox.position.x = appTarget.x;
		selectionBox.position.y = appTarget.y;

		for (auto& placedApp : apps) {
			auto placedAppRect = appRect;
			placedAppRect.position.x = placedApp.x;
			placedAppRect.position.y = placedApp.y;
			renderer.render(app, placedAppRect);
		}

		renderer.fillRect(selectionBox);
		renderer.render(app, appRect);

		renderer.setDrawColor(0, 0, 0);
		renderer.present();
	}

	quit();

	return MainResult::Ok;
}
