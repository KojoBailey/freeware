#ifndef KOJO_SDL3_EVENT_HPP
#define KOJO_SDL3_EVENT_HPP

#include "MouseButtonEvent.hpp"

#include <SDL3/SDL_events.h>
#include <cstdint>

namespace sdl {

enum class EventType : std::uint32_t {
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

	/* Joystick Events */
	JoystickAxisMotion = 0x600,
	JoystickBallMotion,
	JoystickHatMotion,
	JoystickButtonDown,
	JoystickButtonUp,
	JoystickAdded,
	JoystickRemoved,
	JoystickBatteryUpdated,
	JoystickUpdateComplete,

	/* Gamepad Events */
	GamepadAxisMotion = 0x650,
	GamepadButtonDown,
	GamepadButtonUp,
	GamepadAdded,
	GamepadRemoved,
	GamepadRemapped,
	GamepadTouchpadDown,
	GamepadTouchpadMotion,
	GamepadTouchpadUp,
	GamepadSensorUpdate,
	GamepadUpdateComplete,
	GamepadSteamHandleUpdated,
	GamepadCapSenseTouch,
	GamepadCapSenseRelease,

	/* Touch Events */
	FingerDown = 0x700,
	FingerUp,
	FingerMotion,
	FingerCanceled,

	/* Pinch Events */
	PinchBegin = 0x710,
	PinchUpdate,
	PinchEnd,

	/* Clipboard Events */
	ClipboardUpdate = 0x900,

	/* Drag&Drop Events */
	DropFile = 0x1000,
	DropText,
	DropBegin,
	DropComplete,
	DropPosition,

	/* Audio Hotplug Events */
	AudioDeviceAdded = 0x1100,
	AudioDeviceRemoved,
	AudioDeviceFormatChanged,

	/* Sensor Events */
	SensorUpdate = 0x1200,

	/* Pressure-Sensitive Pen Events */
	PenProximityIn = 0x1300,
	PenProximityOut,
	PenDown,
	PenUp,
	PenButtonDown,
	PenButtonUp,
	PenMotion,
	PenAxis,

	/* Camera Hotplug Events */
	CameraDeviceAdded = 0x1400,
	CameraDeviceRemoved,
	CameraDeviceApproved,
	CameraDeviceDenied,

	/* Notification Events */
	NotificationActionInvoked = 0x1500,

	/* Render Events */
	RenderTargetsReset = 0x2000,
	RenderDeviceReset,
	RenderDeviceLost,

	/* Reserved Events for Private Platforms */
	Private0 = 0x4000,
	Private1,
	Private2,
	Private3,

	/* Internal Events */
	PollSentinel = 0x7F00,

	/* User-Defined Events */
	UserBegin = 0x8000,
	UserLast  = 0xFFFF,

	EnumPadding = 0x7FFFFFFF, // Fills u32.
};

class Event {
public:
	auto poll() -> bool
	{
		return SDL_PollEvent(&event);
	}

	auto getType() -> EventType
	{
		return static_cast<EventType>(event.type);
	}

	auto getMouseButton() -> MouseButtonEvent
	{
		return MouseButtonEvent{event.button};
	}

private:
	SDL_Event event;
};

}

#endif
