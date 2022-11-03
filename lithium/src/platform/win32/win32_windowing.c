#include "base/base_context_crack.h"
#ifdef LI_OS_WINDOWS

#include "platform/platform_windowing.h"
#include "base/base_logging.h" 

#include <Windows.h>

struct LiWindow {
	HINSTANCE instance;
	HWND window;
	B8 closed;
};

static LRESULT CALLBACK internal_processMessage(HWND hwnd, U32 msg, WPARAM w_param, LPARAM l_param)
{
	switch (msg) {
		case WM_DESTROY: {
			PostQuitMessage(0);
			return 0;
		};
		default: {
		} break;
	}

	return DefWindowProcA(hwnd, msg, w_param, l_param);
}

LiWindow *liWindowCreate(LiArena *arena, U32 width, U32 height, const char *title, B8 resizable)
{
	LiWindow *window = liArenaPush(arena, sizeof(LiWindow));
	window->closed = false;

	// Get instance.
	window->instance = GetModuleHandleA(0);

	const char *class_name = "lithium_window_class";
	WNDCLASSA wc = {0};
	wc.lpfnWndProc = internal_processMessage;
	wc.hInstance = window->instance;
	wc.lpszClassName = class_name;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);

	if (!RegisterClassA(&wc)) {
		liLogError("Failed to register window!");
		liArenaPop(arena, sizeof(LiWindow));
		return NULL;
	}

	DWORD style = WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX;
	if (resizable) {
		style |= WS_MAXIMIZEBOX;
		style |= WS_THICKFRAME;
	}

	// Correct window sizing
	RECT border_rect = {0};
	AdjustWindowRectEx(&border_rect, style, 0, 0);
	U32 border_margin_x = border_rect.right - border_rect.left;
	U32 border_margin_y = border_rect.bottom - border_rect.top;

	// Create window.
	window->window = CreateWindowExA(
		0,
		"lithium_window_class",
		title,
		style,
		CW_USEDEFAULT, CW_USEDEFAULT, // X, Y
		width + border_margin_x, height + border_margin_y,
		0,
		0,
		window->instance,
		0
	);
	if (window->window == NULL) {
		liLogError("Failed to create window!");
		liArenaPop(arena, sizeof(LiWindow));
		return NULL;
	}
	// Present window.
	ShowWindow(window->window, SW_SHOW);

	return window;
}

void liWindowDestroy(LiWindow *window)
{
	DestroyWindow(window->window);
}

void liWindowPollEvents(LiWindow *window)
{
	MSG msg = { 0 };
	while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE)) {
		if (msg.message == WM_QUIT) {
			window->closed = true;
		} else {
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}
	}
}

B8 liWindowClosed(const LiWindow *window)
{
	return window->closed;
}

#endif // LI_OS_WINDOWS
