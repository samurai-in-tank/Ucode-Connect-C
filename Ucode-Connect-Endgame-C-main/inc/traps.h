// traps.h
#ifndef TRAPS_H
#define TRAPS_H


#include "common.h"
#include "draw.h"
#include "tileset.h"

t_trap *trap_add(t_game * game, t_tile tile, t_tile active_tile, int x1, int y1, int x2, int y2, t_trap_type type, int delay);
void trap_init(t_game* game);
void trap_draw(t_game* game);
void trap_logic(t_game* game);
void trap_free(t_game* game);
void trap_trigger(t_game *game, t_trap *current);
void trap_glimmer(t_game *game, t_trap *current);

#endif
