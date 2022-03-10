// enums.h
#ifndef ENUMS_H
#define ENUMS_H

typedef enum e_facing {
	FACING_LEFT,
	FACING_RIGHT
} t_facing;

typedef enum e_traps {
	TRAP_TRIGGER,
	TRAP_GLIMMER
} t_trap_type;

typedef enum e_anchor {
	ANCHOR_TOP_LEFT,
	ANCHOR_TOP_CENTER,
	ANCHOR_TOP_RIGHT,
	ANCHOR_CENTER_LEFT,
	ANCHOR_CENTER_CENTER,
	ANCHOR_CENTER_RIGHT,
	ANCHOR_BOTTOM_LEFT,
	ANCHOR_BOTTOM_CENTER,
	ANCHOR_BOTTOM_RIGHT
} t_anchor;

typedef enum e_entype {
	ENTYPE_PLAYER,
	ENTYPE_NPC,
	ENTYPE_ITEM,
	ENTYPE_DOOR,
	ENTYPE_OBJECT
} t_entity_type;

typedef enum e_item {
	ITEM_NULL,
	ITEM_NOTSET,
	ITEM_PAINT,
	ITEM_KEY, 
	ITEM_FINAL_KEY,
	ITEM_CAVE_KEY
} t_item;

typedef enum e_sound_channel {
	CH_ANY = -1,
	CH_PLAYER,
	CH_OTHER
} t_sound_channel;

typedef enum e_sound_type {
	SND_PLAYER_RUN,
	SND_PLAYER_DIE,
	SND_DOOR_UNLOCK,
	SND_DOOR_OPEN,
	SND_NPC_SPEECH,
	SND_MENU_MUSIC,
	SND_LEVEL2_MUSIC,
	SND_MAX
} t_sound_type;

#endif
