#include <stdio.h>

#include "base/base.h"
#include "vecmath/vecmath.h"
#include "physics/physics.h"
#include "draw.h"
#include "game.h"
#include "prefabs.h"
#include "entity.h"
#include "game.h"

extern Globals global;
extern Prefabs prefab;
extern Game game;

// @SpawnKillEntity //////////////////////////////////////////////////////////////////////

Entity *create_entity(EntityType type)
{
  Entity *en = alloc_entity();
  en->type = type;
  en->is_active = TRUE;
  en->xform = m3x3f(1.0f);
  en->dim = v2f(16, 16);
  en->scale = v2f(1, 1);
  en->tint = v4f(1.0f, 1.0f, 1.0f, 1.0f);

  switch (type)
  {
  case EntityType_Debug:
    en->draw_type = DrawType_Primitive;
    en->scale = v2f(1/16.0f, 1/16.0f);
    en->tint = DEBUG_YELLOW;
    break;
  case EntityType_Player:
    en->props = EntityProp_Renders | 
                EntityProp_Collides | 
                EntityProp_Controlled | 
                EntityProp_Moves | 
                EntityProp_AffectedByGravity |
                EntityProp_CollidesWithGround;
    en->draw_type = DrawType_Sprite;
    en->move_type = MoveType_Grounded;
    en->combat_type = CombatType_Ranged;
    en->speed = prefab.player_stat[EntityGender_Male].speed;
    en->sprite = prefab.sprite.player_male_idle;
    en->scale = v2f(SPRITE_SCALE, SPRITE_SCALE);
    en->health = prefab.player_stat[EntityGender_Male].health;
    en->invincibility_timer.duration = PLAYER_INVINCIBILITY_TIMER;

    en->anim_descriptors = prefab.animation.player_male;

    entity_add_collider(en, Collider_Body);
    en->cols[Collider_Body]->col_type = P_ColliderType_Rect;
    en->cols[Collider_Body]->pos = v2f(0, 0);
    en->cols[Collider_Body]->scale = v2f(0.5, 1);
    break;
  case EntityType_Zombie:
    en->props = EntityProp_Renders | 
                EntityProp_Moves | 
                EntityProp_Collides |
                EntityProp_AffectedByGravity |
                EntityProp_CollidesWithGround |
                EntityProp_LookAtPlayer;
    en->draw_type = DrawType_Sprite;
    en->scale = v2f(SPRITE_SCALE, SPRITE_SCALE);
    break;
  case EntityType_Equipped:
    en->props = EntityProp_Equipped;
    en->draw_type = DrawType_Sprite;
    break;
  case EntityType_Ammo:
    en->props = EntityProp_Renders | 
                EntityProp_Moves | 
                EntityProp_Collides |
                EntityProp_KillAfterTime;
    
    en->draw_type = DrawType_Sprite;
    en->move_type = MoveType_Projectile;
    en->kill_timer.duration = BULLET_KILL_TIME;
    en->scale = v2f(SPRITE_SCALE, SPRITE_SCALE);

    entity_add_collider(en, Collider_Hit);
    en->cols[Collider_Hit]->col_id = Collider_Hit;
    en->cols[Collider_Hit]->col_type = P_ColliderType_Circle;
    en->cols[Collider_Hit]->radius = 1;
    en->cols[Collider_Hit]->draw_type = DrawType_Nil;
    en->cols[Collider_Hit]->dim = V2F_ZERO;
    break;
  case EntityType_Collider:
    en->props = EntityProp_Collides |
                EntityProp_Renders;
    en->draw_type = DrawType_Primitive;
    break;
  case EntityType_Decoration:
    en->props = EntityProp_Renders;
    en->draw_type = DrawType_Sprite;
    break;
  case EntityType_Collectable:
    en->props = EntityProp_Renders |
                EntityProp_BobsOverTime |
                EntityProp_Collides;

    en->draw_type = DrawType_Sprite;
    en->scale = v2f(SPRITE_SCALE, SPRITE_SCALE);

    entity_add_collider(en, Collider_Hit);
    en->cols[Collider_Hit]->col_id = Collider_Hit;
    en->cols[Collider_Hit]->col_type = P_ColliderType_Circle;
    en->cols[Collider_Hit]->radius = 10;
    en->cols[Collider_Hit]->draw_type = DrawType_Nil;
    en->cols[Collider_Hit]->dim = V2F_ZERO;
    break;
  case EntityType_Egg:
    en->props = EntityProp_Renders;
    en->draw_type = DrawType_Sprite;
    en->sprite = prefab.sprite.egg_0;
    en->scale = v2f(SPRITE_SCALE, SPRITE_SCALE);
    break;
  case EntityType_Shockwave:
    en->props = EntityProp_Renders |
                EntityProp_KillAfterTime |
                EntityProp_Moves;
    en->draw_type = DrawType_Sprite;
    en->sprite = prefab.sprite.egg_0;
    en->scale = v2f(SPRITE_SCALE, SPRITE_SCALE);
    en->state = EntityState_Idle;
    en->anim_descriptors = prefab.animation.shockwave;
    break;
  case EntityType_Merchant:
    en->props = EntityProp_Renders;
    en->draw_type = DrawType_Sprite;
    en->sprite = prefab.sprite.wagon_left;
    en->dim = v2f(16 * 4, 16 * 2);
    en->scale = v2f(SPRITE_SCALE, SPRITE_SCALE);
    break;
  default: break;
  }

  return en;
}

