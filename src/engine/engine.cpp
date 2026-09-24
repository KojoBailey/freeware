#include "engine.hpp"
#include "SDL3/SDL_mouse.h"
#include "game_object.hpp"

#include <SDL3/SDL_timer.h>

auto GameEngine::createGameObject() -> GameObject
{
	return GameObject{this, lastEntityIndex++};
}

auto GameEngine::registerGameObject() -> U32
{
	return lastEntityIndex++;
}

auto GameEngine::createTexture(const FilePath& path) -> Result<Texture>
{
	return Texture::create(renderer, path);
}

auto GameEngine::getMousePosition() -> Vec2<F32>
{
	Vec2<F32> mousePosition;
	auto _ = SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
	return mousePosition;
}

auto GameEngine::isMouseDown() -> Bool
{
	return mIsMouseDown;
}
