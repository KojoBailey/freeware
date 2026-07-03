#ifndef KOJO_SDL3_EVENT_HPP
#define KOJO_SDL3_EVENT_HPP

#include <SDL3/SDL_events.h>
#include <cstdint>

namespace sdl {

enum EventType : std::uint32_t {
	First = 0, // Unused, but do not remove.
	
	/* Application Events */
	Quit = 0x100, // User-requested quit.
	Terminating,  // Being terminated by the OS.
	LowMemory,
	WillEnterBackground,
	DidEnterBackground,
	WillEnterForeground,
	DidEnterForeground,
	LocaleChanged,
	SystemThemeChanged,

	/* Display Events */
	DisplayOrientation = 0x151,
	DisplayAdded,
	DisplayRemoved,
	DisplayMoved,
	DisplayDesktopModeChanged,
	DisplayCurrentModeChanged,
	DisplayContentScaleChanged,
	DisplayUsableBoundsChanged,
	DisplayFirst = EventType::DisplayOrientation,
	DisplayLast = EventType::DisplayUsableBoundsChanged,

	/* Window Events */
	WindowShown = 0x202,
	WindowHidden,
	WindowExposed,
	WindowMoved,
	WindowResized,
	WindowPixelSizeChanged,
	WindowMetalViewResized,
	WindowMinimized,
	WindowMaximized,
	WindowRestored,
	WindowMouseEnter,
	WindowMouseLeave,
	WindowFocusGained,
	WindowFocusLost,
	WindowCloseRequested,
	WindowHitTest,
	WindowIccProfChanged,
	WindowDisplayChanged,
	WindowDisplayScaleChanged,
	WindowSafeAreaChanged,
	WindowOccluded,
	WindowEnterFullscreen,
	WindowLeaveFullscreen,
	WindowDestroyed,
	WindowHdrStateChanged,
	WindowSettingsChanged,
	WindowFirst = EventType::WindowShown,
	WindowLast = EventType::WindowSettingsChanged,

	/* Keyboard Events */
	KeyDown = 0x300,
	KeyUp,
	TextEditing,
	TextInput,
	KeymapChanged,
	KeyboardAdded,
	KeyboardRemoved,
	TextEditingCandidates,
	ScreenKeyboardShown,
	ScreenKeyboardHidden,

	/* Mouse Events */
	MouseMotion = 0x400,
	MouseButtonDown,
	MouseButtonUp,
	MouseWheel,
	MouseAdded,
	MouseRemoved,
};

class Event {
public:
	auto poll() -> bool
	{
		return SDL_PollEvent(&event);
	}

	auto get_type() -> EventType
	{
		return static_cast<EventType>(event.type);
	}

private:
	SDL_Event event;
};

}

#endif
