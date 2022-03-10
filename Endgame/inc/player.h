// player.h
#ifndef PLAYER_H
#define PLAYER_H


#include "common.h"
#include "draw.h"
#include "tileset.h"
#include "entity.h"
#include "text.h"

void player_init(t_game* game, int x, int y);
void player_draw(t_game* game);
void player_logic(t_game* game);
void player_free(t_game* game);

void player_set_spawnpoint(t_game *game, int x, int y);

#endif
