#include <stdio.h>

#include "arena_stack.h"

int main() {
  Arena *arena = ArenaAlloc(32);
  ArenaSetAutoAlign(arena, sizeof(int));

  void *temp = ArenaPush(arena, sizeof(int));
  if (!temp) {
      ArenaRelease(arena);
      return 1;
  }
  *(int *)temp = 2;

  printf("Value: %d\n", *(int *)temp);

  ArenaPop(arena, sizeof(int));
  ArenaRelease(arena);

  return 0;
}
