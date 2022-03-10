//sound.c

#include "sound.h"

void sound_init(t_game *game) {
    
    memset(game->sound.all_sounds, 0, sizeof(Mix_Chunk*) * SND_MAX);
    memset(game->sound.music, 0, sizeof(Mix_Music*) * SND_MAX);
    game->sound.timer = 0;

    game->is_death_sound = false;
    game->is_door_sound = false;

    sound_load(game);
    music_load(game);
}

void sound_load(t_game *game) {
    game->sound.all_sounds[SND_PLAYER_RUN] = Mix_LoadWAV("resource/sounds/walking.wav");
    game->sound.all_sounds[SND_PLAYER_DIE] = Mix_LoadWAV("resource/sounds/death.wav");
    game->sound.all_sounds[SND_DOOR_OPEN] = Mix_LoadWAV("resource/sounds/open_door.wav");
    game->sound.all_sounds[SND_NPC_SPEECH] = Mix_LoadWAV("resource/sounds/speech-announce.wav");
}

void music_load(t_game *game) {
	  game->sound.music[SND_MENU_MUSIC] = Mix_LoadMUS("resource/sounds/main.wav");
	  game->sound.music[SND_LEVEL2_MUSIC] = Mix_LoadMUS("resource/sounds/level02.wav");
}

void music_play(t_game *game, int id) {
	Mix_PlayMusic(game->sound.music[id], -1);
}

void sound_play(t_game *game, int id, int channel) {
	Mix_PlayChannel(channel, game->sound.all_sounds[id], 0);
}

void sound_logic(t_game *game) {
    if (game->sound.timer == 0) game->sound.timer = SDL_GetTicks();

    if (game->control.down == 1 || game->control.up == 1 || game->control.left == 1 || game->control.right == 1) {
        if (SDL_GetTicks() > game->sound.timer + 400) {
            sound_play(game, SND_PLAYER_RUN, CH_PLAYER);
            game->sound.timer = 0;
        }
    }

    if (game->player->is_death && !game->is_death_sound) {
        sound_play(game, SND_PLAYER_DIE, CH_PLAYER);
        game->is_death_sound = true;
    }
}
