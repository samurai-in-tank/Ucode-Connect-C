// death.h
#ifndef DEATH_H
#define DEATH_H

#include "common.h"
#include "draw.h"
#include "tileset.h"
#include "animation.h"

void death_init(t_game *game);
void death_logic(t_game *game);
void death_draw(t_game *game);
void death_free(t_game *game);

#endif
