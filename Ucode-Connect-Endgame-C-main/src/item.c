// item.c

#include "item.h"

t_entity *item_add(t_game *game, t_tile tile, int x, int y, t_item type, bool is_active) {
    t_entity *item = entity_add(game, ENTYPE_ITEM, x, y, tile, FACING_RIGHT);

    item->data = malloc(sizeof(t_entdata_item));
    ((t_entdata_item *)item->data)->is_active = is_active;
    ((t_entdata_item *)item->data)->is_picked_up = false;
    ((t_entdata_item *)item->data)->item = type;

    return item;
}

void item_draw(t_game *game, t_entity *item) {
    if (!((t_entdata_item *)item->data)->is_picked_up) {
        blit_tile(game, item->tile, game->scene_offset.x + item->x * (TILE_SIZE * TILE_SCALE), game->scene_offset.y + item->y * (TILE_SIZE * TILE_SCALE) - TILE_SCALE, ANCHOR_TOP_LEFT);
    }
}

void item_free(t_entity *item) {
    free(item->data);
    item->data = NULL;
}
