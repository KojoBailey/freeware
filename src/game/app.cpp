#include "app.hpp"

#include "../engine/components/texture_renderer.hpp"
#include "../engine/components/rect_transform.hpp"

#include <cassert>
#include <cmath>

auto App::create(GameEngine& engine, AppType type, SharedPtr<Texture> texture) -> Result<App>
{
	App result;

	result.type = type;

	result.object = engine.createGameObject();

	result.object.addComponent<RectTransform>()
		.withSize({ .x = 70, .y = 70 });

	result.object.addComponent<TextureRenderer>()
		.withTexture(texture);

	return result;
}

auto App::getType() const -> AppType
{
	return type;
}

auto App::getSize() const -> Vec2<F32>
{
	auto* rectTransform = object.getComponent<RectTransform>();
	assert(rectTransform != nullptr);
	return rectTransform->size;
}

auto App::getPosition() const -> Vec2<F32>
{
	auto* rectTransform = object.getComponent<RectTransform>();
	assert(rectTransform != nullptr);
	return rectTransform->position;
}

void App::setPosition(Vec2<F32> position)
{
	auto* rectTransform = object.getComponent<RectTransform>();
	assert(rectTransform != nullptr);
	rectTransform->position = position;
}

void App::update(F64 deltaTime)
{
	auto* renderer = object.getComponent<TextureRenderer>();
	assert(renderer != nullptr);
	renderer->positionOffset.y = static_cast<F32>(std::sin((timeElapsed + 100) * 2.0) * 10.0);

	timeElapsed += deltaTime;
}
