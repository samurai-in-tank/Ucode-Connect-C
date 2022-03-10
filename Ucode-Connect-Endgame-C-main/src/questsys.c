// questsys.c

#include "questsys.h"

void questsys_level00(t_game *game);
void questsys_level01(t_game *game);
void questsys_level02(t_game *game);

void questsys_init(t_game *game) {
    game->questsys.level = 0;
    game->questsys.stage = 0;
    game->is_last_stage = false;
}

void questsys_logic(t_game *game) {
    switch (game->questsys.level) {
        case 0:
            questsys_level00(game);
            break;

        case 1:
            questsys_level01(game);
            break;

        case 2:
            questsys_level02(game);
            break;
    }
}

void questsys_level00(t_game *game) {
    t_entity *general = entity_by_slag(game, "real_general");
    t_entdata_npc *general_data = general->data;
    t_entity *scientist = entity_by_slag(game, "real_scientist");
    t_entdata_npc *scientist_data = scientist->data;
    t_entity *main_chair = entity_by_slag(game, "chair_of_vr_main");
    t_entdata_object *main_chair_data = main_chair->data;

    switch (game->questsys.stage) {
        case 0:
            if (!game->is_last_stage) {
                game->is_last_stage = true;

                general_data->is_active = true;
                general_data->current_branch = 0;
            }

            if (!general_data->is_active) {
                game->questsys.stage = 1;
                game->is_last_stage = false;
            }
            break;

        case 1:
            if (!game->is_last_stage) {
                game->is_last_stage = true;

                scientist_data->is_active = true;
                scientist_data->current_branch = 0;
            }

            if (!scientist_data->is_active) {
                game->questsys.stage = 2;
                game->is_last_stage = false;
            }
            break;
        
        case 2:
            if (!game->is_last_stage) {
                game->is_last_stage = true;

                main_chair_data->is_active = true;
            }

            if (main_chair_data->is_used) {
                game->questsys.stage = 3;
                game->is_last_stage = false;
            }
            break;

        case 3:
            if (!game->is_last_stage) {
                game->is_last_stage = true;

                game->player->x = 18 * (TILE_SCALE * TILE_SIZE);
                game->player->y = 2 * (TILE_SCALE * TILE_SIZE);
                game->questsys.level = 1;
                game->questsys.stage = 0;
                player_set_spawnpoint(game, 18, 2);
            }

            break;
    }
}

