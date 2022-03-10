// hoor.h
#ifndef DOOR_H
#define DOOR_H

#include "common.h"
#include "entity.h"
#include "sound.h"

t_entity *door_add(t_game *game, char *slag, t_tile otile, t_tile ctile, int x, int y, bool is_locked, t_item required_item, bool is_hidden);
void door_logic(t_game *game, t_entity *door);
void door_draw(t_game *game, t_entity *door);
void door_free(t_entity *door);

#endif
