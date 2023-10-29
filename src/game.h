#pragma once

#include "base/base_common.h"
#include "base/base_arena.h"
#include "gfx/draw.h"
#include "input.h"
#include "event.h"
#include "entity.h"

#define TARGET_FPS 60

#define VSYNC_AUTO -1
#define VSYNC_OFF 0
#define VSYNC_ON 1

#define W_WIDTH 1024
#define W_HEIGHT 640

#define COLOR_BLACK ((Vec4F) {0.01f, 0.01f, 0.01f, 1.0f})
#define COLOR_WHITE ((Vec4F) {0.9f, 0.9f, 0.9f, 1.0f})
#define COLOR_RED ((Vec4F) {0.9f, 0.2f, 0.1f, 1.0f})
#define COLOR_GREEN ((Vec4F) {0.3f, 0.9f, 0.2f, 1.0f})
#define COLOR_BLUE ((Vec4F) {0.1f, 0.4f, 0.8f, 1.0f})
#define COLOR_YELLOW ((Vec4F) {0.9f, 0.8f, 0.0f, 1.0f})

typedef union SDL_Event SDL_Event;

typedef struct Game Game;
struct Game
{
  Arena arena;
  EventQueue event_queue;
  EntityList entities;
  Mat3x3F camera;
  bool running;
  bool should_quit;
  bool first_frame;
  f64 t;
  f64 dt;
};

typedef struct Global Global;
struct Global
{
  Input *input;
  D_Renderer *renderer;
};

void init(Game *game);
void update(Game *game);
void handle_events(Game *game);
void draw(Game *game);
bool should_quit(Game *game);