Entity *spawn_entity(EntityType type, Vec2F pos)
{
  Entity *en = create_entity(type);
  en->pos = pos;

  entity_rem_prop(en, EntityProp_Renders);
  en->is_active = FALSE;
  en->marked_for_spawn = TRUE;

  return en;
}

Entity *spawn_ammo(AmmoKind kind, Vec2F pos)
{
  Entity *en = create_entity(EntityType_Ammo);
  en->pos = pos;

  switch (kind)
  {
  case AmmoKind_Nil: 
    break;
  case AmmoKind_Bullet:
    en->sprite = prefab.sprite.bullet;
    break;
  case AmmoKind_Pellet:
    en->sprite = prefab.sprite.pellet;
    break;
  case AmmoKind_Laser:
    en->sprite = prefab.sprite.laser;
    break;
  }

  en->is_active = FALSE;
  en->marked_for_spawn = TRUE;
  entity_rem_prop(en, EntityProp_Renders);

  return en;
}

Entity *spawn_zombie(ZombieKind kind, Vec2F pos)
{
  Entity *en = create_entity(EntityType_Zombie);
  en->pos = pos;
  en->zombie_kind = kind;

  ZombieDesc desc = prefab.zombie[kind];
  en->props |= desc.props;
  en->move_type = desc.move_type;
  en->combat_type = desc.combat_type;
  en->health = desc.health;
  en->damage = desc.damage;
  en->speed = desc.speed;
  en->view_dist = 350.0f;
  en->attack_timer.duration = desc.attack_cooldown;

  switch (kind)
  {
  default: break;
  case ZombieKind_Walker:
    en->sprite = prefab.sprite.walker_idle;
    en->anim_descriptors = prefab.animation.zombie_walker;
    en->stop_dist = 40.0f;

    entity_add_collider(en, Collider_Body);
    en->cols[Collider_Body]->col_type = P_ColliderType_Rect;
    en->cols[Collider_Body]->pos = v2f(0, 0);
    en->cols[Collider_Body]->scale = v2f(0.5, 1);

    entity_add_collider(en, Collider_Hit);
    en->cols[Collider_Hit]->col_type = P_ColliderType_Rect;
    en->cols[Collider_Hit]->pos = v2f(en->dim.width, 0);
    en->cols[Collider_Hit]->scale = v2f(0.25, 0.5);

    break;
  case ZombieKind_Chicken:
    en->dim = v2f(16, 16);
    en->sprite = prefab.sprite.chicken_idle_0;
    en->anim_descriptors = prefab.animation.zombie_chicken;
    en->stop_dist = 40.0f;

    entity_add_collider(en, Collider_Body);
    en->cols[Collider_Body]->col_type = P_ColliderType_Rect;
    en->cols[Collider_Body]->pos = v2f(0, -4 * SPRITE_SCALE);
    en->cols[Collider_Body]->scale = v2f(0.5, 0.5);

    entity_add_collider(en, Collider_Hit);
    en->cols[Collider_Hit]->col_type = P_ColliderType_Rect;
    en->cols[Collider_Hit]->pos = v2f(20, -4 * SPRITE_SCALE);
    en->cols[Collider_Hit]->scale = v2f(0.2, 0.2);

    break;
  case ZombieKind_BabyChicken:
    en->dim = v2f(16, 16);
    en->sprite = prefab.sprite.baby_chicken_idle;
    en->anim_descriptors = prefab.animation.zombie_baby_chicken;
    en->stop_dist = 40.0f;

    entity_add_collider(en, Collider_Body);
    en->cols[Collider_Body]->col_type = P_ColliderType_Rect;
    en->cols[Collider_Body]->pos = v2f(0, -4 * SPRITE_SCALE);
    en->cols[Collider_Body]->scale = v2f(0.5, 0.5);

    entity_add_collider(en, Collider_Hit);
    en->cols[Collider_Hit]->col_type = P_ColliderType_Rect;
    en->cols[Collider_Hit]->pos = v2f(20, 0);
    en->cols[Collider_Hit]->scale = v2f(0.1, 0.1);
    
    break;
  case ZombieKind_Bloat:
    en->dim = v2f(16, 32);
    en->scale = v2f(SPRITE_SCALE, SPRITE_SCALE);
    en->sprite = prefab.sprite.bloat_idle;
    en->anim_descriptors = prefab.animation.zombie_bloat;
    en->stop_dist = 70.0f;

    entity_add_collider(en, Collider_Body);
    en->cols[Collider_Body]->col_type = P_ColliderType_Rect;
    en->cols[Collider_Body]->pos = v2f(0, -6 * SPRITE_SCALE);
    en->cols[Collider_Body]->scale = v2f(0.75, 1.25);

    entity_add_collider(en, Collider_Hit);
    en->cols[Collider_Hit]->col_type = P_ColliderType_Rect;
    en->cols[Collider_Hit]->pos = v2f(5 * SPRITE_SCALE, -4 * SPRITE_SCALE);
    en->cols[Collider_Hit]->scale = v2f(0.25, 0.5);

    break;
  }

  entity_rem_prop(en, EntityProp_Renders);
  en->is_active = FALSE;
  en->marked_for_spawn = TRUE;

  return en;
}

