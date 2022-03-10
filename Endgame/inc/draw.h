// draw.h
#ifndef DRAW_H
#define DRAW_H


#include "common.h"
#include "SDL2/SDL_image.h"

void scene_prepare(t_game *game);
void scene_present(t_game *game);

SDL_Texture *loadTexture(t_game *game, char *filename);
void blit(t_game *game, SDL_Texture *texture, int x, int y, t_anchor anchor);


#endif
