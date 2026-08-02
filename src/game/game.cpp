#include "game.hpp"

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
		auto maybeApp = App::create(engine, AppType::Vim, vimTexture);
		if (not maybeApp.has_value()) {
			return Error{maybeApp.error()};
		}

		auto& app = apps.emplace_back(std::move(*maybeApp));
		app.changeY((F32)i * 120);
	}

	timeElapsed = 0.0;

	return {};
}

auto Game::update(F64 deltaTime) -> Result<Nothing> {
	timeElapsed += deltaTime;

	for (auto& app : apps) {
		app.update(deltaTime);
	}

	return {};
}
