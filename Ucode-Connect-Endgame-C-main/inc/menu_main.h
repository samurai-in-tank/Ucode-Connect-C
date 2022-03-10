//menu.h

#ifndef MENU_H
#define MENU_H

#include "common.h"
#include "draw.h"
#include "text.h"
#include "sound.h"

void menu_main_init(t_game *game);
void menu_main_logic(t_game *game);
void menu_main_draw(t_game *game);
//void menu_loading_to_game(t_game *game);

#endif

