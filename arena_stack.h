#ifndef ARENA_STACK_H
#define ARENA_STACK_H

#define U64 unsigned long long
#define U32 unsigned int
#define U16 unsigned short
#define U8 unsigned char
#define I64 long long
#define I32 int


typedef struct {
    U64 cap;
    U8 *buf;
    U64 pos;
    U64 align;
} Arena;

Arena *ArenaAlloc(U64 cap);
void ArenaRelease(Arena *arena);
void ArenaSetAutoAlign(Arena *arena, U64 align);

void *ArenaPush(Arena *arena, U64 size);

void ArenaPop(Arena *arena, U64 size);

#endif
