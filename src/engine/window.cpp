#include "window.hpp"

auto Window::create(
	std::string_view title,
	const Vec2<F32> size
) -> Result<Window>
{
	Window result;
	result.handle.reset(SDL_CreateWindow(title.data(), (I32)size.x, (I32)size.y, 0));
	if (result.handle == nullptr) {
		return std::unexpected{SDL_GetError()};
	}
	return result;
}

auto Window::get() const -> SDL_Window*
{
	return handle.get();
}