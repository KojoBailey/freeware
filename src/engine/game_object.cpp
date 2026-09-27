#include "game_object.hpp"
#include "components/rect_transform.hpp"
#include "components/rect_renderer.hpp"
#include "components/texture_renderer.hpp"

GameObject::GameObject(GameEngine* _engine, U32 index)
	: engine{_engine} 
{
	this->handle.key = index;
}

GameObject::GameObject(const GameObject& other)
	: engine{other.engine}
{
	this->handle = {
		.key = this->engine->registerGameObject(),
	};
	this->componentChecklist = other.componentChecklist;
	this->copyAllComponents(other);
}

auto GameObject::operator=(const GameObject& other) -> GameObject&
{
	if (this == &other) return *this;
	this->removeAllComponents();
	this->engine = other.engine;
	this->handle = {
		.key = this->engine->registerGameObject(),
	};
	this->componentChecklist = other.componentChecklist;
	this->copyAllComponents(other);
	return *this;
}

GameObject::GameObject(GameObject&& other) noexcept
	: engine{other.engine}
{
	this->handle = other.handle; // NOTE: This passes ownership of all components.
	this->componentChecklist = other.componentChecklist;
	other.handle.deregister();
}

auto GameObject::operator=(GameObject&& other) noexcept -> GameObject&
{
	if (this == &other) return *this;
	this->removeAllComponents();
	this->engine = other.engine;
	this->handle = other.handle; // NOTE: This passes ownership of all components.
	this->componentChecklist = other.componentChecklist;
	other.handle.deregister();
	return *this;
}

GameObject::~GameObject()
{
	this->removeAllComponents();
}

void GameObject::removeAllComponents()
{
	if (handle.key == 0) return;

	if (this->componentChecklist.isTicked<RectTransform>()) {
		this->removeComponent<RectTransform>();
	}
	if (this->componentChecklist.isTicked<RectRenderer>()) {
		this->removeComponent<RectRenderer>();
	}
	if (this->componentChecklist.isTicked<TextureRenderer>()) {
		this->removeComponent<TextureRenderer>();
	}
}

void GameObject::copyAllComponents(const GameObject& other)
{
	if (this->componentChecklist.isTicked<RectTransform>()) {
		this->copyComponent<RectTransform>(*other.getComponent<RectTransform>());
	}
	if (this->componentChecklist.isTicked<RectRenderer>()) {
		this->copyComponent<RectRenderer>(*other.getComponent<RectRenderer>());
	}
	if (this->componentChecklist.isTicked<TextureRenderer>()) {
		this->copyComponent<TextureRenderer>(*other.getComponent<TextureRenderer>());
	}
}
