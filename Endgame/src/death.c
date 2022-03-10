#include "death.h"

void death_init(t_game *game) {
    SDL_Point *spawn = (SDL_Point *) malloc(sizeof(SDL_Point));
    memset(spawn, 0, sizeof(SDL_Point));

    spawn->x = 0;
    spawn->y = 0;
    game->spawn = spawn;
    game->death_timer = 0;
}

void death_logic(t_game *game) {

    if (game->player->is_death && game->dev_mode.god == false) {
        animation_play(game->player, 4, -1);
        game->game_over_screen = false;
        game->control.down = 0;
        game->control.up = 0;
        game->control.left = 0;
        game->control.right = 0;

        if (game->death_timer == 0) game->death_timer = SDL_GetTicks();

        if (SDL_GetTicks() > game->death_timer + animation_gettime(game->player, 4) + TIME_AFTER_DEATH) {
            game->player->x = game->spawnpoint.x * (TILE_SIZE * TILE_SCALE);
            game->player->y = game->spawnpoint.y * (TILE_SIZE * TILE_SCALE);
            game->game_over_screen = true;
            animation_reload(game->player, 4);
        }
    }
    else {
        game->death_timer = SDL_GetTicks();
        game->is_death_sound = false;
    }
    
}

void death_draw(t_game *game) {
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = SCREEN_WIDTH;
    rect.h = SCREEN_HEIGHT;
    if (game->player->is_death && SDL_GetTicks() > game->death_timer + animation_gettime(game->player, 4) + TIME_AFTER_DEATH) {
        SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 0);
        SDL_RenderFillRect(game->renderer, &rect);

        text_draw(game, "GAME OVER", SCREEN_WIDTH / 2,  SCREEN_HEIGHT / 2 - 20, 144, ANCHOR_BOTTOM_CENTER);
        text_draw(game, "Нажмите [SPACE] чтобы возродиться", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 20, 24, ANCHOR_TOP_CENTER);
    }
}

void death_free(t_game *game) {
    free(game->spawn);
	game->spawn = NULL;
}
