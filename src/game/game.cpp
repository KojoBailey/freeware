#include "game.hpp"

#include "../engine/components/rect_renderer.hpp"

auto Game::init(GameEngine& engine) -> Result<Nothing> {
	if (Result wallpaperResult = wallpaper.init(engine); not wallpaperResult.has_value()) {
		return Error{wallpaperResult.error()};
	}

	Result maybeGrid = decltype(grid)::create(engine);
	if (not maybeGrid.has_value()) {
		return Error{maybeGrid.error()};
	}
	grid = std::move(*maybeGrid);

	Result maybeVimTexture = engine.createTexture("assets/Vim.png");
	if (not maybeVimTexture.has_value()) {
		return Error{maybeVimTexture.error()};
	}
	vimTexture = std::make_shared<Texture>(std::move(*maybeVimTexture));

	appPreview = engine.createGameObject();
	appPreview.addComponent<RectTransform>()
		.withSize({ .x = 70.0f, .y = 70.0f });
	appPreview.addComponent<TextureRenderer>()
		.withTexture(vimTexture);

	firewall = engine.createGameObject();
	firewall.addComponent<RectTransform>()
		.withPosition({ .x = 160, .y = 0 })
		.withSize({ .x = 60.0f, .y = 720.0f });
	firewall.addComponent<RectRenderer>()
		.withColor({ .red = 255, .green = 150, .blue = 22 });

	bottomBar = engine.createGameObject();
	bottomBar.addComponent<RectTransform>()
		.withPosition({ .x = 160, .y = 690.0f })
		.withSize({ .x = 800.0f, .y = 30.0f });
	bottomBar.addComponent<RectRenderer>()
		.withColor({ .red = 32, .green = 89, .blue = 215 });

	timeElapsed = 0.0;

	return {};
}

auto Game::update(GameEngine& engine, F64 deltaTime) -> Result<Nothing> {
	timeElapsed += deltaTime;

	auto* appPreviewTransform = appPreview.getComponent<RectTransform>();
	assertValidPtr(appPreviewTransform);
	const Vec2 mousePosition = engine.getMousePosition();
	Vec2 tileIndex = grid.posToIndex(mousePosition);
	Maybe snappedPosition = grid.snapToTileCenter(mousePosition);
	if (snappedPosition.has_value()) {
		appPreviewTransform->position = *snappedPosition;
	} else {
		appPreviewTransform->position = mousePosition;
	}
	appPreviewTransform->position -= appPreviewTransform->size / 2.0f;

	if (engine.isMouseDown() and grid.isTileFree(tileIndex.x, tileIndex.y)) {
		Result maybeApp = App::create(engine, AppType::Vim, vimTexture);
		if (not maybeApp.has_value()) {
			return Error{maybeApp.error()};
		}
		App& app = apps.emplace_back(std::move(*maybeApp));
		app.setPosition(*grid.snapToTileCenter(tileIndex.x, tileIndex.y) - appPreview.getComponent<RectTransform>()->size / 2.0f);
		grid.occupyTile(tileIndex.x, tileIndex.y);
	}

	for (App& app : apps) {
		app.update(deltaTime);
	}

	return {};
}
