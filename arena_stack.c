#include <malloc/_malloc.h>
#include <stdio.h>
#include <stdlib.h>

#include "arena_stack.h"

Arena *ArenaAlloc(U64 cap) {
  Arena *arena = (Arena *)malloc(sizeof(Arena));
  if (!arena) {
    printf("Error: Failed to allocate arena\n");
    return NULL;
  }

  arena->cap = cap;
  arena->buf = (U8 *)malloc(cap * sizeof(U8));
  arena->pos = 0;
  arena->align = 1;

  if (!arena->buf) {
    printf("Error: Failed to allocate arena buffer\n");
    free(arena);
    return NULL;
  }

  return arena;
}

void ArenaRelease(Arena *arena) {
  free(arena->buf);
  free(arena);
}

void ArenaSetAutoAlign(Arena *arena, U64 align) {
  // If you need the entire buffer to be aligned (not just individual
  // allocations), use posix_memalign or _aligned_malloc, (so to not have to do
  // the calculations manually i think?)

  if (align == 0 || (align & (align - 1)) != 0) {
    printf("Error: Alignment must be a power of two\n");
    return;
  }

  arena->align = align;
}

U64 ArenaPos(Arena *arena) { return arena->pos; }

void *ArenaPush(Arena *arena, U64 size) {
  U64 aligned_pos = (arena->pos + arena->align - 1) & ~(arena->align - 1);

  if (aligned_pos + size > arena->cap) {
    printf("Error: reached cap");
    return NULL;
  }

  arena->pos = aligned_pos + size;

  return (void *)(arena->buf + aligned_pos);
}

void ArenaPop(Arena *arena, U64 size) { arena->pos -= size; }
