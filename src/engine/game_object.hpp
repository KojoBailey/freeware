#pragma once

#include "engine.hpp"
#include "game_object_handle.hpp"
#include "components/component_type.hpp"
#include "components/rect_transform.hpp"
#include "components/rect_renderer.hpp"
#include "components/texture_renderer.hpp"

class GameObject {
	friend class GameEngine;

public:
	GameObject() = default;
	GameObject(const GameObject& other);
	auto operator=(const GameObject& other) -> GameObject&;
	GameObject(GameObject&& other);
	auto operator=(GameObject&& other) -> GameObject&;
	~GameObject();

	template<typename TComponent, typename... Args>
	auto addComponent(Args&&... componentArgs) -> TComponent&
	{
		componentChecklist.set(ComponentIndex<TComponent>::value);
		return engine->getPool<TComponent>().emplace(handle, TComponent{std::forward<Args>(componentArgs)...});
	}

	template<typename TComponent, typename... Args>
	auto copyComponent(const TComponent& component) -> TComponent&
	{
		componentChecklist.set(ComponentIndex<TComponent>::value);
		return engine->getPool<TComponent>().emplace(handle, component);
	}

	template<typename TComponent>
	void removeComponent()
	{
		componentChecklist.reset(ComponentIndex<TComponent>::value);
		engine->getPool<TComponent>().remove(handle);
	}

	template<typename TComponent>
	auto getComponent() -> TComponent*
	{
		return engine->getPool<TComponent>().get(handle);
	}

	template<typename TComponent>
	auto getComponent() const -> TComponent*
	{
		return engine->getPool<TComponent>().get(handle);
	}

private:
	GameEngine* engine;
	GameObjectHandle handle;

	Bitset<3> componentChecklist{false};
	
	GameObject(GameEngine* _engine, U32 index);

	void removeAllComponents();

	void copyAllComponents(const GameObject& other);
};
