#include "base/base_context_crack.h"
#include <vulkan/vulkan_core.h>
#ifdef LI_OS_LINUX

#define VK_USE_PLATFORM_XCB_KHR
#include "platform/platform_windowing.h"
#include "base/base_logging.h"

#include <xcb/xcb.h>
#include <string.h>
#include <malloc.h>

struct LiWindow {
	xcb_connection_t *connection;
	xcb_window_t window;
	xcb_screen_t *screen;
	xcb_atom_t wm_protocols;
	xcb_atom_t wm_delete_win;
	B8 closed;
};

LiWindow *liWindowCreate(LiArena *arena, U32 width, U32 height, const char *title)
{
	LiWindow *window = liArenaPush(arena, sizeof(LiWindow));
	window->closed = false;

	I32 screenp = 0;
	window->connection = xcb_connect(NULL, &screenp);
	if (xcb_connection_has_error(window->connection)) {
		liLogError("Failed to connect to X server using XCB.");
		return NULL;
	}

	xcb_screen_iterator_t iter = xcb_setup_roots_iterator(xcb_get_setup(window->connection));
	for (U32 i = screenp; i > 0; i--) {
		xcb_screen_next(&iter);
	}
	window->screen = iter.data;

	// Create window
	window->window = xcb_generate_id(window->connection);
	U32 event_mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
	U32 value_list[] = { window->screen->black_pixel, 0 };

	xcb_create_window(
		window->connection,
		XCB_COPY_FROM_PARENT,
		window->window,
		window->screen->root,
		0, 0, // Position
		width, height,
		0,
		XCB_WINDOW_CLASS_INPUT_OUTPUT,
		window->screen->root_visual,
		event_mask,
		value_list
	);

	xcb_change_property(
		window->connection,
		XCB_PROP_MODE_REPLACE,
		window->window,
		XCB_ATOM_WM_NAME,
		XCB_ATOM_STRING,
		8,
		strlen(title),
		title
	);

	// Close button
	xcb_intern_atom_cookie_t wm_delete_cookie = xcb_intern_atom(window->connection, 0, strlen("WM_DELETE_WINDOW"), "WM_DELETE_WINDOW");
	xcb_intern_atom_cookie_t wm_protocols_cookie = xcb_intern_atom(window->connection, 0, strlen("WM_PROTOCOLS"), "WM_PROTOCOLS");
	xcb_intern_atom_reply_t *wm_delete_reply = xcb_intern_atom_reply(window->connection, wm_delete_cookie, NULL);
	xcb_intern_atom_reply_t *wm_protocols_reply = xcb_intern_atom_reply(window->connection, wm_protocols_cookie, NULL);
	window->wm_delete_win = wm_delete_reply->atom;
	window->wm_protocols = wm_protocols_reply->atom;

	xcb_change_property(window->connection, XCB_PROP_MODE_REPLACE, window->window, wm_protocols_reply->atom, 4, 32, 1, &wm_delete_reply->atom);

	xcb_map_window(window->connection, window->window);
	xcb_flush(window->connection);

	return window;
}

void liWindowDestroy(LiWindow *window) { xcb_destroy_window(window->connection, window->window); }

void liWindowPollEvents(LiWindow *window)
{
	xcb_generic_event_t *event;
	xcb_client_message_event_t *cm;

	while ((event = xcb_poll_for_event(window->connection))) {
		switch (event->response_type & ~0x80) {
			case XCB_CLIENT_MESSAGE: {
				cm = (xcb_client_message_event_t *) event;
				// Window close
				if (cm->data.data32[0] == window->wm_delete_win) {
					window->closed = true;
				}
			} break;
			default: {
			} break;
		}
		free(event);
	}
}

B8 liWindowClosed(const LiWindow *window) { return window->closed; }

VkSurfaceKHR liWindowGetSurface(const LiWindow *window, VkInstance instance)
{
	VkSurfaceKHR surface;

	VkXcbSurfaceCreateInfoKHR surface_create_info = {};
	surface_create_info.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
	surface_create_info.pNext = NULL;
	surface_create_info.flags = 0;
	surface_create_info.connection = window->connection;
	surface_create_info.window = window->window;

	VkResult result = vkCreateXcbSurfaceKHR(instance, &surface_create_info, NULL, &surface);
	if (result != VK_SUCCESS) {
		liLogError("Failed to create XCB vulkan surface!");
		return NULL;
	}

	return surface;
}

#endif // LI_OS_LINUX
