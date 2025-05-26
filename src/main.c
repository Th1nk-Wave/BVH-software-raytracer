#include <stdio.h>


#include "defines.h"
#include "triangle.h"
#include "rng.h"
#include "renderer.h"

#define N 64



triangle tris[N];

int main(void) {
    printf("the code is load");
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


    renderer render = renderer_init(800,600,"BVH demonstration", 100.f);

    while (!renderer_should_close(&render)) {
        if (render.keyboard[MU_KEYBOARD_ESCAPE]) {
            renderer_close(&render);
            continue;
        }

        renderer_clear(&render);

        // do stuff

        renderer_update(&render);
    }
    // clean up
    renderer_destroy(&render);

    return 0;
}

