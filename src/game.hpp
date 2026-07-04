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
		reset();
	}

	void reset()
	{
		sdl::init(InitFlag::Video);

		constexpr Vec<float, 2> WINDOW_SIZE { .x = 1280, .y = 720 };
		window = unwrapOrExit(Window::create("FreeWare", WINDOW_SIZE));
		renderer = unwrapOrExit(Renderer::create(window));

		texturePool.insert({"desktop", unwrapOrExit(renderer.loadTexture("./assets/Windows_XP_Wallpaper.png"))});
		texturePool.insert({"app_vim", unwrapOrExit(renderer.loadTexture("./assets/Vim.png"))});

		desktop = Desktop{WINDOW_SIZE, 4.0f / 3.0f};
		desktop.setTexture(&texturePool.at("desktop"));

		appPreview = Sprite{texturePool.at("app_vim"), { .size { .x = 70.0f, .y = 70.0f }}};
		appPreview.anchorCenter();

		Vec<float, 2> appTarget;

		const float gridLength = appPreview.getSize().x + APP_PADDING;
		grid.size = {
			.x = gridLength,
			.y = gridLength,
		};
		grid.position = {
			.x = desktop.getRect().position.x,
			.y = 0.0f,
		};
		apps.reserve(grid.TILE_COUNT);

		selectionBox = {
			.size = grid.size * 0.9f,
		};
		selectionBox.anchorMiddle();


		isRunning = true;

		timeSave = Clock::getTicksSinceStart();
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
		renderer.setDrawColor(255, 255, 255, 100);
		renderer.fillRect(selectionBox);

		renderer.render(appPreview);

		renderer.present();
	}

	void quit()
	{
		sdl::quit();
	}

private:
	static constexpr float APP_PADDING = 40.0f;

	Window window;
	Renderer renderer;
	Event event;

	Desktop desktop;
	Grid<8, 6> grid;
	std::vector<Sprite> apps;

	Vec<float, 2> appTarget;
	Sprite appPreview;
	Rect<float> selectionBox;

	bool isRunning;
	std::uint64_t timeSave;
	float deltaTime;

	std::unordered_map<std::string, Texture> texturePool;

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
	}
};

