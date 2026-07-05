#include "util.hpp"
#include "desktop.hpp"
#include "grid.hpp"

#include "SDL3/Init.hpp"
#include "SDL3/Window.hpp"
#include "SDL3/Renderer.hpp"
#include "SDL3/Event.hpp"
#include "SDL3/Clock.hpp"

#include <cmath>
#include <expected>
#include <unordered_map>
#include <vector>

using namespace sdl;

class Game {
public:
	Game()
	{
		init();
	}

	auto isFinished() -> bool
	{
		return not isRunning;
	}

	void update()
	{
		deltaTime = (float)(Clock::getTicksSinceStart() - timeSave) / (float)Clock::getFrequency();
		timeSave = Clock::getTicksSinceStart();

		handleEvents();

		const Vec<float, 2> mousePos = getMouseState().position;
		const auto snapResult = grid.snap(mousePos);
		if (snapResult.has_value()) {
			appTarget = *snapResult + (grid.size / 2.0f);
			shouldShowTarget = true;
		} else {
			appTarget = mousePos;
			shouldShowTarget = false;
		}
		appPreview.changePos(((appTarget - appPreview.getPos()) * 8.0f) * deltaTime);
		selectionBox.position = appTarget;

		for (Sprite& app : apps) {
			app.changeY(std::sin(app.getSecondsSinceBirth() * 4.0f) * deltaTime * 10.0f);
		}
	}

	void draw()
	{
		renderer.setDrawColor(0, 0, 0);
		renderer.clear();

		desktop.render(renderer);

		for (Sprite& app : apps) {
			renderer.render(app);
		}

		renderer.setDrawBlendMode(BlendMode::Blend);
		if (grid.isTileFree(appTarget)) {
			renderer.setDrawColor(255, 255, 255, 100);
		} else {
			renderer.setDrawColor(255, 60, 60, 100);
		}
		if (shouldShowTarget) {
			renderer.fillRect(selectionBox);
		}

		Rect<float> firewall = desktop.getRect();
		firewall.size.x = 60.0f;
		renderer.setDrawColor(255, 150, 22);
		renderer.fillRect(firewall);

		Rect<float> bottomBar = desktop.getRect();
		bottomBar.position.y = bottomBar.size.y - 30.0f;
		bottomBar.size.y = 30.0f;
		renderer.setDrawColor(32, 89, 215);
		renderer.fillRect(bottomBar);

		renderer.render(appPreview);

		renderer.present();
	}

	void quit()
	{
		sdl::quit();
	}

	void reset()
	{
		quit();
		init();
	}

private:
	static constexpr Vec<float, 2> APP_PADDING = {45.0f, 35.0f};

	Window window;
	Renderer renderer;
	Event event;

	Desktop desktop;
	Grid<8, 7> grid;
	std::vector<Sprite> apps;

	Vec<float, 2> appTarget;
	Sprite appPreview;
	Rect<float> selectionBox;
	bool shouldShowTarget;

	bool isRunning;
	std::uint64_t timeSave;
	float deltaTime;

	std::unordered_map<std::string, Texture> texturePool;

	void init()
	{
		sdl::init(InitFlag::Video);

		constexpr Vec<float, 2> WINDOW_SIZE { .x = 1280, .y = 720 };
		window = unwrapOrExit(Window::create("FreeWare", WINDOW_SIZE));
		renderer = unwrapOrExit(Renderer::create(window));

		texturePool.insert({"desktop", unwrapOrExit(renderer.loadTexture("./assets/Windows_XP_Wallpaper.png"))});
		texturePool.insert({"app_vim", unwrapOrExit(renderer.loadTexture("./assets/Vim.png"))});

		desktop = Desktop{WINDOW_SIZE, 4.0f / 3.0f};
		desktop.setTexture(&texturePool.at("desktop"));

		appPreview = Sprite{texturePool.at("app_vim"), { .size { .x = 55.0f, .y = 55.0f }}};
		appPreview.anchorCenter();

		Vec<float, 2> appTarget;

		grid.size = appPreview.getSize() + APP_PADDING;
		grid.position = {
			.x = desktop.getRect().position.x + 100.0f,
			.y = 0.0f,
		};
		apps.reserve(grid.TILE_COUNT);

		selectionBox = {
			.size = {
				.x = appPreview.getSize().x + APP_PADDING.y * 0.9f,
				.y = appPreview.getSize().x + APP_PADDING.y * 0.9f,
			}
		};
		selectionBox.anchorMiddle();

		timeSave = Clock::getTicksSinceStart();

		isRunning = true;
	}

	void handleEvents()
	{
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
									.x = 55.0f,
									.y = 55.0f,
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
	}
};