void questsys_level01(t_game *game) {
    t_entity *virtual_general = entity_by_slag(game, "virtual_general");
    t_entdata_npc *virtual_general_data = virtual_general->data;
    t_entity *virtual_guard = entity_by_slag(game, "virtual_guard");
    t_entdata_npc *virtual_guard_data = virtual_guard->data;
    t_entity *virtual_sarge = entity_by_slag(game, "virtual_sarge");
    t_entdata_npc *virtual_sarge_data = virtual_sarge->data;

    t_entity *virtual_grass00 = entity_by_slag(game, "virtual_grass00");
    t_entdata_object *virtual_grass00_data = virtual_grass00->data;
    t_entity *virtual_grass01 = entity_by_slag(game, "virtual_grass01");
    t_entdata_object *virtual_grass01_data = virtual_grass01->data;
    t_entity *virtual_grass02 = entity_by_slag(game, "virtual_grass02");
    t_entdata_object *virtual_grass02_data = virtual_grass02->data;
    t_entity *virtual_grass03 = entity_by_slag(game, "virtual_grass03");
    t_entdata_object *virtual_grass03_data = virtual_grass03->data;
    t_entity *virtual_grass04 = entity_by_slag(game, "virtual_grass04");
    t_entdata_object *virtual_grass04_data = virtual_grass04->data;

    t_entity *virtual_potato00 = entity_by_slag(game, "virtual_potato00");
    t_entdata_object *virtual_potato00_data = virtual_potato00->data;
    t_entity *virtual_potato01 = entity_by_slag(game, "virtual_potato01");
    t_entdata_object *virtual_potato01_data = virtual_potato01->data;
    t_entity *virtual_potato02 = entity_by_slag(game, "virtual_potato02");
    t_entdata_object *virtual_potato02_data = virtual_potato02->data;

    t_entity *locked_door = entity_by_slag(game, "mil_locked_door");
    t_entdata_door *locked_door_data = locked_door->data;

    t_entity *portal0 = entity_by_slag(game, "portal0");
    t_entdata_object *portal0_data = portal0->data;
    t_entity *portal1 = entity_by_slag(game, "portal1");
    t_entdata_object *portal1_data = portal1->data;

    switch (game->questsys.stage) {
        case 0:
            if (!game->is_last_stage) {
                game->is_last_stage = true;
                music_play(game, SND_LEVEL2_MUSIC);

                virtual_guard_data->is_active = true;
                virtual_guard_data->current_branch = 0;
                
            }

            if (!virtual_guard_data->is_active) {
                game->questsys.stage = 1;
                game->is_last_stage = false;
            }
            break;

        case 1:
            if (!game->is_last_stage) {
                game->is_last_stage = true;

                virtual_sarge_data->is_active = true;
                virtual_sarge_data->current_branch = 0;
            }

            if (!virtual_sarge_data->is_active) {
                game->questsys.stage = 2;
                game->is_last_stage = false;
            }
            break;

        case 2:
            if (!game->is_last_stage) {
                game->is_last_stage = true;

                virtual_grass00_data->is_active = true;
                virtual_grass01_data->is_active = true;
                virtual_grass02_data->is_active = true;
                virtual_grass03_data->is_active = true;
                virtual_grass04_data->is_active = true;
            }

            if (virtual_grass00_data->is_used && virtual_grass01_data->is_used && virtual_grass02_data->is_used && virtual_grass03_data->is_used && virtual_grass04_data->is_used) {
                game->questsys.stage = 3;
                game->is_last_stage = false;
            }
            break;

        case 3:
            if (!game->is_last_stage) {
                game->is_last_stage = true;

                virtual_sarge_data->is_active = true;
                virtual_sarge_data->current_branch = 1;
            }

            if (!virtual_sarge_data->is_active) {
                game->questsys.stage = 4;
                game->is_last_stage = false;
            }
            break;

        case 4:
            if (!game->is_last_stage) {
                game->is_last_stage = true;

                virtual_guard_data->is_active = true;
                virtual_guard_data->current_branch = 1;
            }

            if (!virtual_guard_data->is_active) {
                game->questsys.stage = 5;
                game->is_last_stage = false;
            }
            break;

        case 5:
            if (!game->is_last_stage) {
                game->is_last_stage = true;

                virtual_potato00_data->is_active = true;
                virtual_potato01_data->is_active = true;
                virtual_potato02_data->is_active = true;
            }

            if (virtual_potato00_data->is_used && virtual_potato01_data->is_used && virtual_potato02_data->is_used) {
                game->questsys.stage = 6;
                game->is_last_stage = false;
            }
            break;

        case 6:
            if (!game->is_last_stage) {
                game->is_last_stage = true;

                virtual_guard_data->is_active = true;
                virtual_guard_data->current_branch = 2;
            }

            if (!virtual_guard_data->is_active) {
                game->questsys.stage = 7;
                game->is_last_stage = false;
            }
            break;

        case 7:
            if (!game->is_last_stage) {
                game->is_last_stage = true;

                locked_door_data->is_locked = false;
                virtual_general_data->is_active = true;
                virtual_general_data->current_branch = 0;
            }

            if (!virtual_guard_data->is_active) {
                game->questsys.stage = 8;
                game->is_last_stage = false;
            }
            break;

        case 8:
            if (!game->is_last_stage) {
                game->is_last_stage = true;

                locked_door_data->is_locked = false;
                virtual_general_data->is_active = true;
                virtual_general_data->current_branch = 0;
            }

            if (!virtual_general_data->is_active) {
                game->questsys.stage = 9;
                game->is_last_stage = false;
            }
            break;

        case 9:
            if (!game->is_last_stage) {
                game->is_last_stage = true;

                portal0_data->is_obstacle = false;
                portal1_data->is_obstacle = false;
            }

            if (((game->player->x / (TILE_SCALE * TILE_SIZE) == portal0->x) && (game->player->y / (TILE_SCALE * TILE_SIZE) == portal0->y)) || ((game->player->x / (TILE_SCALE * TILE_SIZE) == portal1->x) && (game->player->y / (TILE_SCALE * TILE_SIZE) == portal1->y))) {
                game->questsys.level = 2;
                game->questsys.stage = 0;
                game->player->x = 11 * (TILE_SCALE * TILE_SIZE);
                game->player->y = 47 * (TILE_SCALE * TILE_SIZE);
                player_set_spawnpoint(game, 11, 47);
            }
            break;
    }
}

void questsys_level02(t_game *game) {
    t_entity *scientist = entity_by_slag(game, "virtual_scientist");
    t_entdata_npc *scientist_data = scientist->data;
    t_entity *portal0 = entity_by_slag(game, "final_portal0");
    t_entity *portal1 = entity_by_slag(game, "final_portal1");

    switch (game->questsys.stage) {
        case 0:
            if (!game->is_last_stage) {
                game->is_last_stage = true;


                scientist_data->is_active = true;
                scientist_data->current_branch = 0;
            }

            if (!scientist_data->is_active) {
                game->questsys.stage = 1;
                game->is_last_stage = false;
            }
            break;

        case 1:
            if (!game->is_last_stage) {
                game->is_last_stage = true;
                //scientist->x = -10000;
            }

            if (((game->player->x / (TILE_SCALE * TILE_SIZE) == portal0->x) && (game->player->y / (TILE_SCALE * TILE_SIZE) == portal0->y)) || ((game->player->x / (TILE_SCALE * TILE_SIZE) == portal1->x) && (game->player->y / (TILE_SCALE * TILE_SIZE) == portal1->y))) {
                game->control.is_locked = true;
                game->is_finish = true;
            }
            break;
    }
}
