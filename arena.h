#ifndef ARENA
#define ARENA
#include <stdint.h>
#include <stdlib.h>

typedef struct Arena{
	uint8_t *base;
	size_t size;
	size_t offset;
}Arena;

Arena arena_create(size_t size);
void *arena_alloc(Arena *arena, size_t size);
void arena_free(Arena *arena);
#endif
