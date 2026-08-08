#pragma once

#include "pch.hpp"
#include "i_game.hpp"
#include "renderer.hpp"
#include "component_pool.hpp"
#include "texture.hpp"

#include <SDL3/SDL_init.h>

#include <typeindex>

class GameObject;

class GameEngine {
public:
	GameEngine(const GameEngine&) = delete;
	auto operator=(const GameEngine&) -> GameEngine& = delete;

	GameEngine(GameEngine&&) = default;
	auto operator=(GameEngine&&) -> GameEngine& = default;

	~GameEngine() = default;

	template<std::derived_from<IGame> T, typename... Args>
	static auto initGame(
		StringView name,
		Vec2<I32> windowSize,
		Args&&... gameArgs
	) -> Result<GameEngine>
	{
		GameEngine result;

		SDL_InitSubSystem(SDL_INIT_AUDIO | SDL_INIT_VIDEO);
		
		auto maybeWindow = Window::create(name, windowSize);
		if (not maybeWindow.has_value()) {
			return Error(maybeWindow.error());
		}
		result.window = std::move(*maybeWindow);

		auto maybeRenderer = Renderer::create(result.window);
		if (not maybeRenderer.has_value()) {
			return Error(maybeRenderer.error());
		}
		result.renderer = std::move(*maybeRenderer);
		
		result.game = std::make_unique<T>(std::forward<Args>(gameArgs)...);
		
		return result;
	}
	
	auto run() -> Result<Nothing>;
	
	template<typename TComponent>
	auto getPool() -> ComponentPool<TComponent>&
	{
		auto type = std::type_index(typeid(TComponent));
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
	auto isMouseDown() -> Bool; // NOTE: Only detects left-click.
	
private:
	UniquePtr<IGame> game;
	Window window;
    Renderer renderer;
	
	bool isRunning;

	// NOTE: Start at 1 so that 0 is the empty handle.
	U32 lastEntityIndex = 1;
	
	HashMap<std::type_index, UniquePtr<IComponentPool>> componentPools;

	bool mIsMouseDown{false};
	
	GameEngine() = default;
};
