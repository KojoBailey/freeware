#include "game.hpp"

auto Game::init(GameEngine& engine) -> Result<Nothing> {
	if (auto wallpaperResult = wallpaper.init(engine); not wallpaperResult.has_value()) {
		return Error{wallpaperResult.error()};
	}

	auto maybeVimTexture = engine.createTexture("assets/Vim.png");
	if (not maybeVimTexture.has_value()) {
		return Error{maybeVimTexture.error()};
	}
	vimTexture = std::make_shared<Texture>(std::move(*maybeVimTexture));

	auto maybeApp = App::create(engine, AppType::Vim, vimTexture);
	if (not maybeApp.has_value()) {
		return Error{maybeApp.error()};
	}
	auto appTemplate = std::move(*maybeApp);

	apps.reserve(5);
	for (USz i = 0; i < 5; i++) {
		auto& app = apps.emplace_back(appTemplate);
		app.changeY((F32)i * 120);
	}

	appPreview = appTemplate;

	timeElapsed = 0.0;

	return {};
}

auto Game::update(GameEngine& engine, F64 deltaTime) -> Result<Nothing> {
	timeElapsed += deltaTime;

	for (auto& app : apps) {
		app.update(deltaTime);
	}

	appPreview.setPosition(engine.getMousePosition());

	return {};
}
