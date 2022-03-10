//sound.h

#ifndef SOUND_H
#define SOUND_H


#include "common.h"

void sound_init(t_game *game);
void sound_load(t_game *game);
void music_load(t_game *game);
void music_play(t_game *game,  int id);
void sound_play(t_game *game, int id, int channel);
void sound_logic(t_game *game);

#endif
