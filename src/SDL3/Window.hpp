#ifndef KOJO_SDL3_WINDOW_HPP
#define KOJO_SDL3_WINDOW_HPP

#include "Vec.hpp"

#include <SDL3/SDL_error.h>
#include <SDL3/SDL_video.h>

#include <expected>
#include <memory>
#include <string>
#include <string_view>

namespace sdl {

enum WindowFlag : std::uint64_t {
	None              = 0,
	Fullscreen        = 0x0000000000000001,
	OpenGL            = 0x0000000000000002, // Usable with OpenGL context.
	Occluded          = 0x0000000000000004, // Neither mapped onto desktop nor shown in taskbar/dock/window list.
						// Can be made visible via Window::show().
	Hidden            = 0x0000000000000008,
	Borderless        = 0x0000000000000010,
	Resizable         = 0x0000000000000020,
	Minimized         = 0x0000000000000040,
	Maximized         = 0x0000000000000080,
	MouseGrabbed      = 0x0000000000000100,
	InputFocus        = 0x0000000000000200,
	MouseFocus        = 0x0000000000000400,
	External          = 0x0000000000000800, // Not created by SDL.
	Modal             = 0x0000000000001000,
	HighPixelDensity  = 0x0000000000002000, // Uses a high pixel density back buffer if possible.
	MouseCapture      = 0x0000000000004000,
	MouseRelativeMode = 0x0000000000008000,
	AlwaysOnTop       = 0x0000000000010000,
	Utility           = 0x0000000000020000,
	Tooltip           = 0x0000000000040000, // Requires parent window.
	PopupMenu         = 0x0000000000080000, // Requires parent window.
	KeyboardGrabbed   = 0x0000000000100000,
	FillDocument      = 0x0000000000200000, // Emscripten only.
	Vulkan            = 0x0000000010000000, // Usable for Vulkan surface.
	Metal             = 0x0000000020000000, // Usable for Metal view.
	Transparent       = 0x0000000040000000,
	NotFocusable      = 0x0000000080000000,
};

class Window {
public:
	static auto create(std::string_view title, const Vec2<float> dimensions, const WindowFlag flags = WindowFlag::None)
		-> std::expected<Window, std::string>
	{
		Window result;
		result.handle.reset(SDL_CreateWindow(title.data(), (int)dimensions.x, (int)dimensions.y, 0));
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
