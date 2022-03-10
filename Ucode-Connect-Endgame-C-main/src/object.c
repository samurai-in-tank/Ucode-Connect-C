// object.c

#include "object.h"

t_entity *object_add(t_game *game, char *slag, t_tile start_tile, t_tile finish_tile, int x, int y, bool is_active, t_item required_item, int delay, bool is_obstacle) {
    t_entity *obj = entity_add(game, ENTYPE_OBJECT, x, y, start_tile, FACING_RIGHT);

    obj->data = malloc(sizeof(t_entdata_object));

    obj->slag = slag;

    t_entdata_object *data = (t_entdata_object *)obj->data;

    data->start_tile = start_tile;
    data->finish_tile = finish_tile;
    data->is_active = is_active;
    data->is_used = false;
    data->required_item = required_item;
    data->timer = 0;
    data->is_obstacle = true;
    data->delay = delay;
    data->is_using = false;
    data->is_obstacle = is_obstacle;

    return obj;
}

void object_logic(t_game *game, t_entity *obj) {
    t_entdata_object *data = (t_entdata_object *)obj->data;

    if (data->is_used || data->delay <= 0 || !data->is_using) return;

    if (data->timer == 0) {
        data->timer = SDL_GetTicks();
        return;
    }

    game->control.is_locked = true;

    if (SDL_GetTicks() > data->timer + data->delay) {
        game->control.is_locked = false;
        data->is_using = false;
        data->is_used = true;
    }
}

void object_draw(t_game *game, t_entity *obj) {
    if (!((t_entdata_object *)obj->data)->is_used) {
        blit_tile(game, ((t_entdata_object *)obj->data)->start_tile, game->scene_offset.x + obj->x * (TILE_SIZE * TILE_SCALE), game->scene_offset.y + obj->y * (TILE_SIZE * TILE_SCALE) - TILE_SCALE, ANCHOR_TOP_LEFT);
    }
    else {
        blit_tile(game, ((t_entdata_object *)obj->data)->finish_tile, game->scene_offset.x + obj->x * (TILE_SIZE * TILE_SCALE), game->scene_offset.y + obj->y * (TILE_SIZE * TILE_SCALE) - TILE_SCALE, ANCHOR_TOP_LEFT);
    }
}

void object_free(t_entity *obj) {
    free(obj->data);
    obj->data = NULL;
}
