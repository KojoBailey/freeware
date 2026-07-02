#ifndef KOJO_SDL3_SDL_HPP
#define KOJO_SDL3_SDL_HPP

#include <SDL3/SDL.h>

#include "game.hpp"
#include "texture.hpp"

namespace sdl {

void init()
{
	SDL_Init(SDL_INIT_VIDEO);
}

void quit()
{
	SDL_Quit();
}

}

#endif
