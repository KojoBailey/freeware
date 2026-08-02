#include "app.hpp"

#include "../engine/components/texture_renderer.hpp"
#include "../engine/components/rect_transform.hpp"

#include <cassert>
#include <cmath>

auto App::create(GameEngine& engine, AppType type, SharedPtr<Texture> texture) -> Result<App>
{
	App result;

	result.object = engine.createGameObject();

	auto& rectTransform = result.object.addComponent<RectTransform>()
		.withSize({ .x = 70, .y = 70 })
		.withPosition({ .x = 200, .y = 20 });

	auto& textureRenderer = result.object.addComponent<TextureRenderer>()
		.withTexture(texture);

	return result;
}

auto App::getType() const -> AppType
{
	return type;
}

void App::changeY(F32 offset)
{
	auto* rectTransform = object.getComponent<RectTransform>();
	assert(rectTransform != nullptr);
	rectTransform->position.y += offset;
}

void App::update(F64 deltaTime)
{
	auto* renderer = object.getComponent<TextureRenderer>();
	assert(renderer != nullptr);
	renderer->positionOffset.y = static_cast<F32>(std::sin((timeElapsed + 100) * 2.0) * 10.0);

	timeElapsed += deltaTime;
}
