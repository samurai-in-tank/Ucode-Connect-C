// init.c

#include "game.h"

t_game *game_init(void) {
	t_game *game = (t_game *) malloc(sizeof(t_game));
	if (game == NULL) return NULL;

	memset(game, 0, sizeof(t_game));

	int rendererFlags, windowFlags;

	rendererFlags = SDL_RENDERER_ACCELERATED;

	windowFlags = 0;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	// load support for the JPG and PNG image formats
	int flags = IMG_INIT_JPG | IMG_INIT_PNG;
	int initted = IMG_Init(flags);
	if ((initted & flags) != flags) {
		printf("IMG_Init: Failed to init required jpg and png support!\n");
		printf("IMG_Init: %s\n", IMG_GetError());
		// handle error
	}

	game->window = SDL_CreateWindow(GAME_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);

	if (!game->window)
	{
		printf("Failed to open %d x %d window: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
		exit(1);
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");

	game->renderer = SDL_CreateRenderer(game->window, -1, rendererFlags);

	if (!game->renderer)
	{
		printf("Failed to create renderer: %s\n", SDL_GetError());
		exit(1);
	}

	game->is_started = false;
	game->entities = NULL;
	game->traps = NULL;
	game->questsys.level = 0;
	game->questsys.stage = 0;
	game->is_finish = false;

	TTF_Init();

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	Mix_AllocateChannels(MAX_SND_CHANNELS);

	return game;
}

void game_free(t_game *game) {
	free(game);
	TTF_Quit();
}
