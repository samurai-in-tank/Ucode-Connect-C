// npc.h
#ifndef NPC_H
#define NPC_H

#include "common.h"
#include "entity.h"

t_entity *npc_add(t_game *game, char *slag, t_tile tile, int x, int y, bool is_active);
void npc_logic(t_game *game, t_entity *npc);
void npc_draw(t_game *game, t_entity *npc);
void npc_free(t_entity *npc);

#endif
