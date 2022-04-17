#pragma once

#include "Game.h"

#define SPRITE_SIZE_X 16
#define SPRITE_SIZE_Y 16

// player
#define PLAYER_POS				 0,0
#define PLAYER_IDLE_BACK_POS	 1,0
#define PLAYER_IDLE_FRONT_POS	 4,0
#define PLAYER_IDLE_LEFT_POS	 7,0
#define PLAYER_IDLE_RIGHT_POS	10,0
#define PLAYER_MOVING_FRONT_POS	 0,1
#define PLAYER_MOVING_BACK_POS	 4,1
#define PLAYER_MOVING_LEFT_POS	 8,1
#define PLAYER_MOVING_RIGHT_POS 12,1
//enemies
#define CYAN_ENEMY_POS			0,2
#define CYAN_ENEMY_IDLE_POS		1,2
#define CYAN_ENEMY_DEATH_POS	4,2
#define VETERAN_ENEMY_POS		0,3
#define VETERAN_ENEMY_IDLE_POS  1,3
#define VETERAN_ENEMY_DEATH_POS 4,3
#define RED_ENEMY_POS			0,4
#define RED_ENEMY_IDLE_POS		1,4
#define RED_ENEMY_DEATH_POS		4,4
// tiles
#define BRICK_TILE_POS	 0,5
#define GRASS_TILE_1_POS 1,5
#define GRASS_TILE_2_POS 2,5
#define GRASS_TILE_3_POS 3,5
#define GRASS_TILE_4_POS 4,5
// weapons
#define WAND_POS		0,6
#define TRIPLE_WAND_POS 1,6
#define BOW_POS			2,6
#define SWORD_POS		3,6
// projectiles
#define BASIC_PROJECTILE_POS	0,7
#define SPECIAL_PROJECTILE_POS	1,7
#define ARROW_PROJECTILE_POS	2,7
// misc
#define FRAME_POS			0,8
#define SELECTED_FRAME_POS  1,8
#define HEART_POS			2,8
#define HALF_HEART_POS		3,8
#define EMPTY_HEART_POS		4,8