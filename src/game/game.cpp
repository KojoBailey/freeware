#include "game.hpp"

#include "../engine/components/rect_transform.hpp"
#include "../engine/components/texture_renderer.hpp"

#include <cmath>

auto Game::start(GameEngine& engine) -> Result<Nothing> {
	if (auto backgroundResult = background.init(engine); not backgroundResult.has_value()) {
		return Error{backgroundResult.error()};
	}

	auto maybeVimTexture = engine.createTexture("assets/Vim.png");
	if (not maybeVimTexture.has_value()) {
		return Error{maybeVimTexture.error()};
	}
	vimTexture = std::make_shared<Texture>(std::move(*maybeVimTexture));

	apps.reserve(5);
	for (USz i = 0; i < 5; i++) {
		auto& app = apps.emplace_back(engine.createGameObject());

		auto& rectTransform = app.addComponent<RectTransform>()
			.withSize({ .x = 70, .y = 70 })
			.withPosition({ .x = 200, .y = 20 + (F32)i * 120 });

		auto& textureRenderer = app.addComponent<TextureRenderer>()
			.withTexture(vimTexture);
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
