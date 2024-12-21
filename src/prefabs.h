#pragma once

#include "draw.h"
#include "entity.h"
#include "game.h"

typedef struct Prefabs Prefabs;
struct Prefabs
{
  struct
  {
    Sprite player_male_idle;
    Sprite player_male_walk_0;
    Sprite player_male_walk_1;
    Sprite player_male_walk_2;
    Sprite player_male_walk_3;
    Sprite player_male_walk_4;
    Sprite player_male_walk_5;
    Sprite player_male_jump;
    Sprite player_female_idle;
    Sprite player_female_walk_0;
    Sprite player_female_walk_1;
    Sprite player_female_walk_2;
    Sprite player_female_walk_3;
    Sprite player_female_walk_4;
    Sprite player_female_walk_5;
    Sprite player_female_jump;
    Sprite walker_idle;
    Sprite walker_walk_0;
    Sprite walker_walk_1;
    Sprite walker_walk_2;
    Sprite walker_walk_3;
    Sprite walker_walk_4;
    Sprite walker_walk_5;
    Sprite chicken_idle;
    Sprite chicken_lay_0;
    Sprite chicken_lay_1;
    Sprite baby_chicken_idle;
    Sprite bloat_idle;
    Sprite bloat_walk_0;
    Sprite bloat_walk_1;
    Sprite bloat_walk_2;
    Sprite bloat_walk_3;
    Sprite bloat_walk_4;
    Sprite bloat_walk_5;
    Sprite bloat_pound_1;
    Sprite revolver;
    Sprite rifle;
    Sprite shotgun;
    Sprite smg;
    Sprite burst_rifle;
    Sprite laser_pistol;
    Sprite muzzle_flash;
    Sprite bullet;
    Sprite laser_flash;
    Sprite laser;
    Sprite pellet;
    Sprite coin;
    Sprite soul;
    Sprite egg_0;
    Sprite egg_1;
    Sprite egg_2;
    Sprite wagon_left;
    Sprite wagon_right;
    Sprite ui_heart_full;
    Sprite ui_heart_empty;
    Sprite ui_ammo;
  } sprite;

  struct
  {
    AnimationDesc player_male[EntityState_COUNT];
    AnimationDesc player_female[EntityState_COUNT];
    AnimationDesc zombie_walker[EntityState_COUNT];
    AnimationDesc zombie_chicken[EntityState_COUNT];
    AnimationDesc zombie_baby_chicken[EntityState_COUNT];
    AnimationDesc zombie_bloat[EntityState_COUNT];
  } animation;

  ParticleDesc particle[ParticleKind_COUNT];
  WaveDesc wave[TOTAL_WAVE_COUNT];
  ZombieDesc zombie[ZombieKind_COUNT];
  WeaponDesc weapon[WeaponKind_COUNT];
  CollectableDesc collectable[CollectableKind_COUNT];
};

Prefabs create_prefabs(void);
