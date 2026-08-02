#include "background.hpp"

#include "../engine/game_object.hpp"
#include "../engine/components/rect_transform.hpp"
#include "../engine/components/texture_renderer.hpp"

auto Background::init(GameEngine& engine) -> Result<Nothing>
{
	auto maybeBackgroundTexture = engine.createTexture("assets/Windows_XP_Wallpaper.png");
	if (not maybeBackgroundTexture.has_value()) {
		return Error{maybeBackgroundTexture.error()};
	}
	GameObject background = engine.createGameObject();
	auto& backgroundTransform = background.addComponent<RectTransform>()
		.withSize({ .x = 960, .y = 720 })
		.withPosition({ .x = 160, .y = 0 });
	auto& backgroundRenderer = background.addComponent<TextureRenderer>()
		.withTexture(std::make_shared<Texture>(std::move(*maybeBackgroundTexture)));

	return {};
}
