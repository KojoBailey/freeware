#pragma once

#include "engine.hpp"
#include "game_object_handle.hpp"
#include "components/component_type.hpp"

class GameObject {
	friend class GameEngine;

public:
	GameObject() = default;

	GameObject(const GameObject& other);
	auto operator=(const GameObject& other) -> GameObject&;

	GameObject(GameObject&& other) noexcept;
	auto operator=(GameObject&& other) noexcept -> GameObject&;

	~GameObject();

	template<typename TComponent, typename... Args>
	auto addComponent(Args&&... componentArgs) -> TComponent&
	{
		componentChecklist.tick<TComponent>();
		return engine->getOrCreatePool<TComponent>().emplace(
			handle, TComponent{std::forward<Args>(componentArgs)...});
	}

	template<typename TComponent, typename... Args>
	auto copyComponent(const TComponent& component) -> TComponent&
	{
		componentChecklist.tick<TComponent>();
		return engine->getOrCreatePool<TComponent>().emplace(handle, component);
	}

	template<typename TComponent>
	void removeComponent()
	{
		componentChecklist.untick<TComponent>();
		engine->getOrCreatePool<TComponent>().remove(handle);
	}

	template<typename TComponent>
	auto getComponent()
		-> Maybe<Ref<TComponent>> { return engine->getOrCreatePool<TComponent>().get(handle); }

	template<typename TComponent>
	auto getComponent() const
		-> Maybe<Ref<TComponent>> { return engine->getOrCreatePool<TComponent>().get(handle); }

private:
	GameEngine* engine;
	GameObjectHandle handle;

	ComponentChecklist componentChecklist;
	
	GameObject(GameEngine* _engine, U32 index);

	void removeAllComponents();

	void copyAllComponents(const GameObject& other);
};
