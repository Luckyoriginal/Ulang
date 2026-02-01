#include "arena.h"
#include <stdlib.h>

Arena arena_create(size_t size) {
    Arena arena;
    arena.base = malloc(size);
    arena.size = size;
    arena.offset = 0;
    return arena;
}

void *arena_alloc(Arena *arena, size_t size) {
    size = (size + 7) & ~7; // align to 8 bytes

    if (arena->offset + size > arena->size) {
        return NULL; // out of memory
    }

    void *ptr = arena->base + arena->offset;
    arena->offset += size;
    return ptr;
}

void arena_free(Arena *arena) {
    free(arena->base);
}
