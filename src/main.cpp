#include "grid.hpp"

#include "SDL3/Init.hpp"
#include "SDL3/Window.hpp"
#include "SDL3/Renderer.hpp"
#include "SDL3/Event.hpp"
#include "SDL3/Clock.hpp"

#include <cmath>
#include <expected>
#include <iostream>
#include <print>
#include <unordered_map>
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

	std::unordered_map<std::string, Texture> texturePool;
	texturePool.insert({"desktop", unwrapOrExit(renderer.loadTexture("./assets/Windows_XP_Wallpaper.png"))});
	texturePool.insert({"app_vim", unwrapOrExit(renderer.loadTexture("./assets/Vim.png"))});

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

	Sprite appPreview{texturePool.at("app_vim"), {
		.size {
			.x = 70.0f,
			.y = 70.0f,
		},
	}};
	appPreview.anchorCenter();

	constexpr float appPadding = 40.0f;
	Vec<float, 2> appTarget;

	const float gridLength = appPreview.getSize().x + appPadding;
	Grid<8, 6> grid;
	grid.size = {
		.x = gridLength,
		.y = gridLength,
	};
	grid.position = {
		.x = desktopRect.position.x,
		.y = 0.0f,
	};

	Rect<float> selectionBox = {
		.size = grid.size * 0.9f,
	};
	selectionBox.anchorMiddle();

	std::vector<Sprite> apps;
	apps.reserve(grid.TILE_COUNT);

	Event event;
	bool isRunning = true;

	std::uint64_t timeSave = Clock::getTicksSinceStart();

	while (isRunning) {
		while (event.poll()) {
			switch (event.getType()) {
			case EventType::Quit:
				isRunning = false;
				break;
			case EventType::MouseButtonDown:
				if (event.getMouseButton().getButtonType() == MouseButtonType::Left) {
					if (grid.isTileFree(appTarget)) {
						Sprite app{texturePool.at("app_vim"),
							Rect<float>{
								.position = appTarget,
								.size {
									.x = 70.0f,
									.y = 70.0f,
								},
							}
						};
						app.anchorCenter();
						apps.push_back(app);
						grid.occupyTile(appTarget);
					}
				}
				break;
			default: break;
			}
		}

		renderer.clear();

		float deltaTime = (float)(Clock::getTicksSinceStart() - timeSave) / (float)Clock::getFrequency();
		timeSave = Clock::getTicksSinceStart();

		renderer.render(texturePool.at("desktop"), desktopRect);

		Vec<float, 2> mousePos = getMouseState().position;

		auto snapResult = grid.snap(mousePos);
		if (snapResult.has_value()) {
			appTarget = *snapResult + (grid.size / 2.0f);
		}
		appPreview.changePos(((appTarget - appPreview.getPos()) * 8.0f) * deltaTime);

		renderer.setDrawBlendMode(BlendMode::Blend);
		renderer.setDrawColor(255, 255, 255, 100);
		selectionBox.position = appTarget;

		for (Sprite& app : apps) {
			app.changeY(std::sin(app.getSecondsSinceBirth() * 4.0f) * deltaTime * 10.0f);
			renderer.render(app);
		}

		renderer.fillRect(selectionBox);
		renderer.render(appPreview);

		renderer.setDrawColor(0, 0, 0);
		renderer.present();
	}

	quit();

	return MainResult::Ok;
}
