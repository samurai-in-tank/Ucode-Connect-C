// door.c

#include "door.h"

t_entity *door_add(t_game *game, char *slag, t_tile otile, t_tile ctile, int x, int y, bool is_locked, t_item required_item, bool is_hidden) {
    t_entity *door = entity_add(game, ENTYPE_DOOR, x, y, ctile, FACING_RIGHT);

    door->slag = slag;

    door->data = malloc(sizeof(t_entdata_door));
    ((t_entdata_door *)door->data)->open = otile;
    ((t_entdata_door *)door->data)->close = ctile;
    ((t_entdata_door *)door->data)->is_locked = is_locked;
    ((t_entdata_door *)door->data)->required_item = required_item;
    ((t_entdata_door *)door->data)->is_hidden = is_hidden;

    return door;
}

void door_logic(t_game *game, t_entity *door) {
    if (false) printf("%p%p", (void *)game->player, (void *)door);

    if (((t_entdata_door *)door->data)->is_locked) {
        door->tile = ((t_entdata_door *)door->data)->close;
    }
    else {
        door->tile = ((t_entdata_door *)door->data)->open;
        if (game->is_door_sound) {
            sound_play(game, SND_DOOR_OPEN, CH_OTHER);
            game->is_door_sound = false;
        }
    }
}

void door_draw(t_game *game, t_entity *door) {
    blit_tile(game, door->tile, game->scene_offset.x + door->x * (TILE_SIZE * TILE_SCALE), game->scene_offset.y + door->y * (TILE_SIZE * TILE_SCALE) - TILE_SCALE, ANCHOR_TOP_LEFT);
}

void door_free(t_entity *door) {
    free(door->data);
    door->data = NULL;
}
