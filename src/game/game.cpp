#include "game.hpp"

#include "../engine/game_object.hpp"
#include "../engine/rect_renderer.hpp"
#include "../engine/rect_transform.hpp"

void Game::start(GameEngine& engine) {
	GameObject gameObject = engine.createGameObject();

	// auto& rectTransform = gameObject.addComponent<RectTransform>();
	// rectTransform.position = { .x = 100, .y = 100 };

	auto& rectRenderer = gameObject.addComponent<RectRenderer>();
	rectRenderer.size = { .x = 100, .y = 100 };
	rectRenderer.color = { .red = 200, .green = 50, .blue = 50 };
}

void Game::update(F32 deltaTime) {}
