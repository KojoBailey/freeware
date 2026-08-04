#include "game_object.hpp"

GameObject::GameObject(GameEngine* _engine, U32 index)
	: engine{_engine} 
{
	handle.index = index;
}

GameObject::GameObject(const GameObject& other)
	: engine{other.engine}
{
	handle = {
		.index = engine->registerGameObject(),
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
		.index = engine->registerGameObject(),
	};
	componentChecklist = other.componentChecklist;
	copyAllComponents(other);
	return *this;
}

GameObject::GameObject(GameObject&& other)
	: engine{other.engine}
{
	handle = other.handle; // NOTE: This passes ownership of all components.
	componentChecklist = other.componentChecklist;
	other.handle.deregister();
}

auto GameObject::operator=(GameObject&& other) -> GameObject&
{
	if (this == &other) return *this;
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
	if (handle.index == 0) return;

	for (USz i = 0; i < componentChecklist.size(); i++) {
		bool hasComponentT = componentChecklist[i];
		if (not hasComponentT) {
			continue;
		}

		switch (i) {
		case ComponentIndex<RectTransform>::value:
			removeComponent<RectTransform>();
			break;
		case ComponentIndex<RectRenderer>::value:
			removeComponent<RectRenderer>();
			break;
		case ComponentIndex<TextureRenderer>::value:
			removeComponent<TextureRenderer>();
			break;
		}
	}
}

void GameObject::copyAllComponents(const GameObject& other)
{
	for (USz i = 0; i < componentChecklist.size(); i++) {
		bool hasComponentT = componentChecklist[i];
		if (not hasComponentT) {
			continue;
		}

		switch (i) {
		case ComponentIndex<RectTransform>::value:
			copyComponent<RectTransform>(*other.getComponent<RectTransform>());
			break;
		case ComponentIndex<RectRenderer>::value:
			copyComponent<RectRenderer>(*other.getComponent<RectRenderer>());
			break;
		case ComponentIndex<TextureRenderer>::value:
			copyComponent<TextureRenderer>(*other.getComponent<TextureRenderer>());
			break;
		}
	}
}

