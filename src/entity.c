#include <stdio.h>
#include <math.h>

#include "common.h"
#include "util.h"
#include "component.h"
#include "entity.h"

#define PLAYER_HEALTH 3
#define PLAYER_SPEED 300.0f
#define PLAYER_ACC 30.0f
#define PLAYER_FRIC 3.0f

extern Input *input;

Entity entity_create(EntityType type)
{
  Entity entity;
  entity.type = type;
  entity.move_state = EntityState_Idle;
  entity.pos = V2F_ZERO;
  entity.vel = V2F_ZERO;
  entity.dir = V2F_ZERO;
  entity.is_active = TRUE;
  entity.hurt_cooldown.max_duration = 1.0f;
  entity.hurt_cooldown.is_running = FALSE;
  entity.hurt_cooldown.should_tick = FALSE;

  switch (type)
  {
    case EntityType_Player:
    {
      entity.color = COLOR_WHITE;
      entity.width = 20.0f;
      entity.height = 20.0f;
      entity.speed = PLAYER_SPEED;
      entity.health = PLAYER_HEALTH;
      break;
    }
    case EntityType_Enemy:
    {
      entity.color = COLOR_RED;
      entity.width = 20.0f;
      entity.height = 20.0f;
      entity.speed = 100.0f;
      entity.view_dist = 250;
      break;
    }
    default: break;
  }

  return entity;
}

void entity_start(Entity *entity)
{
  switch (entity->type)
  {
    case EntityType_Player:
    {
      entity->pos = v2f32(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 2.0f);
      break;
    }
    case EntityType_Enemy:
    {
      entity->pos = random_position(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
      break;
    }
    default: break;
  }
}

void entity_update(Entity *entity, f64 dt)
{
  if (!entity->is_active)
  {
    entity->dir = V2F_ZERO;
    return;
  }

  switch (entity->type)
  {
    case EntityType_Player:
    {
      if (input->a)
      {
        entity->dir.x = -1.0f;
      }

      if (input->d)
      {
        entity->dir.x = 1.0f;
      }

      if (input->w)
      {
        entity->dir.y = -1.0f;
      }

      if (input->s)
      {
        entity->dir.y = 1.0f;
      }

      if ((!input->a && !input->d) || (input->a && input->d))
      {
        entity->dir.x = 0.0f;
      }

      if ((!input->w && !input->s) || (input->w && input->s))
      {
        entity->dir.y = 0.0f;
      }
      break;
    }
    case EntityType_Enemy:
    {
      if (entity->has_target && entity->is_active)
      {
        entity->dir.x = sinf(entity->target_angle);
        entity->dir.y = cosf(entity->target_angle);
      }
      else
      {
        entity->dir = V2F_ZERO;
      }

      break;
    }
    default: break;
  }

  if (entity->dir.x != 0.0f || entity->dir.y != 0.0f)
  {
    entity->dir = normalize_v2f32(entity->dir);
  }

  if (entity->dir.x != 0.0f)
  {
    entity->vel.x += PLAYER_ACC * entity->dir.x * dt;
    entity->vel.x = clamp(
                          entity->vel.x, 
                         -entity->speed * abs(entity->dir.x) * dt, 
                          entity->speed * abs(entity->dir.x) * dt);
  }
  else
  {
    entity->vel.x = lerp_f32(entity->vel.x, 0.0f, PLAYER_FRIC * dt);
    entity->vel.x = to_zero(entity->vel.x, 0.1f);
  }

  if (entity->dir.y != 0.0f)
  {
    entity->vel.y += PLAYER_ACC * entity->dir.y * dt;
    entity->vel.y = clamp(
                          entity->vel.y, 
                         -entity->speed * abs(entity->dir.y) * dt, 
                          entity->speed * abs(entity->dir.y) * dt);
  }
  else 
  {
    entity->vel.y = lerp_f32(entity->vel.y, 0.0f, PLAYER_FRIC * dt);
    entity->vel.y = to_zero(entity->vel.y, 0.1f);
  }

  // log_f32("DirX: ", entity->dir.x);
  // log_f32("DirY: ", entity->dir.y);
  // log_f32("VelX: ", entity->vel.x);
  // log_f32("VelY: ", entity->vel.y);

  entity->pos = add_v2f32(entity->pos, entity->vel);
}

void entity_set_target(Entity *entity, Vec2F32 target_pos)
{
  if (distance_v2f32(entity->pos, target_pos) <= entity->view_dist)
  {
    entity->has_target = TRUE;
    entity->target_pos = target_pos;

    f32 dist_x = entity->target_pos.x - entity->pos.x;
    f32 dist_y = entity->target_pos.y - entity->pos.y;
    
    entity->target_angle = atan2(dist_x, dist_y);
  }
  else
  {
    entity->has_target = FALSE;
    entity->target_pos = V2F_ZERO;
  }
}

void entity_deal_damage(Entity *target)
{
  target->health -= 1;

  if (target->health <= 0)
  {
    target->health = 0;
    target->is_active = FALSE;
    log_msg("Player ded");
  }
}