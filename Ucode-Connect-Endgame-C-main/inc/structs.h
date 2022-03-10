// structs.c
#ifndef STRUCTS_H
#define STRUCTS_H


#include <SDL2/SDL.h>
#include "defs.h"
#include "enums.h"

typedef SDL_Rect t_tile;

typedef struct s_control {
	int up;
	int down;
	int left;
	int right;
	int use;
	int start;
	bool is_locked;
	bool D;
	bool E;
	bool V;
} t_control;

typedef struct s_animation {
	t_tile *tile;
	t_tile tileset;
	int id;
	int tileset_size;
	int duration;
	int current_tile;
	unsigned int timer_start;
	struct s_animation *next;
	bool is_playing;
	bool is_repeated;
} t_animation;

typedef struct s_entity {
	int x;
	int y;
	int w;
	int h;
	bool is_death;
	t_tile tile;
	t_entity_type type;
	t_animation *animations;
	t_facing facing;
	struct s_entity *next;
	void *data;
	t_item items[8];
	struct s_entity *usable;
	char *slag;
} t_entity;

typedef struct s_map {
	int **data;
	SDL_Point offset;
	SDL_Point size;
} t_map;

typedef struct s_trap {
    int x1;
    int y1;
	int x2;
    int y2;
	int delay;
	unsigned int timer;
    bool activated;
	t_tile tile;
	t_tile active_tile;
	t_trap_type type;
	struct s_trap *next;
} t_trap;

typedef struct s_sound {
	unsigned int timer;
	Mix_Chunk *all_sounds[SND_MAX];
	Mix_Music *music[SND_MAX];
	t_sound_channel sound_channel;
	t_sound_type sound_type;
} t_sound;

typedef struct s_message {
	char *header;
	char *text;
	int branch;
	bool is_current;
	unsigned int timer;
	int delay;
	struct s_message *next;
	bool is_shown;
} t_message;

typedef struct s_questsys {
	int level;
	int stage;
} t_questsys;

typedef struct s_dev_mode {
	bool im_dev;
	bool god;
	bool noclip;
	bool skip;
	int acceleration;
} t_dev_mode;

typedef struct s_game {
	SDL_Renderer *renderer;
	SDL_Window *window;
	t_control control;
	SDL_Texture *tileset;
	SDL_Point *spawn;
	t_map *map;
	t_entity *player;
	t_trap *traps;
	bool is_started;
	unsigned int death_timer;
	bool game_over_screen;
	t_entity *entities;
	SDL_Point scene_offset;
	t_sound sound;
	bool is_death_sound;
	bool is_door_sound;
	t_entity *message_entity;
	t_questsys questsys;
	bool is_last_stage;
	SDL_Point spawnpoint;
	bool is_finish;
	SDL_Texture *main_menu_texture;
	t_dev_mode dev_mode;
} t_game;

typedef struct s_entdata_door {
	bool is_hidden;
	bool is_locked;
	t_item required_item;
	t_tile open;
	t_tile close;
} t_entdata_door;

typedef struct s_entdata_item {
	bool is_active;
	bool is_picked_up;
	t_item item;
} t_entdata_item;

typedef struct s_entdata_object {
	bool is_active;
	bool is_used;
	bool is_using;
	bool is_obstacle;
	unsigned int timer;
	int delay;
	t_tile start_tile;
	t_tile finish_tile;
	t_item required_item;
} t_entdata_object;

typedef struct s_entdata_npc {
	bool is_active;
	t_message *messages;
	int current_branch;
	bool is_talk;
} t_entdata_npc;


#endif
