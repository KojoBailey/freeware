#pragma once

#include "pch.hpp"
#include "i_game.hpp"
#include "renderer.hpp"
#include "component_pool.hpp"
#include "texture.hpp"

#include <SDL3/SDL_init.h>

#include "components/rect_transform.hpp"
#include "components/rect_renderer.hpp"
#include "components/texture_renderer.hpp"

#include <typeindex>

class GameObject;

class GameEngine {
public:
	GameEngine(const GameEngine&) = delete;
	auto operator=(const GameEngine&) -> GameEngine& = delete;

	GameEngine(GameEngine&&) = default;
	auto operator=(GameEngine&&) -> GameEngine& = default;

	~GameEngine() = default;

	static auto create(StringView title, Vec2<I32> windowSize) -> Result<GameEngine>
	{
		GameEngine result;

		SDL_InitSubSystem(SDL_INIT_AUDIO | SDL_INIT_VIDEO);
		
		auto maybeWindow = Window::create(title, windowSize);
		if (not maybeWindow.has_value()) {
			return Error(maybeWindow.error());
		}
		result.window = std::move(*maybeWindow);

		auto maybeRenderer = Renderer::create(result.window);
		if (not maybeRenderer.has_value()) {
			return Error(maybeRenderer.error());
		}
		result.renderer = std::move(*maybeRenderer);
		
		return result;
	}
	
	template<std::derived_from<IGame> Game>
	auto run() -> Result<Nothing>
	{
		this->game = std::make_unique<Game>();
			
		isRunning = true;
		
		auto startResult = game->init(*this);
		if (not startResult.has_value()) {
			return Error(startResult.error());
		}

		U64 clockFrequency = SDL_GetPerformanceFrequency();
		U64 lastClock = SDL_GetPerformanceCounter();
		
		while (isRunning) {
			SDL_Event event;
			while (SDL_PollEvent(&event)) {
				mIsMouseDown = false;
				switch (event.type) {
				case SDL_EVENT_QUIT:
					isRunning = false;
					break;
				case SDL_EVENT_MOUSE_BUTTON_DOWN:
					if (event.button.button == SDL_BUTTON_LEFT) {
						mIsMouseDown = true;
					}
					break;
				default: break;
				}
			}

			U64 currentClock = SDL_GetPerformanceCounter();
			F64 deltaTime = (F64)(currentClock - lastClock) / (F64)clockFrequency;
			lastClock = currentClock;
			auto updateResult = game->update(*this, deltaTime);
			if (not updateResult.has_value()) {
				return Error(updateResult.error());
			}
			
			renderer.setDrawColor(0, 0, 0);
			renderer.clear();
			
			auto& rectTransforms = getPool<RectTransform>();
			auto& rectRenderers = getPool<RectRenderer>();
			auto& textureRenderers = getPool<TextureRenderer>();

			// TODO: Implement render order system.
			
			for (auto [handle, textureRenderer] : textureRenderers) {
				Maybe<Ref<RectTransform>> maybeRectTransform = rectTransforms.get(handle);
				if (not maybeRectTransform.has_value()) {
					return Error("Tried to render TextureRenderer for GameObject without a RectTransform.");
				}
				RectTransform& rectTransform = std::move(*maybeRectTransform);
				SDL_FRect sdlFRect = {
					.x = rectTransform.position.x + textureRenderer.positionOffset.x,
					.y = rectTransform.position.y + textureRenderer.positionOffset.y,
					.w = rectTransform.size.x * textureRenderer.scale.x,
					.h = rectTransform.size.y * textureRenderer.scale.y,
				};
				SDL_RenderTexture(renderer.get(), textureRenderer.texture->get(), nullptr, &sdlFRect);
			}

			for (auto [handle, rectRenderer] : rectRenderers) {
				Maybe<Ref<RectTransform>> maybeRectTransform = rectTransforms.get(handle);
				if (not maybeRectTransform.has_value()) {
					return Error("Tried to render RectRenderer for GameObject without a RectTransform.");
				}
				RectTransform& rectTransform = std::move(*maybeRectTransform);
				renderer.setDrawColor(rectRenderer.color);
				SDL_FRect sdlFRect = {
					.x = rectTransform.position.x + rectRenderer.positionOffset.x,
					.y = rectTransform.position.y + rectRenderer.positionOffset.y,
					.w = rectTransform.size.x * rectRenderer.scale.x,
					.h = rectTransform.size.y * rectRenderer.scale.y,
				};
				SDL_RenderFillRect(renderer.get(), &sdlFRect);
			}

			renderer.draw();
		}

		SDL_Quit();
		
		return {};
	}
	
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
