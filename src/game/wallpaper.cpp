#include "wallpaper.hpp"

#include "../engine/components/rect_transform.hpp"
#include "../engine/components/texture_renderer.hpp"

auto Wallpaper::init(GameEngine& engine) -> Result<Nothing>
{
	auto maybeWallpaperTexture = engine.createTexture("assets/Windows_XP_Wallpaper.png");
	if (not maybeWallpaperTexture.has_value()) {
		return Error{maybeWallpaperTexture.error()};
	}
	wallpaper = engine.createGameObject();
	wallpaper.addComponent<RectTransform>()
		.withSize({ .x = 960, .y = 720 })
		.withPosition({ .x = 160, .y = 0 });
	wallpaper.addComponent<TextureRenderer>()
		.withTexture(std::make_shared<Texture>(std::move(*maybeWallpaperTexture)));

	return {};
}
