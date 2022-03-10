//menu.c

#include "menu_main.h"
#include "SDL2_gfxPrimitives.h"
void menu_main_init(t_game *game) {
    game->control.start = 0;
    game->death_timer = 0;
    game->main_menu_texture = IMG_LoadTexture(game->renderer, "resource/sprites/menu_background.jpg");
}

void menu_main_draw(t_game *game) {
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = SCREEN_WIDTH;
    rect.h = SCREEN_HEIGHT / 3;

    if (game->control.start == 0) {
        //blit(game, game->main_menu_texture, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 1.75, ANCHOR_CENTER_CENTER);
        //SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 0);
        //SDL_RenderFillRect(game->renderer, &rect);

        rect.y = SCREEN_HEIGHT / 1.5;
        rect.w = SCREEN_WIDTH;
        rect.h = SCREEN_HEIGHT;
       
        //--------------------------------------------------------------------------------------------------------//
        //SDL objeckt on form  Login
        boxRGBA (game->renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 5, 50, 80, 255);
        text_draw(game, "Cop`n'Past Games Studia", SCREEN_WIDTH / 2,  SCREEN_HEIGHT / 2 - 300, 48, ANCHOR_BOTTOM_CENTER);        

        boxRGBA (game->renderer, SCREEN_WIDTH / 3, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 1.5, SCREEN_HEIGHT / 4+50,  95, 120, 135, 255);
        text_draw(game, "Enter you login", SCREEN_WIDTH / 2-120,  SCREEN_HEIGHT / 3.3, 24, ANCHOR_BOTTOM_CENTER);
        
        boxRGBA (game->renderer, SCREEN_WIDTH / 3, SCREEN_HEIGHT / 2.5, SCREEN_WIDTH / 1.5, SCREEN_HEIGHT / 2.5+50,  95, 120, 135, 255);
        text_draw(game, "Enter you password", SCREEN_WIDTH / 2-100,  SCREEN_HEIGHT / 2.5+40, 24, ANCHOR_BOTTOM_CENTER);
        
        boxRGBA (game->renderer, SCREEN_WIDTH / 3, SCREEN_HEIGHT / 2, SCREEN_WIDTH / 1.5, SCREEN_HEIGHT / 2+50,  95, 120, 135, 255);
        text_draw(game, "Repeat you pasword", SCREEN_WIDTH / 2-100,  SCREEN_HEIGHT / 2+40, 24, ANCHOR_BOTTOM_CENTER);

        boxRGBA (game->renderer, SCREEN_WIDTH / 2.5, SCREEN_HEIGHT / 1.5, SCREEN_WIDTH / 1.75, SCREEN_HEIGHT / 1.5+50,  10, 120, 135, 255);
        text_draw(game, "Login", SCREEN_WIDTH / 2-20,  SCREEN_HEIGHT / 1.5+40, 24, ANCHOR_BOTTOM_CENTER);

        boxRGBA (game->renderer, SCREEN_WIDTH / 2.5, SCREEN_HEIGHT /1.25, SCREEN_WIDTH / 1.75, SCREEN_HEIGHT / 1.25+50,  10, 120, 135, 255);
        text_draw(game, "Registration", SCREEN_WIDTH / 2-15,  SCREEN_HEIGHT / 1.25+40, 24, ANCHOR_BOTTOM_CENTER);
        //--------------------------------------------------------------------------------------------------------//
        
        rect.y = 0;
        rect.w = SCREEN_WIDTH;
        rect.h = SCREEN_HEIGHT;
    }
    else {
        if (game->death_timer == 0 && game->control.start) game->death_timer = SDL_GetTicks();

        if (SDL_GetTicks() < game->death_timer + 3000 && game->control.start) {
            SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 0);
            SDL_RenderFillRect(game->renderer, &rect);
            text_draw(game, "Загрузка...", SCREEN_WIDTH - 20, SCREEN_HEIGHT - 20, 24, ANCHOR_BOTTOM_RIGHT);
        }

        if (SDL_GetTicks() > game->death_timer + 3000) {
            Mix_PauseMusic();
            music_play(game, SND_LEVEL2_MUSIC);
            game->death_timer = 0;
            game->is_started = true;
        }
    }
    
    
    

    
}
