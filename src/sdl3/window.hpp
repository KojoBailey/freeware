#ifndef KOJO_SDL3_WINDOW_HPP
#define KOJO_SDL3_WINDOW_HPP

#include <SDL3/SDL.h>

#include <expected>
#include <memory>
#include <string>
#include <string_view>

namespace sdl {

class Window {
public:
	static auto create(std::string_view title, const int width, const int height)
		-> std::expected<Window, std::string>
	{
		Window result;
		result.handle.reset(SDL_CreateWindow(title.data(), width, height, 0));
		if (result.handle == nullptr) {
			return std::unexpected{SDL_GetError()};
		}
		return result;
	}

	auto get() -> SDL_Window*
	{
		return handle.get();
	}
	
private:
	std::unique_ptr<SDL_Window, decltype([](SDL_Window* w) { SDL_DestroyWindow(w); })> handle;
};

}

#endif
