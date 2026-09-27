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
		this->componentChecklist.tick<TComponent>();
		return this->engine->getOrCreatePool<TComponent>().emplace(
			this->handle, TComponent{std::forward<Args>(componentArgs)...});
	}

	template<typename TComponent>
	auto copyComponent(const TComponent& component) -> TComponent&
	{
		this->componentChecklist.tick<TComponent>();
		return this->engine->getOrCreatePool<TComponent>().emplace(this->handle, component);
	}

	template<typename TComponent>
	void removeComponent()
	{
		this->componentChecklist.untick<TComponent>();
		this->engine->getPool<TComponent>().remove(this->handle);
	}

	template<typename TComponent>
	auto getComponent()
		-> Maybe<Ref<TComponent>> { return this->engine->getPool<TComponent>().get(this->handle); }

	template<typename TComponent>
	auto getComponent() const
		-> Maybe<Ref<TComponent>> { return this->engine->getPool<TComponent>().get(this->handle); }

private:
	GameEngine* engine;
	GameObjectHandle handle;

	ComponentChecklist componentChecklist;
	
	GameObject(GameEngine* _engine, U32 index);

	void removeAllComponents();

	void copyAllComponents(const GameObject& other);
};
