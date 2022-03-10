// map.c

#include "map.h"

void map_init(t_game *game, char *filename) {
	FILE *map_file = fopen(filename, "r");
	if (map_file == NULL) exit(-1);
    
	t_map *map = (t_map *) malloc(sizeof(t_map));
	if (map == NULL) exit(-1);

	fscanf(map_file, "%d", &map->size.x);
	fscanf(map_file, "%d", &map->size.y);

	fscanf(map_file, "%d", &map->offset.x);
	fscanf(map_file, "%d", &map->offset.y);

	map->data = (int **) malloc(map->size.x * sizeof(int *));
	if (map->data == NULL) exit(-1);
	for (int i = 0; i < map->size.x; i++) {
		map->data[i] = (int *) malloc(map->size.y * sizeof(int));
		if (map->data[i] == NULL) exit(-1);
	}
	
    for (int i = 0; i < map->size.y; i++) {
		for (int j = 0; j < map->size.x; j++) {
			if(feof(map_file)) exit(1);
			fscanf(map_file, "%d", &map->data[j][i]);
		}
	}

    fclose(map_file);

	game->map = map;

	// game->map = (t_map *) malloc(sizeof(t_map));
	// game->map->size.x = MAP_WIDTH;
	// game->map->size.y = MAP_HEIGHT;
	// game->map->offset.x = 0;
	// game->map->offset.y = 0;

	// game->map->data = (int **) malloc(game->map->size.x * sizeof(int *));
	// if (game->map->data == NULL) exit(-1);
	// for (int i = 0; i < game->map->size.x; i++) {
	// 	game->map->data[i] = (int *) malloc(game->map->size.y * sizeof(int));
	// 	if (game->map->data[i] == NULL) exit(-1);
	// }


	// srand(141);

	// int x, y;
	// for (x = 0; x < MAP_WIDTH; x++) {
	// 	for (y = 0; y < MAP_HEIGHT; y++) {
	// 		game->map->data[x][y] = TILE_GROUND;

	// 		if (rand() % 25 == 0)
	// 		{
	// 			game->map->data[x][y] = TILE_HOLE;
	// 		}

	// 		if (rand() % 30 == 0)
	// 		{
	// 			game->map->data[x][y] = TILE_WALL;
	// 		}
	// 	}
	// }
	// for (x = 0; x < MAP_WIDTH; x++) {
	// 	game->map->data[x][MAP_HEIGHT - 1] = TILE_WALL_FRONT;
	// }
}

