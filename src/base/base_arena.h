#pragma once

#include "base_common.h"

#define KiB(bytes) ((u64) bytes << 10)
#define MiB(bytes) ((u64) bytes << 20)
#define GiB(bytes) ((u64) bytes << 30)

// @Arena ////////////////////////////////////////////////////////////////////////////////

typedef struct Arena Arena;
struct Arena
{
  u64 size;
  byte *memory;
  u8 *allocated;
  u8 *committed;
  u8 id;
  bool decommit_on_clear;
};

#define arena_push(arena, T, count) (T *) _arena_push(arena, size_of(T) * count, align_of(T))

Arena create_arena(u64 size, bool decommit_on_clear);
void destroy_arena(Arena *arena);
byte *_arena_push(Arena *arena, u64 size, u64 align);
void arena_pop(Arena *arena, u64 size);
void arena_clear(Arena *arena);

void init_scratch_arenas(void);
Arena get_scratch_arena(Arena *conflict);

byte *align_ptr(u8 *ptr, u32 align);