Entity *spawn_collectable(CollectableKind kind, Vec2F pos)
{
  CollectableDesc desc = prefab.collectable[kind];

  Entity *en = create_entity(EntityType_Collectable);
  en->pos = pos;
  en->item_kind = kind;
  en->sprite = desc.sprite;
  en->bobbing.range = v2f(en->pos.y - 5, en->pos.y + 5);
  en->bobbing.state = -1;

  entity_rem_prop(en, EntityProp_Renders);
  en->is_active = FALSE;
  en->marked_for_spawn = TRUE;

  return en;
}

Entity *spawn_particles(ParticleKind kind, Vec2F pos)
{
  Entity *en = create_entity(EntityType_Any);
  en->pos = pos;

  ParticleDesc desc = prefab.particle[kind];
  en->particle_desc = desc;

  for (u32 i = 0; i < en->particle_desc.count; i++)
  {
    Particle *particle = get_next_free_particle();
    particle->is_active = TRUE;
    particle->pos = en->pos;
    particle->scale = desc.scale;
    particle->dir = (f32) random_i32(-en->particle_desc.spread, en->particle_desc.spread);
    particle->rot = (f32) random_i32(-45, 45);
    particle->color = desc.color_primary;
    particle->vel = desc.vel;
    particle->speed = desc.speed;
    particle->owner = ref_from_entity(en);
  }

  return en;
}

