#include <SDL2/SDL.h>

#include "base/base_common.h"

#include "input.h"
#include "game.h"

Global *GLOBAL;

static void set_gl_attributes(void);

i32 main(void)
{
  Game game = {0};
  game.arena = arena_create(MEGABYTES(16));

  srand(time(NULL));
  SDL_InitSubSystem(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
  set_gl_attributes();

  SDL_Window *window = SDL_CreateWindow(
                                        "SPACE GAME",
                                        SDL_WINDOWPOS_CENTERED, 
                                        SDL_WINDOWPOS_CENTERED, 
                                        W_WIDTH, 
                                        W_HEIGHT, 
                                        SDL_WINDOW_OPENGL);

  SDL_GLContext gl_context = SDL_GL_CreateContext(window);
  SDL_GL_MakeCurrent(window, gl_context);
  SDL_GL_SetSwapInterval(VSYNC_ON);

  if (!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress))
  {
    printf("GLAD failed to load!\n");
    return 1;
  }

  GLOBAL = arena_alloc(&game.arena, sizeof (Global));
  GLOBAL->input = arena_alloc(&game.arena, sizeof (Input));
  GLOBAL->renderer = arena_alloc(&game.arena, sizeof (*GLOBAL->renderer));
  d_init_renderer(GLOBAL->renderer);

  init(&game);

  f64 elapsed_time = 0.0f;
  f64 current_time = SDL_GetTicks64() * 0.001f;
  f64 time_step = 1.0f / TARGET_FPS;
  f64 accumulator = 0.0f;

  while (game.running)
  {
    f64 new_time = SDL_GetTicks64() * 0.001f;
    f64 frame_time = new_time - current_time;
    current_time = new_time;
    accumulator += frame_time;

    while (accumulator >= time_step)
    {
      clear_last_frame_input();

      SDL_Event event;
      while (SDL_PollEvent(&event))
      {
        handle_input(&event, &game.should_quit);
      }

      if (should_quit(&game))
      {
        game.running = FALSE;
      }

      if (!game.first_frame)
      {
        game.t = elapsed_time;
        game.dt = time_step;

        update(&game);
        handle_events(&game);
      }

      elapsed_time += time_step;
      accumulator -= time_step;

      game.first_frame = FALSE;
    }

    draw(&game);
    SDL_GL_SwapWindow(window);
  }

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}

static
void set_gl_attributes(void)
{
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 0);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
}
