#pragma once

#include "engine.hpp"
#include "game_object_handle.hpp"

class GameObject {
	friend class GameEngine;

public:
	GameObject() = default;

	template<typename TComponent, typename... Args>
	auto addComponent(Args&&... componentArgs) -> TComponent&
	{
		return engine->getPool<TComponent>().emplace(handle, TComponent{std::forward<Args>(componentArgs)...});
	}

	template<typename TComponent>
	auto getComponent() -> TComponent*
	{
		return engine->getPool<TComponent>().get(handle);
	}

private:
	GameEngine* engine;
	GameObjectHandle handle;
	
	GameObject(GameEngine* _engine, U32 index)
		: engine{_engine} 
	{
		handle.index = index;
	}
};