Entity *spawn_merchant(void)
{
  Entity *en = create_entity(EntityType_Merchant);
  en->spid = SPID_Merchant;
  en->pos = v2f(WIDTH/2, GROUND_Y+80);
  en->state = EntityState_MerchantComing;
  en->scale = V2F_ZERO;

  Entity *slot_0 = create_entity(EntityType_Decoration);
  slot_0->merchant_slot.kind = MerchantSlotKind_Weapon;
  slot_0->pos = v2f(SPRITE_SCALE * -19, SPRITE_SCALE * 3);
  slot_0->sprite = prefab.sprite.ui_slot_coin_empty;
  attach_entity_child(en, slot_0);
  
  Entity *weapon_deco = create_entity(EntityType_Decoration);
  attach_entity_child(slot_0, weapon_deco);
  slot_populate_weapon(slot_0);
  entity_rem_prop(slot_0, EntityProp_Renders);
  entity_rem_prop(weapon_deco, EntityProp_Renders);
  weapon_deco->is_active = TRUE;

  Entity *slot_1 = create_entity(EntityType_Decoration);
  slot_1->merchant_slot.kind = MerchantSlotKind_Coin;
  slot_1->pos = v2f(SPRITE_SCALE * -8, SPRITE_SCALE * 3);
  slot_1->sprite = prefab.sprite.ui_slot_coin_ammo;
  attach_entity_child(en, slot_1);
  slot_populate_ammo(slot_1);
  entity_rem_prop(slot_1, EntityProp_Renders);

  Entity *slot_2 = create_entity(EntityType_Decoration);
  slot_2->merchant_slot.kind = MerchantSlotKind_Powerup;
  slot_2->pos = v2f(SPRITE_SCALE * 15, SPRITE_SCALE * 3);
  slot_2->sprite = prefab.sprite.ui_slot_soul_heal;
  attach_entity_child(en, slot_2);
  slot_populate_powerup(slot_2);
  entity_rem_prop(slot_2, EntityProp_Renders);

  return en;
}

void kill_entity(Entity *en, bool slain)
{
  en->marked_for_death = TRUE;

  push_event(EventType_EntityKilled, (EventDesc) {
    .en=en, 
    .type=en->type, 
    .slain = slain
  });
}

// @GeneralEntity ////////////////////////////////////////////////////////////////////////

inline
bool entity_has_prop(Entity *en, EntityProp prop)
{
  return (en->props & prop) != 0;
}

inline
void entity_add_prop(Entity *en, EntityProp prop)
{
  en->props |= prop;
}

inline
void entity_rem_prop(Entity *en, EntityProp prop)
{
  en->props &= ~prop;
}

Vec2F pos_from_entity(Entity *en)
{
  Mat3x3F mat = en->model_mat;

  Entity *parent = entity_from_ref(en->parent);
  while (entity_is_valid(parent))
  {
    mat = mul_3x3f(parent->model_mat, mat);
    parent = entity_from_ref(parent->parent);
  }

  return v2f(mat.e[0][2], mat.e[1][2]);
}

Vec2F pos_tl_from_entity(Entity *en)
{
  Vec2F result = pos_from_entity(en);
  Vec2F dim = dim_from_entity(en);
  Vec2F offset = scale_2f(dim, 0.5f);
  result.x -= offset.x;
  result.y += offset.y;

  return result;
}

Vec2F pos_tr_from_entity(Entity *en)
{
  Vec2F result = pos_from_entity(en);
  Vec2F dim = dim_from_entity(en);
  Vec2F offset = scale_2f(dim, 0.5f);
  result.x += offset.x;
  result.y += offset.y;

  return result;
}

Vec2F pos_bl_from_entity(Entity *en)
{
  Vec2F result = pos_from_entity(en);
  Vec2F dim = dim_from_entity(en);
  Vec2F offset = scale_2f(dim, 0.5f);
  result.x -= offset.x;
  result.y -= offset.y;

  return result;
}

