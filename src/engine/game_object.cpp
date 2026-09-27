#include "game_object.hpp"
#include "components/rect_transform.hpp"
#include "components/rect_renderer.hpp"
#include "components/texture_renderer.hpp"

// TODO: Refactor for code cleanness.

GameObject::GameObject(GameEngine* _engine, U32 index)
	: engine{_engine} 
{
	handle.key = index;
}

GameObject::GameObject(const GameObject& other)
	: engine{other.engine}
{
	handle = {
		.key = engine->registerGameObject(),
	};
	componentChecklist = other.componentChecklist;
	copyAllComponents(other);
}

auto GameObject::operator=(const GameObject& other) -> GameObject&
{
	if (this == &other) return *this;
	removeAllComponents();
	engine = other.engine;
	handle = {
		.key = engine->registerGameObject(),
	};
	componentChecklist = other.componentChecklist;
	copyAllComponents(other);
	return *this;
}

GameObject::GameObject(GameObject&& other) noexcept
	: engine{other.engine}
{
	handle = other.handle; // NOTE: This passes ownership of all components.
	componentChecklist = other.componentChecklist;
	other.handle.deregister();
}

auto GameObject::operator=(GameObject&& other) noexcept -> GameObject&
{
	if (this == &other) return *this;
	removeAllComponents();
	engine = other.engine;
	handle = other.handle; // NOTE: This passes ownership of all components.
	componentChecklist = other.componentChecklist;
	other.handle.deregister();
	return *this;
}

GameObject::~GameObject()
{
	removeAllComponents();
}

void GameObject::removeAllComponents()
{
	if (handle.key == 0) return;

	if (componentChecklist.isTicked<RectTransform>()) {
		removeComponent<RectTransform>();
	}
	if (componentChecklist.isTicked<RectRenderer>()) {
		removeComponent<RectRenderer>();
	}
	if (componentChecklist.isTicked<TextureRenderer>()) {
		removeComponent<TextureRenderer>();
	}
}

void GameObject::copyAllComponents(const GameObject& other)
{
	if (componentChecklist.isTicked<RectTransform>()) {
		copyComponent<RectTransform>(*other.getComponent<RectTransform>());
	}
	if (componentChecklist.isTicked<RectRenderer>()) {
		copyComponent<RectRenderer>(*other.getComponent<RectRenderer>());
	}
	if (componentChecklist.isTicked<TextureRenderer>()) {
		copyComponent<TextureRenderer>(*other.getComponent<TextureRenderer>());
	}
}
