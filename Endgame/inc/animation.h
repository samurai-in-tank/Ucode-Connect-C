// animation.h
#ifndef ANIMATION_H
#define ANIMATION_H

#include "common.h"
#include "tileset.h"
#include "entity.h"

t_animation *animation_add(t_entity *entity, int id, t_tile tileset, int tileset_size, int duration, bool is_repeated);
void animation_play(t_entity *entity, int id, int start_tile);
void animation_reload(t_entity *entity, int id);
void animate(t_entity *entity);
int animation_gettime(t_entity *entity, int id);
void animations_free(t_entity *entity);

#endif
