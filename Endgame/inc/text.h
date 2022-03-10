// text.h
#ifndef TEXT_H
#define TEXT_H


#include "common.h"
#include "draw.h"

SDL_Texture* text_render(char *message, char *font_file_name, SDL_Color color, int font_size, t_game *game);
void text_draw(t_game *game, char *text, int x, int y, int size, t_anchor anchor);

#endif
