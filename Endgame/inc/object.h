// object.h
#ifndef OBJECT_H
#define OBJECT_H

#include "common.h"
#include "entity.h"

t_entity *object_add(t_game *game, char *slag, t_tile start_tile, t_tile finish_tile, int x, int y, bool is_active, t_item required_item, int delay, bool is_obstacle);
void object_logic(t_game *game, t_entity *obj);
void object_draw(t_game *game, t_entity *obj);
void object_free(t_entity *obj);

#endif