Vec2F pos_br_from_entity(Entity *en)
{
  Vec2F result = pos_from_entity(en);
  Vec2F dim = dim_from_entity(en);
  Vec2F offset = scale_2f(dim, 0.5f);
  result.x += offset.x;
  result.y -= offset.y;

  return result;
}

Vec2F dim_from_entity(Entity *en)
{
  Vec2F result = en->dim;
  result = mul_2f(result, en->scale);

  Entity *parent = entity_from_ref(en->parent);
  while (entity_is_valid(parent))
  {
    result = mul_2f(result, parent->scale);
    parent = entity_from_ref(parent->parent);
  }

  return result;
}

Vec2F scale_from_entity(Entity *en)
{
  Vec2F result = en->scale;

  Entity *parent = entity_from_ref(en->parent);
  while (entity_is_valid(parent))
  {
    result = mul_2f(result, parent->scale);
    parent = entity_from_ref(parent->parent);
  }

  return result;
}

f32 rot_from_entity(Entity *en)
{
  f32 result = en->rot;

  Entity *parent = entity_from_ref(en->parent);
  while (entity_is_valid(parent))
  {
    result += parent->rot;
    parent = entity_from_ref(parent->parent);
  }

  return result;
}

bool flip_x_from_entity(Entity *en)
{
  bool result = en->flip_x;

  Entity *parent = entity_from_ref(en->parent);
  while (entity_is_valid(parent))
  {
    result = parent->flip_x ? !result : result;
    parent = entity_from_ref(parent->parent);
  }

  return result;
}

bool flip_y_from_entity(Entity *en)
{
  bool result = en->flip_y;

  Entity *parent = entity_from_ref(en->parent);
  while (entity_is_valid(parent))
  {
    result = parent->flip_y ? !result : result;
    parent = entity_from_ref(parent->parent);
  }

  return result;
}

void entity_look_at(Entity *en, Vec2F target_pos)
{
  Vec2F entity_pos = pos_from_entity(en);
  en->flip_x = entity_pos.x > target_pos.x ? TRUE : FALSE;
}

void entity_set_target(Entity *en, EntityRef target)
{
  Entity *target_entity = entity_from_ref(target);
  Vec2F target_pos = pos_from_entity(target_entity);

  if (distance_2f(en->pos, target_pos) <= en->view_dist)
  {
    Vec2F diff = v2f(target_pos.x - en->pos.x, target_pos.y - en->pos.y);
    en->target_angle = atan_2f(diff);
    en->has_target = TRUE;
  }
  else
  {
    en->target_pos = V2F_ZERO;
    en->has_target = FALSE;
  }
}

inline
bool entity_is_valid(Entity *en)
{
  return (en != NULL && en->type != EntityType_Nil);
}

void damage_entity(Entity *reciever, i16 damage)
{
  if (reciever->health <= 0) return;

  reciever->health -= damage;

  if (damage != 0)
  {
    entity_add_prop(reciever, EntityProp_FlashWhite);
  }

  if (reciever->health <= 0)
  {
    spawn_particles(ParticleKind_Death, pos_from_entity(reciever));
    kill_entity(reciever, TRUE);
  }
}

// @EntityRef ////////////////////////////////////////////////////////////////////////////

inline
EntityRef ref_from_entity(Entity *en)
{
  return (EntityRef) {
    .ptr = en,
    .id = en->id
  };
}

inline
Entity *entity_from_ref(EntityRef ref)
{
  Entity *result = NIL_ENTITY;

  if (entity_is_valid(ref.ptr) && ref.ptr->id == ref.id && !ref.ptr->marked_for_death)
  {
    result = ref.ptr;
  }

  return result;
}

// @EntityList ///////////////////////////////////////////////////////////////////////////

