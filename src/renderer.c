#define MU_SUPPORT_OPENGL
#define MUG_NAMES
#define MUCOSA_NAMES
#define MUG_IMPLEMENTATION
//#include <muGraphics.h>

#include "renderer.h"

renderer renderer_init(uint width, uint height, char* window_name, float fps) {
    renderer renderer;
    renderer.gfx_system = MU_GRAPHIC_OPENGL;
    renderer.window_system = MU_WINDOW_NULL; // auto
    renderer.pixel_format = (muPixelFormat){
        // RGBA bits
		8, 8, 8, 8,
		// Depth bits
		24,
		// Stencil bits
		0,
		// Samples
		1
    };
    renderer.wininfo = (muWindowInfo){
        // Title
		window_name,
		// Resolution (width & height)
		800, 600,
		// Min/Max resolution (none)
		0, 0, 0, 0,
		// Coordinates (x and y)
		50, 50,
		// Pixel format
		&renderer.pixel_format,
		// Callbacks (default)
		0
    };

    // init mug
    mug_context_create(&renderer.mug, renderer.window_system, MU_TRUE);

    renderer.gfx = mu_graphic_create_window(renderer.gfx_system, &renderer.wininfo);
    renderer.win = mu_graphic_get_window(renderer.gfx);
    mu_window_get(renderer.win, MU_WINDOW_KEYBOARD_MAP, &renderer.keyboard);


    renderer.fps_target = fps;

    return renderer;
}

bool renderer_should_close(renderer* renderer) {
    return !mu_graphic_exists(renderer->gfx);
}

void renderer_update(renderer* renderer) {
    mu_graphic_swap_buffers(renderer->gfx);
    mu_graphic_update(renderer->gfx,renderer->fps_target);
}

void renderer_clear(renderer* renderer) {
    mu_graphic_clear(renderer->gfx,15.f/255.f, 17.f/255.f, 15.f/255.f);
}

void renderer_close(renderer* renderer) {
    mu_window_close(renderer->win);
}

void renderer_destroy(renderer* renderer) {
    renderer->gfx = mu_graphic_destroy(renderer->gfx);
    mug_context_destroy(&renderer->mug);

    // Print possible error
	if (renderer->mug.result != MUG_SUCCESS) {
		printf("Something went wrong during the program's life; result: %s\n",
			mug_result_get_name(renderer->mug.result)
		);
	} else {
		printf("Successful\n");
	}
}