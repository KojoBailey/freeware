#include "engine.hpp"

class GameObject {
	friend class GameEngine;

public:
	template<typename T>
	auto addComponent() -> T&
	{
		return engine->registerComponent<T>();
	}

private:
	GameEngine* engine;
	
	GameObject(GameEngine* _engine)
		: engine{_engine} {}
};