Entity *alloc_entity(void)
{
  EntityList *list = &game.entities;
  Entity *new_en = list->first_free;

  if (new_en == NULL)
  {
    new_en = arena_push(&game.entity_arena, Entity, 1);
    zero(*new_en, Entity);

    new_en->children = arena_push(&game.entity_arena, EntityRef, MAX_ENTITY_CHILDREN);
    new_en->free_child_list = arena_push(&game.entity_arena, i16, MAX_ENTITY_CHILDREN);

    // Reset entity children
    for (u16 i = 0; i < MAX_ENTITY_CHILDREN; i++)
    {
      new_en->children[i].ptr = NIL_ENTITY;
      new_en->children[i].id = 0;
      new_en->free_child_list[i] = -1;
    }

    if (list->head == NULL)
    {
      list->head = new_en;
      list->tail = new_en;
    }

    new_en->next = NULL;
    list->tail->next = new_en;
    list->tail = new_en;
    list->count++;
  }
  else
  {
    list->first_free = list->first_free->next_free;
  }

  new_en->id = (u64) random_i32(2, UINT32_MAX-1);

  return new_en;
}

void free_entity(Entity *en)
{
  EntityList *list = &game.entities;

  // Reset entity
  // NOTE(dg): This is a load of crap.
  Entity *next = en->next;
  Entity *next_free = en->next_free;
  EntityRef *children = en->children;
  i16 *free_child_list = en->free_child_list;
  zero(*en, Entity);
  en->free_child_list = free_child_list;
  en->children = children;
  for (u16 i = 0; i < MAX_ENTITY_CHILDREN; i++)
  {
    en->children[i].ptr = NIL_ENTITY;
    en->children[i].id = 0;
    en->free_child_list[i] = -1;
  }
  en->next_free = next_free;
  en->next = next;

  en->next_free = list->first_free;
  list->first_free = en;
}

Entity *get_entity_by_id(u64 id)
{
  Entity *result = NIL_ENTITY;

  for (Entity *en = game.entities.head; en != NULL; en = en->next)
  {
    if (en->id == id)
    {
      result = en;
      break;
    }
  }

  return result;
}

Entity *get_entity_by_sp(u8 sp)
{
  Entity *result = NIL_ENTITY;

  for (Entity *en = game.entities.head; en != NULL; en = en->next)
  {
    if (en->spid == sp)
    {
      result = en;
      break;
    }
  }

  return result;
}

void attach_entity_child(Entity *en, Entity *child)
{
  assert(en->child_count <= MAX_ENTITY_CHILDREN);

  en->child_count++;

  if (en->free_child_count == 0)
  {
    for (u16 i = 0; i < en->child_count; i++)
    {
      Entity *slot = entity_from_ref(en->children[i]);
      if (!entity_is_valid(slot))
      {
        en->children[i] = ref_from_entity(child);
        break;
      }
    }
  }
  else
  {
    for (u16 i = 0; i < en->free_child_count; i++)
    {
      i16 slot = en->free_child_list[i];
      if (slot != -1)
      {
        en->children[slot] = ref_from_entity(child);
        en->free_child_list[i] = -1;
        en->free_child_count--;
        break;
      }
    }
  }

  child->parent = ref_from_entity(en);
}

void attach_entity_child_at(Entity *en, Entity *child, u16 index)
{ 
  EntityRef slot = en->children[index];
  if (!entity_is_valid(entity_from_ref(slot)))
  {
    slot = ref_from_entity(child);
    child->parent = ref_from_entity(en);
  }
}

void detach_entity_child(Entity *en, Entity *child)
{
  for (u16 i = 0; i < en->child_count; i++)
  {
    EntityRef *slot = &en->children[i];
    if (slot->id == child->id)
    {
      zero(*slot, EntityRef);

      if (i < en->child_count)
      {
        en->free_child_list[en->free_child_count] = i;
        en->free_child_count++;
      }

      en->child_count--;
      zero(child->parent, EntityRef);
      break;
    }
  }
}

inline
Entity *get_entity_child_at(Entity *en, u16 index)
{
  return entity_from_ref(en->children[index]);
}

Entity *get_entity_child_by_id(Entity *en, u64 id)
{
  Entity *result = NIL_ENTITY;

  for (u16 i = 0; i < MAX_ENTITY_CHILDREN; i++)
  {
    Entity *curr = entity_from_ref(en->children[i]);
    if (curr->id == id)
    {
      result = curr;
      break;
    }
  }

  return result;
}

