// draw.c

#include "draw.h"

SDL_Texture *loadTexture(t_game *game, char *filename) {
	SDL_Texture *texture;

	texture = IMG_LoadTexture(game->renderer, filename);

	return texture;
}

void blit(t_game *game, SDL_Texture *texture, int x, int y, t_anchor anchor) {
	SDL_Rect dest;

	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

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

	SDL_RenderCopy(game->renderer, texture, NULL, &dest);
}
