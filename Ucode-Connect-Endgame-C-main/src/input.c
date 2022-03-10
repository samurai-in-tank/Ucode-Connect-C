// input.c

#include "input.h"

void input_handle(t_game *game) {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				exit(0);
				break;

			case SDL_KEYDOWN:
				input_keydown(game, &event.key);
				break;

			case SDL_KEYUP:
				input_keyup(game, &event.key);
				break;

			default:
				break;
		}
	}

	if (game->control.is_locked) {
		game->control.up = 0;
		game->control.down = 0;
		game->control.left = 0;
		game->control.right = 0;
		game->control.use = 0;
	}
}

void input_keydown(t_game *game, SDL_KeyboardEvent *event) {
	if (event->repeat == 0) {
		if (((event->keysym.scancode == SDL_SCANCODE_UP) || (event->keysym.scancode == SDL_SCANCODE_W)) && !game->control.is_locked) {
			game->control.up = 1;
		}

		if (((event->keysym.scancode == SDL_SCANCODE_DOWN) || (event->keysym.scancode == SDL_SCANCODE_S)) && !game->control.is_locked) {
			game->control.down = 1;
		}

		if (((event->keysym.scancode == SDL_SCANCODE_LEFT) || (event->keysym.scancode == SDL_SCANCODE_A)) && !game->control.is_locked) {
			game->control.left = 1;
		}

		if (((event->keysym.scancode == SDL_SCANCODE_RIGHT) || (event->keysym.scancode == SDL_SCANCODE_D)) && !game->control.is_locked) {
			game->control.right = 1;
		}

		if (((event->keysym.scancode == SDL_SCANCODE_RIGHT) || (event->keysym.scancode == SDL_SCANCODE_F)) && !game->control.is_locked) {
			game->control.use = 1;
		}

		if (event->keysym.scancode == SDL_SCANCODE_D) {
			game->control.D = true;
		}

		if (event->keysym.scancode == SDL_SCANCODE_E) {
			game->control.E = true;
		}

		if (event->keysym.scancode == SDL_SCANCODE_V) {
			game->control.V = true;
		}

		if (game->control.D && game->control.E && game->control.V) {
			game->dev_mode.im_dev = true;
		}

		if (event->keysym.scancode == SDL_SCANCODE_K && game->dev_mode.im_dev) {
			game->dev_mode.skip = true;
		}
	}
}

void input_keyup(t_game *game, SDL_KeyboardEvent *event) {
	if (event->repeat == 0) {
		if ((event->keysym.scancode == SDL_SCANCODE_UP) || (event->keysym.scancode == SDL_SCANCODE_W)) {
			game->control.up = 0;
		}

		if ((event->keysym.scancode == SDL_SCANCODE_DOWN) || (event->keysym.scancode == SDL_SCANCODE_S)) {
			game->control.down = 0;
		}

		if ((event->keysym.scancode == SDL_SCANCODE_LEFT) || (event->keysym.scancode == SDL_SCANCODE_A)) {
			game->control.left = 0;
		}

		if ((event->keysym.scancode == SDL_SCANCODE_RIGHT) || (event->keysym.scancode == SDL_SCANCODE_D)) {
			game->control.right = 0;
		}

		if ((event->keysym.scancode == SDL_SCANCODE_RIGHT) || (event->keysym.scancode == SDL_SCANCODE_F)) {
			game->control.use = 0;
		}

		if (event->keysym.scancode == SDL_SCANCODE_ESCAPE && !game->control.start) {
			exit(0);
		}

		if (event->keysym.scancode == SDL_SCANCODE_RETURN) {
			game->control.start = true;
		}

		if (event->keysym.scancode == SDL_SCANCODE_SPACE && game->game_over_screen) {
			game->player->is_death = false;
		}

		if (event->keysym.scancode == SDL_SCANCODE_D) {
			game->control.D = false;
		}

		if (event->keysym.scancode == SDL_SCANCODE_E) {
			game->control.E = false;
		}

		if (event->keysym.scancode == SDL_SCANCODE_V) {
			game->control.V = false;
		}

		if (event->keysym.scancode == SDL_SCANCODE_G && !game->player->is_death) {
			game->dev_mode.god = !game->dev_mode.god;
		}

		if (event->keysym.scancode == SDL_SCANCODE_N && game->dev_mode.im_dev) {
			game->dev_mode.noclip = !game->dev_mode.noclip;
		}

		if (event->keysym.scancode == SDL_SCANCODE_K && game->dev_mode.im_dev) {
			game->dev_mode.skip = false;
		}

		if (event->keysym.scancode == SDL_SCANCODE_KP_PLUS && game->dev_mode.im_dev) {
			game->dev_mode.acceleration += 5;
		}

		if (event->keysym.scancode == SDL_SCANCODE_KP_MINUS && game->dev_mode.im_dev) {
			game->dev_mode.acceleration -= 5;
		}
	}
}
