#pragma once

#include "util.hpp"
#include "i_game.hpp"
#include "renderer.hpp"

#include "rect_renderer.hpp"

#include <SDL3/SDL_init.h>

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
		if (!maybeWindow.has_value()) {
			return Error(maybeWindow.error());
		}
		result.window = std::move(*maybeWindow);

		auto maybeRenderer = Renderer::create(result.window);
		if (!maybeRenderer.has_value()) {
			return Error(maybeRenderer.error());
		}
		result.renderer = std::move(*maybeRenderer);
		
		result.game = std::make_unique<T>(std::forward<Args>(gameArgs)...);
		
		return result;
	}
	
	void run();
	
	auto createGameObject() -> GameObject;
	
	template<typename T>
	auto registerComponent() -> T&
	{
		return rectRenderers.emplace_back();
	}
	
private:
	UniquePtr<IGame> game;
	Window window;
    Renderer renderer;
	
	bool isRunning;
	
	Vector<RectRenderer> rectRenderers;
	
	GameEngine() = default;
};