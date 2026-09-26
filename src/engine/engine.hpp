#pragma once

#include "pch.hpp"
#include "util.hpp"
#include "i_game.hpp"
#include "renderer.hpp"
#include "component_pool.hpp"
#include "texture.hpp"

#include <SDL3/SDL_init.h>

class GameObject;

class GameEngine {
public:
	GameEngine(const GameEngine&) = delete;
	auto operator=(const GameEngine&) -> GameEngine& = delete;

	GameEngine(GameEngine&&) = default;
	auto operator=(GameEngine&&) -> GameEngine& = default;

	static auto create() -> Result<GameEngine>;

	~GameEngine();

	auto load(UniquePtr<IGame> game) -> Result<Nothing>;
	
	auto run() -> Result<Nothing>;
	
	template<typename TComponent>
	auto getOrCreatePool() -> ComponentPool<TComponent>&
	{
		TypeIndex type = typeid(TComponent);
		auto iterator = this->componentPoolByTypeIndex.find(type);
		if (not wasFindSuccessful(iterator , this->componentPoolByTypeIndex)) {
			auto [insertedIterator,didInsert] = this->componentPoolByTypeIndex.emplace(
				type, std::make_unique<ComponentPool<TComponent>>());
			iterator = insertedIterator;
		}
		auto& [key,componentPool] = *iterator;
		return static_cast<ComponentPool<TComponent>&>(*componentPool);
	}
	
	auto createGameObject() -> GameObject;
	auto registerGameObject() -> U32;

	auto createTexture(const FilePath& path) -> Result<Texture>;

	auto getMousePosition() -> Vec2<F32>;
	auto isLeftClickActive() -> Bool;
	
private:
	UniquePtr<IGame> game;
	Window window;
    Renderer renderer;
	
	// NOTE: Start at 1 so that 0 is the empty handle.
	U32 lastEntityIndex = 1;
	
	HashMap<TypeIndex, UniquePtr<IComponentPool>> componentPoolByTypeIndex;

	U64 clockFrequency;
	U64 lastTimestamp;
	F64 deltaTime;
	Bool _isLeftClickActive{false};
	
	GameEngine() = default;

	auto processEvents() -> QuitStatus;
	void updateDeltaTime();
	auto render() -> Result<Nothing>;
};
