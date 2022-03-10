// animation.c

#include "animation.h"

t_animation *animation_add(t_entity *entity, int id, t_tile tileset, int tileset_size, int duration, bool is_repeated) {
    t_animation *current = entity->animations;
    t_animation *anim = (t_animation *) malloc(sizeof(t_animation));
    if (anim == NULL) exit(-5);

    memset(anim, 0, sizeof(t_animation));

    anim->id = id;
    anim->tile = &entity->tile;
    anim->tileset = tileset;
    anim->tileset_size = tileset_size;
    anim->duration = duration;
    anim->current_tile = 0;
    anim->timer_start = 0;
    anim->is_playing = false;
    anim->is_repeated = is_repeated;

    if (current != NULL) {
        while (current->next != NULL) {
            current = current->next;
        }

        current->next = anim;
    }
    else {
        entity->animations = anim;
    }

    return anim;
}

void animation_play(t_entity *entity, int id, int start_tile) {
    t_animation *current = entity->animations;
    while (current != NULL) {
        if (current->id == id) break;
        if (current->next == NULL) return;
        current = current->next;
    }

    if (current->is_playing == true) return;

    t_animation *previous = entity->animations;
    while (previous != NULL) {
        if (previous->is_playing == true) {
            previous->is_playing = false;
            break;
        }
        previous = previous->next;
    }

    current->is_playing = true;
    if (start_tile != -1) {
        current->current_tile = start_tile;
    }
}

void animation_reload(t_entity *entity, int id) {
    t_animation *current = entity->animations;
    while (current != NULL) {
        if (current->id == id) break;
        if (current->next == NULL) return;
        current = current->next;
    }

    current->current_tile = 0;
}

void animate(t_entity *entity) {
    t_animation *current = entity->animations;
    while (current != NULL) {
        if (current->is_playing == true) break;
        if (current->next == NULL) return;
        current = current->next;
    }

    if (current->timer_start == 0) {
        current->timer_start = SDL_GetTicks();
        return;
    }

    if (SDL_GetTicks() > current->timer_start + current->duration) {
        if (current->is_repeated) {
            if (current->current_tile >= current->tileset_size) current->current_tile = 0;
        }
        else {
            if (current->current_tile >= current->tileset_size) {
                current->is_playing = false;
                return;
            } 
        }

        *current->tile = set_tile(current->tileset.x / TILE_SIZE + current->current_tile, current->tileset.y / TILE_SIZE);
        current->current_tile++;
        current->timer_start = SDL_GetTicks();
    }
}

int animation_gettime(t_entity *entity, int id) {
    t_animation *current = entity->animations;
    while (current != NULL) {
        if (current->id == id) break;
        if (current->next == NULL) return -1;
        current = current->next;
    }

    return current->duration * current->tileset_size;
}

void animations_free(t_entity *entity) {
    while (entity->animations != NULL) {
        t_animation *next = NULL;
        next = entity->animations->next;

        free(entity->animations);
        entity->animations = next;
    }

	entity->animations = NULL;
}
