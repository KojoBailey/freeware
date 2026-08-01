#include "game.hpp"

#include "../engine/components/rect_renderer.hpp"
#include "../engine/components/rect_transform.hpp"
#include "../engine/components/texture_renderer.hpp"

#include <cmath>

auto Game::start(GameEngine& engine) -> Result<Nothing> {
	auto maybeVimTexture = engine.createTexture("assets/Vim.png");
	if (not maybeVimTexture.has_value()) {
		return Error{maybeVimTexture.error()};
	}
	vimTexture = std::make_shared<Texture>(std::move(*maybeVimTexture));

	auto maybeBackgroundTexture = engine.createTexture("assets/Windows_XP_Wallpaper.png");
	if (not maybeBackgroundTexture.has_value()) {
		return Error{maybeVimTexture.error()};
	}
	background = engine.createGameObject();
	auto& backgroundTransform = background.addComponent<RectTransform>();
	backgroundTransform.size = { .x = 960, .y = 720 };
	backgroundTransform.position = { .x = 160, .y = 0 };
	auto& backgroundRenderer = background.addComponent<TextureRenderer>();
	backgroundRenderer.texture = std::make_shared<Texture>(std::move(*maybeBackgroundTexture));

	apps.reserve(5);
	for (USz i = 0; i < 5; i++) {
		auto& app = apps.emplace_back(engine.createGameObject());

		auto& rectTransform = app.addComponent<RectTransform>();
		rectTransform.size = { .x = 70, .y = 70 };
		rectTransform.position = { .x = 200, .y = 20 + (F32)i * 120 };

		auto& textureRenderer = app.addComponent<TextureRenderer>();
		textureRenderer.texture = vimTexture;
	}

	timeElapsed = 0.0;

	return {};
}

auto Game::update(F64 deltaTime) -> Result<Nothing> {
	timeElapsed += deltaTime;

	USz i = 0;
	for (auto& app : apps) {
		auto* renderer = app.getComponent<TextureRenderer>();
		if (renderer == nullptr) {
			return Error{"Could not find TextureRenderer component in app."};
		}

		renderer->positionOffset.y = static_cast<F32>(std::sin((timeElapsed + 100 * i) * 2.0) * 10.0);

		i++;
	}

	return {};
}
