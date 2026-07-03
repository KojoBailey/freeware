#ifndef KOJO_SDL3_VEC_HPP
#define KOJO_SDL3_VEC_HPP

namespace sdl {

template<typename T, std::size_t N> struct Vec;

template<typename T> struct Vec<T, 2> { T x, y; };
template<typename T> struct Vec<T, 3> { T x, y, z; };
template<typename T> struct Vec<T, 4> { T w, x, y, z; };

}

#endif
