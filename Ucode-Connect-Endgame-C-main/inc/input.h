// input.h
#ifndef INPUT_H
#define INPUT_H


#include "common.h"

void input_handle(t_game *game);
void input_keydown(t_game *game, SDL_KeyboardEvent *event);
void input_keyup(t_game *game, SDL_KeyboardEvent *event);


#endif
