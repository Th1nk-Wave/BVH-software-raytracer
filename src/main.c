#include <stdio.h>
#include <muGraphics.h>

#include "defines.h"
#include "triangle.h"
#include "ray.h"
#include "rng.h"
#include "renderer.h"


#define N 20

#define WIDTH 800
#define HEIGHT 600

triangle tris[N];
uint8_m pixels[WIDTH*HEIGHT*4];

uint32_m dim[2] = { WIDTH, HEIGHT };
mug2DTextureRect texrect = {
	// Center point
	{
		// Position (xyz)
		{ WIDTH/2, HEIGHT/2, 0.f },
		// Color (rgba)
		{ 1.f, 1.f, 1.f, 1.f }
	},
	// Dimensions
	{ WIDTH, HEIGHT },
	// Rotation
	0.f,
	// Texture position
	{ 0.f, 0.f },
	// Texture dimensions
	{ 1.f, 1.f }
};

mugObjects texbuf;

mugTextureInfo texinfo = {
	// Type (2D)
	MUG_TEXTURE_2D,
	// Format (uint8_m RGBA)
	MUG_TEXTURE_U8_RGBA,
	// Wrapping x and y (clamp)
	{ MUG_TEXTURE_CLAMP, MUG_TEXTURE_CLAMP },
	// Filtering up-/downscale (nearest)
	{ MUG_TEXTURE_NEAREST, MUG_TEXTURE_NEAREST }
};

mugTexture tex;


void calc_pixel() {
	vec3 p0 = {-1, 1, -15}, p1 = {1, 1, -15}, p2 = {-1, -1, -15};
    ray cast;

    for (uint y = 0; y < HEIGHT; y++)  {
        uint32_m ph = y*WIDTH;
        for (uint x = 0; x < WIDTH; x++) {
            uint32_m pw = (ph+x)*4;

            vec3 pixelPos;
            pixelPos[0] = p0[0] + (p1[0] - p0[0]) * (x / (float)WIDTH) + (p2[0] - p0[0]) * (y / (float)HEIGHT);
            pixelPos[1] = p0[1] + (p1[1] - p0[1]) * (x / (float)WIDTH) + (p2[1] - p0[1]) * (y / (float)HEIGHT);
            pixelPos[2] = p0[2] + (p1[2] - p0[2]) * (x / (float)WIDTH) + (p2[2] - p0[2]) * (y / (float)HEIGHT);
        
            cast.O[0] = 0; cast.O[1] = 0; cast.O[2] = -18;
        
            vec3_normalize((vec3){pixelPos[0] - cast.O[0], pixelPos[1] - cast.O[1], pixelPos[2] - cast.O[2]}, cast.D);

            cast.t = FLOAT_INFINITY;

            for (uint i = 0; i < N; i++) {intersect_triangle(&cast, &tris[i]);}
            if (cast.t < FLOAT_INFINITY){
                pixels[pw  ] = ((float)x / (float)WIDTH) * 255.f;
			    // - Gradient on the y; more y, more green
			    pixels[pw+1] = ((float)y / (float)HEIGHT) * 255.f;
			    // - Blue and alpha stay constant
			    pixels[pw+2] = pixels[pw+3] = 255;
            } else {
                pixels[pw] = 15;
                pixels[pw + 1] = 17;
                pixels[pw + 2] = 15;
            }
            
        }
    }
}

void random_triangles() {
    for (uint i = 0; i < N; i++) {
        vec3 r0 = {random_float(), random_float(), random_float()};
        vec3 r1 = {random_float(), random_float(), random_float()};
        vec3 r2 = {random_float(), random_float(), random_float()};
        tris[i].vertex0[0] = r0[0] * 9 - 5;
        tris[i].vertex0[1] = r0[1] * 9 - 5;
        tris[i].vertex0[2] = r0[2] * 9 - 5;

        tris[i].vertex1[0] = tris[i].vertex0[0] + r1[0];
        tris[i].vertex1[1] = tris[i].vertex0[1] + r1[1];
        tris[i].vertex1[2] = tris[i].vertex0[2] + r1[2];

        tris[i].vertex2[0] = tris[i].vertex0[0] + r2[0];
        tris[i].vertex2[1] = tris[i].vertex0[1] + r2[1];
        tris[i].vertex2[2] = tris[i].vertex0[2] + r2[2];
    }
}

int main(void) {
    printf("the code is load");
    

    renderer render = renderer_init(WIDTH,HEIGHT,"BVH demonstration", 100.f);

   
    texbuf = mu_gobjects_create(render.gfx, MUG_OBJECT_TEXTURE_2D, 1, &texrect);
    mu_gobjects_texture(render.gfx,texbuf,tex);

    

    while (!renderer_should_close(&render)) {
        if (render.keyboard[MU_KEYBOARD_ESCAPE]) {
            renderer_close(&render);
            continue;
        }

        renderer_clear(&render);

        // do stuff
        random_triangles();
        calc_pixel();
        
        tex = mu_gtexture_create(render.gfx, &texinfo, dim, (muByte*)pixels);

        mu_gobjects_fill(render.gfx, texbuf, &texrect);
        mu_gobjects_render(render.gfx, texbuf);

        renderer_update(&render);
        mu_gtexture_destroy(render.gfx, tex);
    }
    // clean up
    texbuf = mu_gobjects_destroy(render.gfx, texbuf);
    mu_gtexture_destroy(render.gfx, tex);


    renderer_destroy(&render);

    return 0;
}

