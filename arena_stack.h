#ifndef ARENA_STACK_H
#define ARENA_STACK_H

#include <stdint.h>

#define U64 uint64_t
#define U32 uint32_t
#define U16 uint16_t
#define U8 uint8_t
#define I64 int64_t
#define I32 int32_t


typedef struct {
    U64 cap;
    U8 *buf;
    U64 pos;
    U64 align;
} Arena;

Arena *ArenaAlloc(U64 cap);
void ArenaRelease(Arena *arena);
void ArenaSetAutoAlign(Arena *arena, U64 align);

U64 ArenaPos(Arena *arena);

void *ArenaPushNoZero(Arena *arena, U64 size);
void *ArenaPushAligner(Arena *arena, U64 size);
void *ArenaPush(Arena *arena, U64 size);

void ArenaPop(Arena *arena, U64 size);

#endif
