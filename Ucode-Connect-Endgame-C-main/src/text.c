// text.c

#include "text.h"

SDL_Texture* text_render(char *message, char *font_file_name, SDL_Color color, int font_size, t_game *game) {
    TTF_Font *font = TTF_OpenFont(font_file_name, font_size);

    SDL_Surface *surf = TTF_RenderUTF8_Blended(font, message, color);

    SDL_Texture *texture = SDL_CreateTextureFromSurface(game->renderer, surf);

    SDL_FreeSurface(surf);
    TTF_CloseFont(font);
    return texture;
}

void text_draw(t_game *game, char *text, int x, int y, int size, t_anchor anchor) {
    SDL_Color color = { 255, 255, 255, 255 };
    SDL_Texture *image = text_render(text, "resource/fonts/font00.ttf", color, size, game);

    SDL_Rect dest;
	dest.x = x;
	dest.y = y;

    SDL_QueryTexture(image, NULL, NULL, &dest.w, &dest.h);

    switch (anchor) {
        case ANCHOR_TOP_LEFT:
            break;

        case ANCHOR_TOP_CENTER:
            dest.x -= (dest.w / 2);
            break;

        case ANCHOR_TOP_RIGHT:
            dest.x -= dest.w;
            break;

        case ANCHOR_CENTER_LEFT:
            dest.y -= (dest.h / 2);
            break;

        case ANCHOR_CENTER_CENTER:
            dest.x -= (dest.w / 2);
            dest.y -= (dest.h / 2);
            break;

        case ANCHOR_CENTER_RIGHT:
            dest.x -= dest.w;
            dest.y -= (dest.h / 2);
            break;

        case ANCHOR_BOTTOM_LEFT:
            dest.y -= dest.h;
            break;

        case ANCHOR_BOTTOM_CENTER:
            dest.x -= (dest.w / 2);
            dest.y -= dest.h;
            break;

        case ANCHOR_BOTTOM_RIGHT:
            dest.x -= dest.w;
            dest.y -= dest.h;
            break;

        default:
            break;
	}

    SDL_QueryTexture(image, NULL, NULL, &dest.w, &dest.h);
    SDL_RenderCopy(game->renderer, image, NULL, &dest);
    SDL_DestroyTexture(image);
}
