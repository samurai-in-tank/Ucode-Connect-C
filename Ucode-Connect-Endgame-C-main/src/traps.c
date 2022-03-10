// traps.c

#include "traps.h"

t_trap *trap_add(t_game * game, t_tile tile, t_tile active_tile, int x1, int y1, int x2, int y2, t_trap_type type, int delay) {
    t_trap *current = game->traps;
    t_trap *trap = (t_trap *) malloc(sizeof(t_trap));
    if (trap == NULL) exit(-1);

    memset(trap, 0, sizeof(t_trap));

    trap->delay = delay;
    trap->tile = tile;
    trap->active_tile = active_tile;
    trap->type = type;
    trap->x1 = x1 * TILE_SIZE * TILE_SCALE;
    trap->y1 = y1 * TILE_SIZE * TILE_SCALE;
    trap->x2 = x2 * TILE_SIZE * TILE_SCALE;
    trap->y2 = y2 * TILE_SIZE * TILE_SCALE;
    trap->timer = 0;
    trap->next = NULL;

    if (current != NULL) {
        while (current->next != NULL) {
            current = current->next;
        }

        current->next = trap;
    }
    else {
        game->traps = trap;
    }

    return trap;
}

void trap_logic(t_game *game) {
    t_trap *current = game->traps;

    while (current != NULL) {
        if (current->x1 == (0) || current->y1 == (0) || current->x2 == (0) || current->y2 == (0)) {
            current = current->next;
            continue;
        }

        switch (current->type) {
        case TRAP_TRIGGER:
            trap_trigger(game, current);
            break;
        
        case TRAP_GLIMMER:
            trap_glimmer(game, current);
            break;
        
        default:
            break;
        }

        current = current->next;
    }
}

void trap_draw(t_game *game) {
	double tX1 = 0, tY1 = 0, tX2 = 0, tY2 = 0;

    t_trap *current = game->traps;

    while (current != NULL) {
        if (current->x1 == (0) || current->y1 == (0) || current->x2 == (0) || current->y2 == (0)) {
            current = current->next;
            continue;
        }

        int to_tile = TILE_SIZE * TILE_SCALE;
        tX1 = current->x1 / to_tile;
        tY1 = current->y1 / to_tile;
        tX2 = current->x2 / to_tile;
        tY2 = current->y2 / to_tile;

        if (current->activated == true) {
            for (int i = tY1; i <= tY2; i++) {
                for (int j = tX1; j <= tX2; j++) {
                    blit_tile(game, current->active_tile, game->scene_offset.x + j * to_tile, game->scene_offset.y + i * to_tile, false);
                }
            }
        }
        else {
            for (int i = tY1; i <= tY2; i++) {
                for (int j = tX1; j <= tX2; j++) {
                    blit_tile(game, current->tile, game->scene_offset.x + j * to_tile, game->scene_offset.y + i * to_tile, false);
                }
            }
        }

        current = current->next;
    }
}

void trap_free(t_game *game) {
    while (game->traps != NULL) {
        t_trap *next_node = NULL;
        next_node = game->traps->next;

        free(game->traps);
        game->traps = next_node;
    }

	game->traps = NULL;
}

/*==========================================================================
                            Types traps
==========================================================================*/

void trap_trigger(t_game *game, t_trap *current) {
    int to_tile = TILE_SIZE * TILE_SCALE;
    int pX = game->player->x / to_tile;
    int pY = game->player->y / to_tile;
    int tX1 = current->x1 / to_tile;
    int tY1 = current->y1 / to_tile;
    int tX2 = current->x2 / to_tile;
    int tY2 = current->y2 / to_tile;
    current->activated = false;

    for (int i = tY1; i <= tY2; i++) {
        for (int j = tX1; j <= tX2; j++) {
            if (pX == j && pY == i && game->dev_mode.god == false) {
                current->activated = true;
                game->player->is_death = true;
            }
        }
    }
}

void trap_glimmer(t_game *game, t_trap *current) {
    int to_tile = TILE_SIZE * TILE_SCALE;
    int pX = game->player->x / to_tile;
    int pY = game->player->y / to_tile;
    int tX1 = current->x1 / to_tile;
    int tY1 = current->y1 / to_tile;
    int tX2 = current->x2 / to_tile;
    int tY2 = current->y2 / to_tile;

    if (current->timer == 0) current->timer = SDL_GetTicks();

    if (SDL_GetTicks() > current->timer + current->delay) {
        current->activated = false;

        if (SDL_GetTicks() > current->timer + current->delay * 2) current->timer = SDL_GetTicks();
    }
    else {
        current->activated = true;
    }

    for (int i = tY1; i <= tY2; i++) {
        for (int j = tX1; j <= tX2; j++) {
            if (pX == j && pY == i && current->activated == true && game->dev_mode.god == false) {
                game->player->is_death = true;
            }
        }
    }
}
