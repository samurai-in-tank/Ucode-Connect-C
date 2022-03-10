// map.h
#ifndef MAP_H
#define MAP_H

#include "common.h"
#include "tileset.h"

void map_init(t_game *game, char *filename);
void map_draw(t_game* game);
void map_draw_front(t_game* game);

#endif

