#ifndef KOJO_SDL3_RECT_HPP
#define KOJO_SDL3_RECT_HPP

#include "Vec.hpp"

namespace sdl {

template<typename T>
struct Rect {
	Vec<T, 2> position;
	Vec<T, 2> size;
};

}

#endif
