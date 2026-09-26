#pragma once

#include "pch.hpp"
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
	auto getPool() -> ComponentPool<TComponent>&
	{
		auto type = TypeIndex{typeid(TComponent)};
		auto it = componentPools.find(type);
		if (it == componentPools.end()) {
			auto [inserted, ok] = componentPools.emplace(type, std::make_unique<ComponentPool<TComponent>>());
			it = inserted;
		}
		return static_cast<ComponentPool<TComponent>&>(*it->second);
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
	
	HashMap<TypeIndex, UniquePtr<IComponentPool>> componentPools;

	Bool _isLeftClickActive{false};
	
	GameEngine() = default;
};
