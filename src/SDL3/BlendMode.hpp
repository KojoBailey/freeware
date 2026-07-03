#ifndef KOJO_SDL3_BLEND_MODE_HPP
#define KOJO_SDL3_BLEND_MODE_HPP

#include <SDL3/SDL_blendmode.h>
#include <cstdint>

namespace sdl {

enum class BlendMode : std::uint32_t {
	None                  = 0x00000000u,
	Blend                 = 0x00000001u,
	BlendPremultiplied    = 0x00000010u,
	Additive              = 0x00000002u,
	AdditivePremultiplied = 0x00000020u,
	Modulate              = 0x00000004u,
	Multiply              = 0x00000008u,
	Invalid               = 0x7FFFFFFFu,
};

}

#endif