Entity *get_entity_child_by_spid(Entity *en, u8 sp)
{
  Entity *result = NIL_ENTITY;

  for (u16 i = 0; i < MAX_ENTITY_CHILDREN; i++)
  {
    Entity *curr = entity_from_ref(en->children[i]);
    if (curr->spid == sp)
    {
      result = curr;
      break;
    }
  }

  return result;
}

Entity *get_entity_child_by_type(Entity *en, EntityType type)
{
  Entity *result = NIL_ENTITY;

  for (u16 i = 0; i < MAX_ENTITY_CHILDREN; i++)
  {
    Entity *curr = entity_from_ref(en->children[i]);
    if (curr->type == type)
    {
      result = curr;
      break;
    }
  }

  return result;
}

void entity_add_collider(Entity *en, ColliderID col_id)
{
  en->cols[col_id] = create_entity(EntityType_Collider);
  en->cols[col_id]->col_id = col_id;
  attach_entity_child(en, en->cols[col_id]);
}

// @Timer ////////////////////////////////////////////////////////////////////////////////

inline
void timer_start(Timer *timer, f64 duration)
{
  timer->end_time = game.t + duration;
  timer->ticking = TRUE;
}

inline
bool timer_timeout(Timer *timer)
{
  return timer->ticking && game.t >= timer->end_time;
}

inline
f64 timer_remaining(Timer *timer)
{
  return timer->end_time - game.t;
}

// @Misc /////////////////////////////////////////////////////////////////////////////////

inline
bool has_prop(b64 props, u64 prop)
{
  return (props & prop) != 0;
}

P_CollisionParams collision_params_from_entity(Entity *en, Vec2F vel)
{
  if (en == NULL) assert(0);

  P_CollisionParams result = {
    .type = en->col_type,
    .pos = pos_bl_from_entity(en),
    .dim = dim_from_entity(en),
    .vel = vel,
    .radius = en->radius,
  };

  return result;
}

void equip_weapon(Entity *en, WeaponKind kind)
{
  if (!entity_is_valid(en)) return;

  Entity *weapon_en = get_entity_child_by_spid(en, SPID_Gun);
  Entity *shot_point_en = get_entity_child_at(weapon_en, 0);

  if (kind == WeaponKind_Nil)
  {
    en->is_weapon_equipped = FALSE;
    Entity *gun = get_entity_child_by_spid(en, SPID_Gun);
    entity_rem_prop(gun, EntityProp_Renders);
    return;
  }
  else if (kind == WeaponKind_Revolver || kind == WeaponKind_LaserPistol)
  {
    game.weapon.unlimitted_ammo = TRUE;
  }
  else
  {
    game.weapon.unlimitted_ammo = FALSE;
  }

  WeaponDesc desc = prefab.weapon[kind];

  en->is_weapon_equipped = TRUE;
  en->attack_timer.duration = desc.shot_cooldown;

  weapon_en->sprite = desc.sprite;
  weapon_en->weapon_kind = kind;
  weapon_en->pos = desc.ancor;
  weapon_en->damage = desc.damage;
  weapon_en->speed = desc.bullet_speed;
  entity_add_prop(weapon_en, EntityProp_Renders);

  shot_point_en->pos = desc.shot_point;

  game.weapon.kind = kind;
  if (game.weapon.is_reloading)
  {
    weapon_cancel_reload();
  }
}

void entity_distort_x(Entity *en, f32 scale, f32 rate, f32 original)
{
  entity_add_prop(en, EntityProp_DistortScaleX);
  en->distort_x.state = 0;
  en->distort_x.rate = rate;
  en->distort_x.scale = scale;
  en->distort_x.saved = original;
}

void entity_distort_y(Entity *en, f32 scale, f32 rate, f32 original)
{
  entity_add_prop(en, EntityProp_DistortScaleY);
  en->distort_y.state = 0;
  en->distort_y.rate = rate;
  en->distort_y.scale = scale;
  en->distort_y.saved = original;
}

