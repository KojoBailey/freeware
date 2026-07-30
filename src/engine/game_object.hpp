#pragma once

#include "engine.hpp"
#include "game_object_handle.hpp"

class GameObject {
	friend class GameEngine;

public:
	template<typename TComponent, typename... Args>
	auto addComponent(Args&&... componentArgs) -> TComponent&
	{
		return engine->getPool<TComponent>().emplace(handle, TComponent{std::forward<Args>(componentArgs)...});
	}

private:
	GameEngine* engine;
	GameObjectHandle handle;
	
	GameObject(GameEngine* _engine)
		: engine{_engine} {}
};