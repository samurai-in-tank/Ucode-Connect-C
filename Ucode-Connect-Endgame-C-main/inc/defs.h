// defs.c :: Ivan Ryzhenko 2021
#ifndef DEFS_H
#define DEFS_H

#define GAME_TITLE "Game"
#define PLAYER_SPEED 4
#define TIME_AFTER_DEATH 300

#define MAP_WIDTH 20
#define MAP_HEIGHT 12

#define MAX_FILENAME_LENGTH 256

#define TILE_SIZE 16
#define TILE_SCALE 4
//Common things
#define TILE_GROUND 0

//Labs assets
#define TILE_LAB_LEFT_CORNER_UP 13
#define TILE_LAB_LEFT_CORNER_DOWN 14
#define TILE_LAB_RIGHT_CORNER_UP 16
#define TILE_LAB_RIGHT_CORNER_DOWN 17
#define TILE_LAB_FLOOR 18
#define TILE_LAB_WALL_FRONT 19
#define TILE_LAB_WALL 20
#define TILE_LAB_WALL_LINER_LEFT 21
#define TILE_LAB_WALL_LINER_RIGHT 22
//First level assets(military base)
#define TILE_MIL_LEFT_CORNER_UP 23
#define TILE_MIL_LEFT_CORNER_DOWN 24
#define TILE_MIL_RIGHT_CORNER_UP 25
#define TILE_MIL_RIGHT_CORNER_DOWN 26
#define TILE_MIL_FLOOR 27
#define TILE_MIL_WALL_FRONT 28
#define TILE_MIL_WALL 29
#define TILE_MIL_WALL_LINER_LEFT 31
#define TILE_MIL_WALL_LINER_RIGHT 32



#define MIL_LEFT_CORNER_UP 43
#define MIL_LEFT_CORNER_DOWN 34
#define MIL_RIGHT_CORNER_UP 35
#define MIL_RIGHT_CORNER_DOWN 36
#define MIL_FLOOR 37
#define MIL_WALL_FRONT 38
#define MIL_WALL 39
#define WALL_LINER_LEFT_I 41
#define WALL_LINER_RIGHT 42

#define TILE_WALL 11

#define TILE_WALL_FRONT 99

#define ROCK 88

#define ROCK_FLOOR 8
#define TILE_MILL_ROOF 33

#define ROCK_WALL_FRONT 87

#define ROCK_WALL_FRONT_L_CORNNER 89

#define ROCK_WALL_LEFT 91


#define ROCK_WALL_RIGH 92

#define MAX_SND_CHANNELS 8
#define CHARACTER_TIME 50


//PLANTS AND OTHER THIGS
#define CACTUS 51


#define CACTUS_1 53
#define CACTUS_2 54

#define PERECATI_POLE 52

#define NETRAN 55

#define bottle 56

#define bottle_empty 57

#define trash 58
#define trash2 9
#define comp 60
#define trava 7

#define SCREEN_WIDTH   MAP_WIDTH * TILE_SIZE * TILE_SCALE
#define SCREEN_HEIGHT  MAP_HEIGHT * TILE_SIZE * TILE_SCALE

#endif