void entity_set_gender(Entity *en, EntityGender gender)
{
  if (en->type != EntityType_Player) return;

  en->speed = prefab.player_stat[gender].speed;
  en->health = prefab.player_stat[gender].health;

  if (gender == EntityGender_Male)
  {
    en->sprite = prefab.sprite.player_male_idle;
    en->anim_descriptors = prefab.animation.player_male;
    game.player_gender = EntityGender_Male;
  }
  else if (gender == EntityGender_Female)
  {
    en->sprite = prefab.sprite.player_female_idle;
    en->anim_descriptors = prefab.animation.player_female;
    game.player_gender = EntityGender_Female;
  }
}

bool entity_is_laying(Entity *en)
{
  return en->state == EntityState_LayEggBegin ||
         en->state == EntityState_LayEggLaying ||
         en->state == EntityState_LayEggEnd;
}

bool slot_purchase_item(Entity *slot)
{
  bool purchase_made = FALSE;

  if (slot->merchant_slot.kind == MerchantSlotKind_Weapon &&
      game.progression.weapon_unlocked[slot->merchant_slot.weapon_kind])
  {
    return FALSE;
  }

  if (slot->merchant_slot.purchased == TRUE) return FALSE;

  switch (slot->merchant_slot.kind)
  {
  case MerchantSlotKind_Weapon:
    if (game.coin_count >= slot->merchant_slot.price)
    {
      game.coin_count -= slot->merchant_slot.price;
      purchase_made = TRUE;
    }
  case MerchantSlotKind_Coin:
    if (game.coin_count >= slot->merchant_slot.price)
    {
      game.coin_count -= slot->merchant_slot.price;
      purchase_made = TRUE;
    }
  case MerchantSlotKind_Powerup:
    if (game.soul_count >= slot->merchant_slot.price)
    {
      game.soul_count -= slot->merchant_slot.price;
      purchase_made = TRUE;
    }
  }

  slot->merchant_slot.purchased = purchase_made;

  return purchase_made;
}

void slot_populate_weapon(Entity *slot)
{
  bool is_weapon_remaining = FALSE;
  for (i32 i = 1; i < WeaponKind_COUNT-1; i++)
  {
    if (game.progression.weapon_unlocked[i] == FALSE)
    {
      is_weapon_remaining = TRUE;
    }
  }

  if (!is_weapon_remaining) return;
  
  WeaponKind weapon_kind = WeaponKind_Nil;
  bool hit = FALSE;
  while (!hit)
  {
    i32 roll = random_i32(1, 100);
    i32 acc = 0;
    if (roll <= (acc += 10))
    {
      weapon_kind = WeaponKind_BurstRifle;
    }
    else if (roll <= (acc += 20))
    {
      weapon_kind = WeaponKind_Shotgun;
    }
    else if (roll <= (acc += 20))
    {
      weapon_kind = WeaponKind_SMG;
    }
    else
    {
      weapon_kind = WeaponKind_Rifle;
    }

    if (!game.progression.weapon_unlocked[weapon_kind])
    {
      hit = TRUE;
    }
  }

  slot->merchant_slot.weapon_kind = weapon_kind;
  slot->merchant_slot.price = prefab.weapon[weapon_kind].merchant.price;
  slot->merchant_slot.purchased = FALSE;

  Entity *weapon_deco = get_entity_child_at(slot, 0);
  weapon_deco->pos = prefab.weapon[weapon_kind].merchant.offset;
  weapon_deco->sprite = prefab.weapon[weapon_kind].sprite;
  weapon_deco->rot = 270;
  entity_rem_prop(weapon_deco, EntityProp_Renders);
}

void slot_populate_ammo(Entity *slot)
{
  i32 roll = random_i32(1, 4);
  slot->merchant_slot.ammo_count = 8 * roll;
  slot->merchant_slot.price = roll;
  slot->merchant_slot.purchased = FALSE;
  slot->sprite = prefab.sprite.ui_slot_coin_ammo;
}

void slot_populate_powerup(Entity *slot)
{

}
