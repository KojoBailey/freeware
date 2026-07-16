#include "window.hpp"

auto Window::create(
	std::string_view title,
	const Vec2<I32> size
) -> Result<Window>
{
	Window result;
	result.handle.reset(SDL_CreateWindow(
		title.data(), 
		size.x, size.y, 
		0
	));
	if (result.handle == nullptr) {
		return Error{SDL_GetError()};
	}
	return result;
}

auto Window::get() const -> SDL_Window*
{
	return handle.get();
}