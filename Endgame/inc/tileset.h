// tile.h
#ifndef ATLAS_H
#define ATLAS_H


#include "common.h"

void tileset_init(t_game* game, char* filename);
void blit_tile(t_game* game, t_tile tile, int x, int y, t_anchor anchor);
t_tile set_tile(int x, int y);
void tileset_free(t_game* game);

#endif

