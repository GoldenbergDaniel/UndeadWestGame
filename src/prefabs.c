#include "vecmath/vecmath.h"
#include "prefabs.h"

extern Prefabs prefab;

void init_prefabs(void)
{
  // - :sprites ---
  {
    prefab.sprite.player_male_idle      = (Sprite) {v2i(0, 0), v2i(1, 1)};
    prefab.sprite.player_male_walk_0    = (Sprite) {v2i(1, 0), v2i(1, 1)};
    prefab.sprite.player_male_walk_1    = (Sprite) {v2i(2, 0), v2i(1, 1)};
    prefab.sprite.player_male_walk_2    = (Sprite) {v2i(3, 0), v2i(1, 1)};
    prefab.sprite.player_male_walk_3    = (Sprite) {v2i(4, 0), v2i(1, 1)};
    prefab.sprite.player_male_walk_4    = (Sprite) {v2i(5, 0), v2i(1, 1)};
    prefab.sprite.player_male_jump      = (Sprite) {v2i(6, 0), v2i(1, 1)};
    prefab.sprite.player_male_dead      = (Sprite) {v2i(7, 0), v2i(1, 1)};
    prefab.sprite.player_female_idle    = (Sprite) {v2i(8, 0), v2i(1, 1)};
    prefab.sprite.player_female_walk_0  = (Sprite) {v2i(9, 0), v2i(1, 1)};
    prefab.sprite.player_female_walk_1  = (Sprite) {v2i(10, 0), v2i(1, 1)};
    prefab.sprite.player_female_walk_2  = (Sprite) {v2i(11, 0), v2i(1, 1)};
    prefab.sprite.player_female_walk_3  = (Sprite) {v2i(12, 0), v2i(1, 1)};
    prefab.sprite.player_female_walk_4  = (Sprite) {v2i(13, 0), v2i(1, 1)};
    prefab.sprite.player_female_jump    = (Sprite) {v2i(14, 0), v2i(1, 1)};
    prefab.sprite.player_female_dead    = (Sprite) {v2i(15, 0), v2i(1, 1)};
    prefab.sprite.walker_idle           = (Sprite) {v2i(0, 1), v2i(1, 1)};
    prefab.sprite.walker_walk_0         = (Sprite) {v2i(1, 1), v2i(1, 1)};
    prefab.sprite.walker_walk_1         = (Sprite) {v2i(2, 1), v2i(1, 1)};
    prefab.sprite.walker_walk_2         = (Sprite) {v2i(3, 1), v2i(1, 1)};
    prefab.sprite.walker_walk_3         = (Sprite) {v2i(4, 1), v2i(1, 1)};
    prefab.sprite.walker_walk_4         = (Sprite) {v2i(5, 1), v2i(1, 1)};
    prefab.sprite.chicken_idle_0        = (Sprite) {v2i(0, 2), v2i(1, 1)};
    prefab.sprite.chicken_idle_1        = (Sprite) {v2i(1, 2), v2i(1, 1)};
    prefab.sprite.chicken_lay_0         = (Sprite) {v2i(2, 2), v2i(1, 1)};
    prefab.sprite.chicken_lay_1         = (Sprite) {v2i(3, 2), v2i(1, 1)};
    prefab.sprite.baby_chicken_idle     = (Sprite) {v2i(7, 2), v2i(1, 1)};
    prefab.sprite.bloat_idle            = (Sprite) {v2i(0, 3), v2i(1, 2)};
    prefab.sprite.bloat_walk_0          = (Sprite) {v2i(1, 3), v2i(1, 2)};
    prefab.sprite.bloat_walk_1          = (Sprite) {v2i(2, 3), v2i(1, 2)};
    prefab.sprite.bloat_walk_2          = (Sprite) {v2i(3, 3), v2i(1, 2)};
    prefab.sprite.bloat_walk_3          = (Sprite) {v2i(4, 3), v2i(1, 2)};
    prefab.sprite.bloat_walk_4          = (Sprite) {v2i(5, 3), v2i(1, 2)};
    prefab.sprite.bloat_pound_0         = (Sprite) {v2i(6, 3), v2i(1, 2)};
    prefab.sprite.revolver              = (Sprite) {v2i(0, 5), v2i(1, 1)};
    prefab.sprite.rifle                 = (Sprite) {v2i(1, 5), v2i(1, 1)};
    prefab.sprite.shotgun               = (Sprite) {v2i(2, 5), v2i(1, 1)};
    prefab.sprite.smg                   = (Sprite) {v2i(3, 5), v2i(1, 1)};
    prefab.sprite.burst_rifle           = (Sprite) {v2i(4, 5), v2i(1, 1)};
    prefab.sprite.laser_pistol          = (Sprite) {v2i(5, 5), v2i(1, 1)};
    prefab.sprite.muzzle_flash          = (Sprite) {v2i(0, 6), v2i(1, 1)};
    prefab.sprite.bullet                = (Sprite) {v2i(1, 6), v2i(1, 1)};
    prefab.sprite.laser_flash           = (Sprite) {v2i(2, 6), v2i(1, 1)};
    prefab.sprite.laser                 = (Sprite) {v2i(3, 6), v2i(1, 1)};
    prefab.sprite.pellet                = (Sprite) {v2i(4, 6), v2i(1, 1)};
    prefab.sprite.coin                  = (Sprite) {v2i(5, 6), v2i(1, 1)};
    prefab.sprite.soul                  = (Sprite) {v2i(6, 6), v2i(1, 1)};
    prefab.sprite.egg_0                 = (Sprite) {v2i(0, 7), v2i(1, 1)};
    prefab.sprite.egg_1                 = (Sprite) {v2i(1, 7), v2i(1, 1)};
    prefab.sprite.egg_2                 = (Sprite) {v2i(2, 7), v2i(1, 1)};
    prefab.sprite.wagon_left            = (Sprite) {v2i(8, 7), v2i(4, 2)};
    prefab.sprite.wagon_right           = (Sprite) {v2i(12, 7), v2i(4, 2)};
    prefab.sprite.ui_heart_full         = (Sprite) {v2i(0, 8), v2i(1, 1)};
    prefab.sprite.ui_heart_empty        = (Sprite) {v2i(1, 8), v2i(1, 1)};
    prefab.sprite.ui_ammo               = (Sprite) {v2i(3, 8), v2i(1, 1)};
    prefab.sprite.shockwave_0           = (Sprite) {v2i(0, 9), v2i(1, 1)};
    prefab.sprite.shockwave_1           = (Sprite) {v2i(1, 9), v2i(1, 1)};
    prefab.sprite.shockwave_2           = (Sprite) {v2i(2, 9), v2i(1, 1)};
    prefab.sprite.ui_slot_coin_empty    = (Sprite) {v2i(0, 10), v2i(1, 1)};
    prefab.sprite.ui_slot_coin_ammo     = (Sprite) {v2i(1, 10), v2i(1, 1)};
    prefab.sprite.ui_slot_soul_empty    = (Sprite) {v2i(2, 10), v2i(1, 1)};
    prefab.sprite.ui_slot_soul_heal     = (Sprite) {v2i(3, 10), v2i(1, 1)};
  }

  // - :animations ---
  {
    prefab.animation.player_male[EntityState_Idle] = (AnimationDesc) {
      .frame_count = 1,
      .frames[0]   = prefab.sprite.player_male_idle,
    };

    prefab.animation.player_male[EntityState_Walk] = (AnimationDesc) {
      .ticks_per_frame = 10,
      .frame_count     = 5,
      .frames[0]       = prefab.sprite.player_male_walk_0,
      .frames[1]       = prefab.sprite.player_male_walk_1,
      .frames[2]       = prefab.sprite.player_male_walk_2,
      .frames[3]       = prefab.sprite.player_male_walk_3,
      .frames[4]       = prefab.sprite.player_male_walk_4,
    };

    prefab.animation.player_male[EntityState_Jump] = (AnimationDesc) {
      .ticks_per_frame = 0,
      .frame_count     = 1,
      .frames[0]       = prefab.sprite.player_male_jump,
    };

    prefab.animation.player_female[EntityState_Idle] = (AnimationDesc) {
      .frame_count = 1,
      .frames[0]   = prefab.sprite.player_female_idle,
    };

    prefab.animation.player_female[EntityState_Walk] = (AnimationDesc) {
      .ticks_per_frame = 10,
      .frame_count     = 5,
      .frames[0]       = prefab.sprite.player_female_walk_0,
      .frames[1]       = prefab.sprite.player_female_walk_1,
      .frames[2]       = prefab.sprite.player_female_walk_2,
      .frames[3]       = prefab.sprite.player_female_walk_3,
      .frames[4]       = prefab.sprite.player_female_walk_4,
    };

    prefab.animation.player_female[EntityState_Jump] = (AnimationDesc) {
      .frame_count = 1,
      .frames[0]   = prefab.sprite.player_female_jump,
    };

    prefab.animation.player_female[EntityState_Dead] = (AnimationDesc) {
      .frame_count = 1,
      .frames[0]   = prefab.sprite.player_female_dead,
    };

    prefab.animation.zombie_walker[EntityState_Idle] = (AnimationDesc) {
      .frame_count = 1,
      .frames[0]   = prefab.sprite.walker_idle,
    };

    prefab.animation.zombie_walker[EntityState_Walk] = (AnimationDesc) {
      .ticks_per_frame = 20,
      .frame_count     = 5,
      .frames[0]       = prefab.sprite.walker_walk_0,
      .frames[1]       = prefab.sprite.walker_walk_1,
      .frames[2]       = prefab.sprite.walker_walk_2,
      .frames[3]       = prefab.sprite.walker_walk_3,
      .frames[4]       = prefab.sprite.walker_walk_4,
    };

    prefab.animation.zombie_chicken[EntityState_Idle] = (AnimationDesc) {
      .ticks_per_frame = 40,
      .frame_count     = 2,
      .frames[0]       = prefab.sprite.chicken_idle_0,
      .frames[1]       = prefab.sprite.chicken_idle_1,
    };

    prefab.animation.zombie_chicken[EntityState_Walk] = (AnimationDesc) {
      .ticks_per_frame = 30,
      .frame_count     = 2,
      .frames[0]       = prefab.sprite.chicken_idle_0,
      .frames[1]       = prefab.sprite.chicken_idle_1,
    };

    prefab.animation.zombie_chicken[EntityState_LayEggBegin] = (AnimationDesc) {
      .ticks_per_frame = 30,
      .frame_count     = 3,
      .frames = {
        [0] = prefab.sprite.chicken_idle_0,
        [1] = prefab.sprite.chicken_lay_0,
        [2] = prefab.sprite.chicken_lay_1,
      },
      .exit_state      = EntityState_LayEggLaying,
    };

    prefab.animation.zombie_chicken[EntityState_LayEggLaying] = (AnimationDesc) {
      .frame_count = 1,
      .frames[0]   = prefab.sprite.chicken_lay_1,
    };

    prefab.animation.zombie_chicken[EntityState_LayEggEnd] = (AnimationDesc) {
      .ticks_per_frame = 30,
      .frame_count     = 3,
      .frames[0]       = prefab.sprite.chicken_lay_1,
      .frames[1]       = prefab.sprite.chicken_lay_0,
      .frames[2]       = prefab.sprite.chicken_idle_0,
      .exit_state      = EntityState_Walk,
    };

    prefab.animation.zombie_baby_chicken[EntityState_Idle] = (AnimationDesc) {
      .frame_count = 1,
      .frames[0]   = prefab.sprite.baby_chicken_idle,
    };

    prefab.animation.zombie_baby_chicken[EntityState_Walk] = (AnimationDesc) {
      .frame_count = 1,
      .frames[0]   = prefab.sprite.baby_chicken_idle,
    };

    prefab.animation.zombie_bloat[EntityState_Idle] = (AnimationDesc) {
      .frame_count = 1,
      .frames[0]   = prefab.sprite.bloat_idle,
    };

    prefab.animation.zombie_bloat[EntityState_Walk] = (AnimationDesc) {
      .ticks_per_frame = 25,
      .frame_count     = 5,
      .frames[0]       = prefab.sprite.bloat_walk_0,
      .frames[1]       = prefab.sprite.bloat_walk_1,
      .frames[2]       = prefab.sprite.bloat_walk_2,
      .frames[3]       = prefab.sprite.bloat_walk_3,
      .frames[4]       = prefab.sprite.bloat_walk_4,
    };

    prefab.animation.zombie_bloat[EntityState_Jump] = (AnimationDesc) {
      .frame_count = 1,
      .frames[0]   = prefab.sprite.bloat_pound_0,
    };

    prefab.animation.zombie_bloat[EntityState_PoundBegin] = (AnimationDesc) {
      .frame_count = 1,
      .frames[0]   = prefab.sprite.rifle,
    };

    prefab.animation.zombie_bloat[EntityState_PoundEnd] = (AnimationDesc) {
      .frame_count = 1,
      .frames[0]   = prefab.sprite.bloat_pound_0,
      .exit_state  = EntityState_Walk,
    };

    prefab.animation.shockwave[EntityState_Idle] = (AnimationDesc) {
      .ticks_per_frame = 20,
      .frame_count     = 3,
      .frames[0]       = prefab.sprite.shockwave_0,
      .frames[1]       = prefab.sprite.shockwave_1,
      .frames[2]       = prefab.sprite.shockwave_2,
      .exit_state      = EntityState_Dead,
    };
  }

  // - :player stats ---
  {
    prefab.player_stat[EntityGender_Male].health   = 5; 
    prefab.player_stat[EntityGender_Male].speed    = 400.0f; 
    prefab.player_stat[EntityGender_Male].jump_vel = 900.0f; 

    prefab.player_stat[EntityGender_Female].health   = 4;
    prefab.player_stat[EntityGender_Female].speed    = 400.0f * 1.1f; 
    prefab.player_stat[EntityGender_Female].jump_vel = 900.0f * 1.1f; 
  }

  // - :particles ---
  {
    prefab.particle[ParticleKind_Smoke] = (ParticleDesc) {
      .emmission_type  = ParticleEmmissionType_Burst,
      .props           = ParticleProp_ScaleOverTime |
                         ParticleProp_SpeedOverTime |
                         ParticleProp_VariateColor |
                         ParticleProp_RotateOverTime |
                         ParticleProp_KillAfterTime,
      .count           = 3,
      .duration        = 1.5f,
      .spread          = 180.0f,
      .color_primary   = v4f(0.55f, 0.55f, 0.55f, 1.0f),
      .color_secondary = v4f(0.1f, 0.1f, 0.1f, 1.0f),
      .scale           = v2f(7, 7),
      .scale_delta     = v2f(-8.0f, -8.0f),
      .speed           = 60.0f,
      .speed_delta     = -4000.0f,
      .rot_delta       = 20.0f,
    };

    prefab.particle[ParticleKind_Blood] = (ParticleDesc) {
      .emmission_type = ParticleEmmissionType_Burst,
      .props          = ParticleProp_ScaleOverTime |
                        ParticleProp_RotateOverTime |
                        ParticleProp_KillAfterTime,
      .count          = 6,
      .duration       = 0.3f,
      .spread         = 180.0f,
      .color_primary  = v4f(0.47f, 0.13f, 0.13f, 1.0f),
      .scale          = v2f(5, 5),
      .scale_delta    = v2f(-6.0f, -6.0f),
      .speed          = 60.0f,
      .rot_delta      = 50.0f,
    };

    prefab.particle[ParticleKind_Death] = (ParticleDesc) {
      .emmission_type = ParticleEmmissionType_Burst,
      .props          = ParticleProp_CollidesWithGround,
      .count          = 40,
      .duration       = 10.0f,
      .spread         = 100.0f,
      .color_primary  = v4f(0.37f, 0.0f, 0.0f, 1.0f),
      .scale          = v2f(10, 10),
      .speed          = 3000.0f,
      .vel            = v2f(0.0f, 0.0f),
    };

    prefab.particle[ParticleKind_PickupCoin] = (ParticleDesc) {
      .emmission_type = ParticleEmmissionType_Burst,
      .props          = ParticleProp_ScaleOverTime |
                        ParticleProp_RotateOverTime |
                        ParticleProp_KillAfterTime,
      .count          = 6,
      .duration       = 0.3f,
      .spread         = 500.0f,
      .color_primary  = v4f(0.89f, 0.78f, 0.11f, 1.0f),
      .scale          = v2f(5, 5),
      .scale_delta    = v2f(-6.0f, -6.0f),
      .speed          = 60.0f,
      .rot_delta      = 50.0f,
    };

    prefab.particle[ParticleKind_PickupSoul] = (ParticleDesc) {
      .emmission_type = ParticleEmmissionType_Burst,
      .props          = ParticleProp_ScaleOverTime |
                        ParticleProp_RotateOverTime |
                        ParticleProp_KillAfterTime,
      .count          = 6,
      .duration       = 0.3f,
      .spread         = 500.0f,
      .color_primary  = v4f(119/255.0f, 176/255.0f, 231/255.0f, 1.0f),
      .scale          = v2f(5, 5),
      .scale_delta    = v2f(-6.0f, -6.0f),
      .speed          = 60.0f,
      .rot_delta      = 50.0f,
    };

    prefab.particle[ParticleKind_EggHatch] = (ParticleDesc) {
      .emmission_type = ParticleEmmissionType_Burst,
      .props          = ParticleProp_ScaleOverTime |
                        ParticleProp_RotateOverTime |
                        ParticleProp_KillAfterTime,
      .count          = 6,
      .duration       = 0.3f,
      .spread         = 500.0f,
      .color_primary  = v4f(209/255.0f, 177/255.0f, 113/255.0f, 1.0f),
      .scale          = v2f(5, 5),
      .scale_delta    = v2f(-6.0f, -6.0f),
      .speed          = 60.0f,
      .rot_delta      = 50.0f,
    };

    prefab.particle[ParticleKind_Dirt] = (ParticleDesc) {
      .emmission_type  = ParticleEmmissionType_Burst,
      .props           = ParticleProp_ScaleOverTime |
                         ParticleProp_SpeedOverTime |
                         ParticleProp_VariateColor |
                         ParticleProp_RotateOverTime |
                         ParticleProp_KillAfterTime,
      .count           = 16,
      .duration        = 0.25f,
      .spread          = 180.0f,
      .color_primary   = v4f(120/255.0f, 71/255.0f, 48/255.0f, 1.0f),
      .color_secondary = v4f(0.1f, 0.1f, 0.1f, 1.0f),
      .scale           = v2f(4, 4),
      .speed           = 120.0f,
      .speed_delta     = -4000.0f,
      .rot_delta       = 20.0f,
    };

    prefab.particle[ParticleKind_Debug] = (ParticleDesc) {
      .emmission_type  = ParticleEmmissionType_Burst,
      .props           = ParticleProp_ScaleOverTime |
                         ParticleProp_SpeedOverTime |
                         ParticleProp_VariateColor |
                         ParticleProp_KillAfterTime,
      .scale           = v2f(20, 20),
      .count           = 100,
      .duration        = 2.0f,
      .speed           = 80.0f,
      .spread          = 180.0f,
      .color_primary   = DEBUG_RED,
      .color_secondary = DEBUG_BLUE,
      .scale_delta     = v2f(-0.5f, -0.5f),
      .speed_delta     = 50.0f,
    };
  }

  // - :zombies ---
  {
    prefab.zombie[ZombieKind_Walker] = (ZombieDesc) {
      .props           = 0,
      .move_type       = MoveType_Grounded,
      .combat_type     = CombatType_Melee,
      .speed           = 55,
      .health          = 20,
      .damage          = 1,
      .attack_cooldown = 1.0f,
    };

    prefab.zombie[ZombieKind_Chicken] = (ZombieDesc) {
      .props           = EntityProp_LaysEggs,
      .move_type       = MoveType_Grounded,
      .combat_type     = CombatType_Melee,
      .speed           = 150,
      .health          = 14,
      .damage          = 1,
      .attack_cooldown = 0.5f,
    };

    prefab.zombie[ZombieKind_BabyChicken] = (ZombieDesc) {
      .props           = EntityProp_Morphs,
      .move_type       = MoveType_Grounded,
      .speed           = 50,
      .health          = 1,
      .damage          = 0,
      .attack_cooldown = 0.5f,
    };

    prefab.zombie[ZombieKind_Bloat] = (ZombieDesc) {
      .props           = 0,
      .move_type       = MoveType_Grounded,
      .combat_type     = CombatType_Pound,
      .speed           = 45,
      .health          = 70,
      .damage          = 2,
      .attack_cooldown = 2.0f,
    };
  }

  // - :weapons ---
  {
    prefab.weapon[WeaponKind_Revolver] = (WeaponDesc) {
      .name            = str("Revolver"),
      .sprite          = prefab.sprite.revolver,
      .ammo_kind       = AmmoKind_Bullet,
      .ancor           = v2f(35, 0),
      .shot_point      = v2f(20, 2.5),
      .shot_cooldown   = 0.6f,
      .damage          = 6,
      .bullet_speed    = 1000.0f,
      .ammo            = 6,
      .reload_duration = 3,
    };

    prefab.weapon[WeaponKind_Rifle] = (WeaponDesc) {
      .name            = str("Rifle"),
      .sprite          = prefab.sprite.rifle,
      .ammo_kind       = AmmoKind_Bullet,
      .ancor           = v2f(30, 5),
      .shot_point      = v2f(45, 0),
      .shot_cooldown   = 1.15f,
      .damage          = 14,
      .bullet_speed    = 1500.0f,
      .ammo            = 5,
      .reload_duration = 5,
      .merchant = {
        .price = 3,
      }
    };

    prefab.weapon[WeaponKind_Shotgun] = (WeaponDesc) {
      .name            = str("Shotgun"),
      .sprite          = prefab.sprite.shotgun,
      .ammo_kind       = AmmoKind_Pellet,
      .ancor           = v2f(30, 5),
      .shot_point      = v2f(40, 0),
      .shot_cooldown   = 0.95f,
      .damage          = 4,
      .bullet_speed    = 1000.0f,
      .ammo            = 7,
      .reload_duration = 3,
      .merchant = {
        .price = 7,
      }
    };

    prefab.weapon[WeaponKind_SMG] = (WeaponDesc) {
      .name            = str("SMG"),
      .sprite          = prefab.sprite.smg,
      .ammo_kind       = AmmoKind_Bullet,
      .ancor           = v2f(25, 0),
      .shot_point      = v2f(35, 0),
      .shot_cooldown   = 0.085f,
      .damage          = 2,
      .bullet_speed    = 1500.0f,
      .ammo            = 30,
      .reload_duration = 5,
      .merchant = {
        .price = 7,
      }
    };

    prefab.weapon[WeaponKind_BurstRifle] = (WeaponDesc) {
      .name            = str("Burst Rifle"),
      .sprite          = prefab.sprite.burst_rifle,
      .ammo_kind       = AmmoKind_Bullet,
      .ancor           = v2f(25, 0),
      .shot_point      = v2f(40, 0),
      .shot_cooldown   = 0.15f,
      .damage          = 3,
      .bullet_speed    = 1200.0f,
      .ammo            = 30,
      .reload_duration = 5,
      .merchant = {
        .price = 10,
      }
    };

    prefab.weapon[WeaponKind_LaserPistol] = (WeaponDesc) {
      .name            = str("Laser Pistol"),
      .sprite          = prefab.sprite.laser_pistol,
      .ammo_kind       = AmmoKind_Laser,
      .ancor           = v2f(35, 5),
      .shot_point      = v2f(20, 0),
      .shot_cooldown   = 0.2f,
      .damage          = 6,
      .bullet_speed    = 1000.0f,
      .ammo            = 999,
      .reload_duration = 5,
    };
  }

  // - :collectables ---
  {
    prefab.collectable[CollectableKind_Coin] = (CollectableDesc) {
      .sprite      = prefab.sprite.coin,
      .draw_chance = 30,
    };
    
    prefab.collectable[CollectableKind_Soul] = (CollectableDesc) {
      .sprite      = prefab.sprite.soul,
      .draw_chance = 5,
    };
  }

  // - :waves ---
  {
    // prefab.wave[0] = (WaveDesc) {
    //   .time_btwn_spawns = 3,
    //   .zombie_counts = {
    //     [ZombieKind_Walker] = 4,
    //   }
    // };

    prefab.wave[0] = (WaveDesc) {
      .time_btwn_spawns = 3,
      .zombie_counts = {
        [ZombieKind_Walker] = 0,
      }
    };

    prefab.wave[1] = (WaveDesc) {
      .time_btwn_spawns = 3,
      .zombie_counts = {
        [ZombieKind_Walker] = 6,
      }
    };

    prefab.wave[2] = (WaveDesc) {
      .time_btwn_spawns = 3,
      .zombie_counts = {
        [ZombieKind_Walker]  = 8,
        [ZombieKind_Chicken] = 1,
      }
    };
    
    prefab.wave[3] = (WaveDesc) {
      .time_btwn_spawns = 2,
      .zombie_counts = {
        [ZombieKind_Walker]  = 8,
        [ZombieKind_Chicken] = 3,
      }
    };

    prefab.wave[4] = (WaveDesc) {
      .time_btwn_spawns = 2,
      .zombie_counts = {
        [ZombieKind_Walker]  = 7,
        [ZombieKind_Chicken] = 5,
        [ZombieKind_Bloat] = 1,
      }
    };
  }
}
