// item.c
#ifndef ITEM_H
#define ITEM_H

#include "common.h"
#include "entity.h"

t_entity *item_add(t_game *game, t_tile tile, int x, int y, t_item item, bool is_active);
void item_draw(t_game *game, t_entity *item);
void item_free(t_entity *item);

#endif
