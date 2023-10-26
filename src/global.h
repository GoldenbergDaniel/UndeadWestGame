#pragma once

#include "base/base_common.h"
#include "base/base_math.h"
#include "gfx/draw.h"

// @Input ======================================================================================

typedef enum Key
{
  KEY_A,
  KEY_D,
  KEY_S,
  KEY_W,
  KEY_SPACE,
  KEY_ESCAPE,
} Key;

typedef struct Input Input;
struct Input
{
  u8 key_down[6];
  u8 key_just_down[6];
  u8 key_just_up[6];
  Vec2I mouse_pos;
};

bool key_pressed(Key key);
bool key_just_pressed(Key key);
bool key_just_released(Key key);
Vec2I mouse_position(void);
void clear_last_frames_input(void);

// @Global =====================================================================================

typedef struct Global Global;
struct Global
{
  Input *input;
  D_Renderer *renderer;
};