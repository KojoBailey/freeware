#include "game.hpp"

#include "../engine/rect_renderer.hpp"
#include "../engine/rect_transform.hpp"

#include <cmath>

void Game::start(GameEngine& engine) {
	apps.reserve(5);
	for (USz i = 0; i < 5; i++) {
		auto& app = apps.emplace_back(engine.createGameObject());

		auto& rectTransform = app.addComponent<RectTransform>();
		rectTransform.size = { .x = 70, .y = 70 };
		rectTransform.position = { .x = 100, .y = 70 + (F32)i * 120 };

		auto& rectRenderer = app.addComponent<RectRenderer>();
		rectRenderer.color = { .red = 200, .green = 50, .blue = 50 };
	}

	timeElapsed = 0.0;
}

void Game::update(F64 deltaTime) {
	timeElapsed += deltaTime;

	USz i = 0;
	for (auto& app : apps) {
		auto* rectRenderer = app.getComponent<RectRenderer>();
		if (rectRenderer == nullptr) {
			std::println(stderr, "nope");
			std::exit(1);
		}

		rectRenderer->positionOffset.y = static_cast<F32>(std::sin((timeElapsed + 100 * i) * 2.0) * 10.0);

		i++;
	}
}
