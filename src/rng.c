#include "rng.h"

// RNG - Marsaglia's xor32
static uint seed = 0x12345678;
uint random_uint() {
    seed ^= seed << 13;
	seed ^= seed >> 17;
	seed ^= seed << 5;
	return seed;
}

float random_float() {
    return random_uint() * 2.3283064365387e-10f;
}