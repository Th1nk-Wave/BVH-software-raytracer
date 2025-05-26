#ifndef __RENDERER_H_
#define __RENDERER_H_


#include <stdbool.h>
#include <muGraphics.h>

#include "defines.h"

typedef struct {
    mugContext mug;
    muGraphic gfx;
    muGraphicSystem gfx_system;
    muWindowSystem window_system;
    muPixelFormat pixel_format;
    muWindowInfo wininfo;
    muWindow win;
    muBool* keyboard;

    float fps_target;
} renderer;

renderer renderer_init(uint width, uint height, char* window_name, float fps);
bool renderer_should_close(renderer* renderer);
void renderer_clear(renderer* renderer);
void renderer_update(renderer* renderer);
void renderer_close(renderer* renderer);
void renderer_destroy(renderer* renderer);


#endif