void map_draw(t_game* game) {
	int x, y, n;

	for (y = 0; y < game->map->size.y; y++)
	{
		for (x = 0; x < game->map->size.x; x++)
		{
			n = game->map->data[x][y];
			t_tile tile = set_tile(0, 0);
			switch (n)
			{
      
			case TILE_GROUND:
				tile = set_tile(6, 0);
				blit_tile(game, tile, game->scene_offset.x + x * TILE_SIZE * TILE_SCALE, game->scene_offset.y + y * TILE_SIZE * TILE_SCALE - TILE_SCALE,  ANCHOR_TOP_LEFT);
				break;
			case TILE_WALL:
				tile = set_tile(11, 3);
				blit_tile(game, tile, game->scene_offset.x + x * TILE_SIZE * TILE_SCALE, game->scene_offset.y + y * TILE_SIZE * TILE_SCALE - TILE_SCALE, ANCHOR_TOP_LEFT);
				break;
     //*********LAB Location sprite*******
			case TILE_WALL_FRONT:
				tile = set_tile(9,7);
				blit_tile(game, tile, game->scene_offset.x + x * TILE_SIZE * TILE_SCALE, game->scene_offset.y + y * TILE_SIZE * TILE_SCALE - TILE_SCALE, ANCHOR_TOP_LEFT);
				break;

			case TILE_LAB_LEFT_CORNER_UP :
				tile = set_tile(8, 3);
				blit_tile(game, tile, game->scene_offset.x + x * TILE_SIZE * TILE_SCALE, game->scene_offset.y + y * TILE_SIZE * TILE_SCALE - TILE_SCALE, ANCHOR_TOP_LEFT);
				break;

			case TILE_LAB_RIGHT_CORNER_DOWN:
				tile = set_tile(10, 5);
				blit_tile(game, tile, game->scene_offset.x + x * TILE_SIZE * TILE_SCALE, game->scene_offset.y + y * TILE_SIZE * TILE_SCALE - TILE_SCALE, ANCHOR_TOP_LEFT);
				break;
			case TILE_LAB_RIGHT_CORNER_UP:
				tile = set_tile(10, 3);
				blit_tile(game, tile, game->scene_offset.x + x * TILE_SIZE * TILE_SCALE, game->scene_offset.y + y * TILE_SIZE * TILE_SCALE - TILE_SCALE, ANCHOR_TOP_LEFT);
				break;

			case TILE_LAB_WALL:
				tile = set_tile(9, 5);
				blit_tile(game, tile, game->scene_offset.x + x * TILE_SIZE * TILE_SCALE, game->scene_offset.y + y * TILE_SIZE * TILE_SCALE - TILE_SCALE, ANCHOR_TOP_LEFT);
				break;
			case TILE_LAB_WALL_FRONT :
				tile = set_tile(9, 3);
				blit_tile(game, tile, game->scene_offset.x + x * TILE_SIZE * TILE_SCALE, game->scene_offset.y + y * TILE_SIZE * TILE_SCALE - TILE_SCALE, ANCHOR_TOP_LEFT);
				break;
			case TILE_LAB_FLOOR :
				tile = set_tile(9, 4);
				blit_tile(game, tile, game->scene_offset.x + x * TILE_SIZE * TILE_SCALE, game->scene_offset.y + y * TILE_SIZE * TILE_SCALE - TILE_SCALE, ANCHOR_TOP_LEFT);
				break;
			case TILE_LAB_WALL_LINER_LEFT:
				tile = set_tile(8, 4);
				blit_tile(game, tile, game->scene_offset.x + x * TILE_SIZE * TILE_SCALE, game->scene_offset.y + y * TILE_SIZE * TILE_SCALE - TILE_SCALE, ANCHOR_TOP_LEFT);
				break;
			case TILE_LAB_WALL_LINER_RIGHT:
				tile = set_tile(10, 4);
				blit_tile(game, tile, game->scene_offset.x + x * TILE_SIZE * TILE_SCALE, game->scene_offset.y + y * TILE_SIZE * TILE_SCALE - TILE_SCALE, ANCHOR_TOP_LEFT);
				break;
			
			case TILE_LAB_LEFT_CORNER_DOWN :
				tile = set_tile(8, 5);
				blit_tile(game, tile, game->scene_offset.x + x * TILE_SIZE * TILE_SCALE, game->scene_offset.y + y * TILE_SIZE * TILE_SCALE - TILE_SCALE, ANCHOR_TOP_LEFT);
				break;
	//********MIL location sprite*********
			case TILE_MIL_LEFT_CORNER_UP :
				tile = set_tile(10, 6);
				blit_tile(game, tile, game->scene_offset.x + x * TILE_SIZE * TILE_SCALE, game->scene_offset.y + y * TILE_SIZE * TILE_SCALE - TILE_SCALE, ANCHOR_TOP_LEFT);
				break;

			case TILE_MIL_RIGHT_CORNER_DOWN:
				tile = set_tile(10, 5);
				blit_tile(game, tile, game->scene_offset.x + x * TILE_SIZE * TILE_SCALE, game->scene_offset.y + y * TILE_SIZE * TILE_SCALE - TILE_SCALE, ANCHOR_TOP_LEFT);
				break;
			case TILE_MIL_RIGHT_CORNER_UP:
				tile = set_tile(10, 3);
				blit_tile(game, tile, game->scene_offset.x + x * TILE_SIZE * TILE_SCALE, game->scene_offset.y + y * TILE_SIZE * TILE_SCALE - TILE_SCALE, ANCHOR_TOP_LEFT);
				break;

			case TILE_MIL_WALL:
				tile = set_tile(11, 6);
				blit_tile(game, tile, game->scene_offset.x + x * TILE_SIZE * TILE_SCALE, game->scene_offset.y + y * TILE_SIZE * TILE_SCALE - TILE_SCALE, ANCHOR_TOP_LEFT);
				break;
			case TILE_MIL_WALL_FRONT :
			    tile = set_tile(11, 8);
				blit_tile(game, tile, game->scene_offset.x + x * TILE_SIZE * TILE_SCALE, game->scene_offset.y + y * TILE_SIZE * TILE_SCALE - TILE_SCALE, ANCHOR_TOP_LEFT);
				break;
			case TILE_MIL_FLOOR :
				tile = set_tile(9, 4);
				blit_tile(game, tile, game->scene_offset.x + x * TILE_SIZE * TILE_SCALE, game->scene_offset.y + y * TILE_SIZE * TILE_SCALE - TILE_SCALE, ANCHOR_TOP_LEFT);
				break;
			case TILE_MIL_WALL_LINER_LEFT:
				tile = set_tile(10,7);
				blit_tile(game, tile, game->scene_offset.x + x * TILE_SIZE * TILE_SCALE, game->scene_offset.y + y * TILE_SIZE * TILE_SCALE - TILE_SCALE, ANCHOR_TOP_LEFT);
				break;
			case TILE_MIL_WALL_LINER_RIGHT:
				tile = set_tile(12, 7);
				blit_tile(game, tile, game->scene_offset.x + x * TILE_SIZE * TILE_SCALE, game->scene_offset.y + y * TILE_SIZE * TILE_SCALE - TILE_SCALE, ANCHOR_TOP_LEFT);
				break;
			
			case TILE_MIL_LEFT_CORNER_DOWN :
				tile = set_tile(9, 11);
				blit_tile(game, tile, game->scene_offset.x + x * TILE_SIZE * TILE_SCALE, game->scene_offset.y + y * TILE_SIZE * TILE_SCALE - TILE_SCALE, ANCHOR_TOP_LEFT);
				break;	

			case TILE_MILL_ROOF :
				tile = set_tile(11, 3);
				blit_tile(game, tile, game->scene_offset.x + x * TILE_SIZE * TILE_SCALE, game->scene_offset.y + y * TILE_SIZE * TILE_SCALE - TILE_SCALE, ANCHOR_TOP_LEFT);
				break;
				//********MIL location sprite INSIDE*********
			case MIL_LEFT_CORNER_UP  :
				tile = set_tile(10, 9);
				blit_tile(game, tile, game->scene_offset.x + x * TILE_SIZE * TILE_SCALE, game->scene_offset.y + y * TILE_SIZE * TILE_SCALE - TILE_SCALE, ANCHOR_TOP_LEFT);
				break;
			case  MIL_FLOOR  :
				tile = set_tile(11, 13);
				blit_tile(game, tile, game->scene_offset.x + x * TILE_SIZE * TILE_SCALE, game->scene_offset.y + y * TILE_SIZE * TILE_SCALE - TILE_SCALE, ANCHOR_TOP_LEFT);
				break;
				case  MIL_LEFT_CORNER_DOWN   :
				tile = set_tile(10, 11);
				blit_tile(game, tile, game->scene_offset.x + x * TILE_SIZE * TILE_SCALE, game->scene_offset.y + y * TILE_SIZE * TILE_SCALE - TILE_SCALE, ANCHOR_TOP_LEFT);
				break;
				case MIL_RIGHT_CORNER_UP  :
				tile = set_tile(12, 9);
				blit_tile(game, tile, game->scene_offset.x + x * TILE_SIZE * TILE_SCALE, game->scene_offset.y + y * TILE_SIZE * TILE_SCALE - TILE_SCALE, ANCHOR_TOP_LEFT);
				break;
				case  MIL_WALL_FRONT  :
				tile = set_tile(11, 11);
				blit_tile(game, tile, game->scene_offset.x + x * TILE_SIZE * TILE_SCALE, game->scene_offset.y + y * TILE_SIZE * TILE_SCALE - TILE_SCALE, ANCHOR_TOP_LEFT);
				break;
				case MIL_RIGHT_CORNER_DOWN :
					tile = set_tile(12, 11);
				blit_tile(game, tile, game->scene_offset.x + x * TILE_SIZE * TILE_SCALE, game->scene_offset.y + y * TILE_SIZE * TILE_SCALE - TILE_SCALE, ANCHOR_TOP_LEFT);
				break;
				case  MIL_WALL  :
				tile = set_tile(11, 9);
				blit_tile(game, tile, game->scene_offset.x + x * TILE_SIZE * TILE_SCALE, game->scene_offset.y + y * TILE_SIZE * TILE_SCALE - TILE_SCALE, ANCHOR_TOP_LEFT);
				break;
				case WALL_LINER_LEFT_I   :
				tile = set_tile(10, 10);
				blit_tile(game, tile, game->scene_offset.x + x * TILE_SIZE * TILE_SCALE, game->scene_offset.y + y * TILE_SIZE * TILE_SCALE - TILE_SCALE, ANCHOR_TOP_LEFT);
				break;
				case WALL_LINER_RIGHT   :
				tile = set_tile(12, 10);
				blit_tile(game, tile, game->scene_offset.x + x * TILE_SIZE * TILE_SCALE, game->scene_offset.y + y * TILE_SIZE * TILE_SCALE - TILE_SCALE, ANCHOR_TOP_LEFT);
				break;
				//PLANTS
				case CACTUS   :
				tile = set_tile(6, 13);
				blit_tile(game, tile, game->scene_offset.x + x * TILE_SIZE * TILE_SCALE, game->scene_offset.y + y * TILE_SIZE * TILE_SCALE - TILE_SCALE, ANCHOR_TOP_LEFT);
				break;
				case PERECATI_POLE   :
				tile = set_tile(7, 12);
				blit_tile(game, tile, game->scene_offset.x + x * TILE_SIZE * TILE_SCALE, game->scene_offset.y + y * TILE_SIZE * TILE_SCALE - TILE_SCALE, ANCHOR_TOP_LEFT);
				break;
				case CACTUS_1   :
				tile = set_tile(5 ,12);
				blit_tile(game, tile, game->scene_offset.x + x * TILE_SIZE * TILE_SCALE, game->scene_offset.y + y * TILE_SIZE * TILE_SCALE - TILE_SCALE, ANCHOR_TOP_LEFT);
				break;
				case CACTUS_2   :
				tile = set_tile(5, 13);
				blit_tile(game, tile, game->scene_offset.x + x * TILE_SIZE * TILE_SCALE, game->scene_offset.y + y * TILE_SIZE * TILE_SCALE - TILE_SCALE, ANCHOR_TOP_LEFT);
				break;
				case ROCK   :
				tile = set_tile(9, 12);
				blit_tile(game, tile, game->scene_offset.x + x * TILE_SIZE * TILE_SCALE, game->scene_offset.y + y * TILE_SIZE * TILE_SCALE - TILE_SCALE, ANCHOR_TOP_LEFT);
				break;
				case ROCK_FLOOR   :
				tile = set_tile(11, 13);
				blit_tile(game, tile, game->scene_offset.x + x * TILE_SIZE * TILE_SCALE, game->scene_offset.y + y * TILE_SIZE * TILE_SCALE - TILE_SCALE, ANCHOR_TOP_LEFT);
				break;

				case ROCK_WALL_FRONT   :
				tile = set_tile(11, 14);
				blit_tile(game, tile, game->scene_offset.x + x * TILE_SIZE * TILE_SCALE, game->scene_offset.y + y * TILE_SIZE * TILE_SCALE - TILE_SCALE, ANCHOR_TOP_LEFT);
				break;
					case ROCK_WALL_FRONT_L_CORNNER :
				tile = set_tile(11, 13);
				blit_tile(game, tile, game->scene_offset.x + x * TILE_SIZE * TILE_SCALE, game->scene_offset.y + y * TILE_SIZE * TILE_SCALE - TILE_SCALE, ANCHOR_TOP_LEFT);
				break;

					case ROCK_WALL_LEFT :
				tile = set_tile(11, 13);
				blit_tile(game, tile, game->scene_offset.x + x * TILE_SIZE * TILE_SCALE, game->scene_offset.y + y * TILE_SIZE * TILE_SCALE - TILE_SCALE, ANCHOR_TOP_LEFT);
				break;

					case ROCK_WALL_RIGH :
				tile = set_tile(12, 13);
				blit_tile(game, tile, game->scene_offset.x + x * TILE_SIZE * TILE_SCALE, game->scene_offset.y + y * TILE_SIZE * TILE_SCALE - TILE_SCALE, ANCHOR_TOP_LEFT);
				break;
				case NETRAN   :
				tile = set_tile(1, 14);
				blit_tile(game, tile, game->scene_offset.x + x * TILE_SIZE * TILE_SCALE, game->scene_offset.y + y * TILE_SIZE * TILE_SCALE - TILE_SCALE, ANCHOR_TOP_LEFT);
				break;
	            case bottle   :
				tile = set_tile(0, 12);
				blit_tile(game, tile, game->scene_offset.x + x * TILE_SIZE * TILE_SCALE, game->scene_offset.y + y * TILE_SIZE * TILE_SCALE - TILE_SCALE, ANCHOR_TOP_LEFT);
				break;
				case bottle_empty   :
				tile = set_tile(1, 12);
				blit_tile(game, tile, game->scene_offset.x + x * TILE_SIZE * TILE_SCALE, game->scene_offset.y + y * TILE_SIZE * TILE_SCALE - TILE_SCALE, ANCHOR_TOP_LEFT);
				break;
				case trash   :
				tile = set_tile(1, 13);
				blit_tile(game, tile, game->scene_offset.x + x * TILE_SIZE * TILE_SCALE, game->scene_offset.y + y * TILE_SIZE * TILE_SCALE - TILE_SCALE, ANCHOR_TOP_LEFT);
				break;
				case trash2   :
				tile = set_tile(4, 12);
				blit_tile(game, tile, game->scene_offset.x + x * TILE_SIZE * TILE_SCALE, game->scene_offset.y + y * TILE_SIZE * TILE_SCALE - TILE_SCALE, ANCHOR_TOP_LEFT);
				break;
				case comp   :
				tile = set_tile(5 ,14);
				blit_tile(game, tile, game->scene_offset.x + x * TILE_SIZE * TILE_SCALE, game->scene_offset.y + y * TILE_SIZE * TILE_SCALE - TILE_SCALE, ANCHOR_TOP_LEFT);
				break;
				case trava   :
				tile = set_tile(4 ,13);
				blit_tile(game, tile, game->scene_offset.x + x * TILE_SIZE * TILE_SCALE, game->scene_offset.y + y * TILE_SIZE * TILE_SCALE - TILE_SCALE, ANCHOR_TOP_LEFT);
				break;


			default:
				blit_tile(game, tile, game->scene_offset.x + x * TILE_SIZE * TILE_SCALE, game->scene_offset.y + y * TILE_SIZE * TILE_SCALE - TILE_SCALE, ANCHOR_TOP_LEFT);
				break;
			}
		}
	}
}

void map_draw_front(t_game* game) {
	int x, y, n;

	for (y = 0; y < game->map->size.y; y++)
	{
		for (x = 0; x < game->map->size.x; x++)
		{
			n = game->map->data[x][y];

			if (n == 12) {
				t_tile tile = set_tile(5, 7);
				blit_tile(game, tile, game->scene_offset.x + x * TILE_SIZE * TILE_SCALE, game->scene_offset.y + y * TILE_SIZE * TILE_SCALE - TILE_SCALE, ANCHOR_TOP_LEFT);
			}
		}
	}
}
