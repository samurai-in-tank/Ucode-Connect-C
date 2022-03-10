// npc.c

#include "npc.h"

t_entity *npc_add(t_game *game, char *slag, t_tile tile, int x, int y, bool is_active) {
    t_entity *npc = entity_add(game, ENTYPE_NPC, x, y, tile, FACING_RIGHT);
    npc->slag = slag;

    npc->data = malloc(sizeof(t_entdata_npc));

    t_entdata_npc *data = (t_entdata_npc *)npc->data;

    data->is_active = is_active;
    data->messages = NULL;
    data->current_branch = 0;
    data->is_talk = false;

    return npc;
}

void npc_logic(t_game *game, t_entity *npc) {
    if(((t_entdata_npc *)npc->data)->is_talk)
        message_show(game, npc);
}

void npc_draw(t_game *game, t_entity *npc) {
    blit_tile(game, npc->tile, game->scene_offset.x + npc->x * (TILE_SIZE * TILE_SCALE), game->scene_offset.y + npc->y * (TILE_SIZE * TILE_SCALE) - TILE_SCALE, ANCHOR_TOP_LEFT);
}

void npc_free(t_entity *npc) {
    messages_free(npc);
    free(npc->data);
    npc->data = NULL;
}
