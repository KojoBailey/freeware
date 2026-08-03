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

	GameObject(const GameObject& other)
		: engine{other.engine}
	{
		// TODO: Probably make use of assignment overload.
		handle.index = engine->registerGameObject();
		handle.generation = 0;

		componentChecklist = other.componentChecklist;

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

	auto operator=(const GameObject& other) -> GameObject&
	{
		if (this == &other) return *this;
		// TODO: Remove existing components as well.
		engine = other.engine;
		handle.index = engine->registerGameObject();
		componentChecklist = other.componentChecklist;
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
		return *this;
	}

	// TODO: Clean up resources on destruction.
	~GameObject() = default;

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
	
	GameObject(GameEngine* _engine, U32 index)
		: engine{_engine} 
	{
		handle.index = index;
	}
};
