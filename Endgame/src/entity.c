// entity.c

#include "entity.h"

t_entity *entity_add(t_game *game, t_entity_type type, int x, int y, t_tile tile, t_facing facing) {
    t_entity *current = game->entities;
    t_entity *entity = (t_entity *) malloc(sizeof(t_entity));
    if (entity == NULL) exit(-1);

    memset(entity, 0, sizeof(t_entity));

    entity->type = type;
	entity->x = x;
	entity->y = y;
    entity->tile = tile;
    entity->facing = facing;
    entity->next = NULL;
    entity->animations = NULL;
    entity->usable = NULL;
    entity->slag = NULL;

    if (current != NULL) {
        while (current->next != NULL) {
            current = current->next;
        }

        current->next = entity;
    }
    else {
        game->entities = entity;
    }

    return entity;
}

void entity_logic(t_game *game) {
    t_entity *current = game->entities;
    

    while (current != NULL) {
        switch (current->type) {
        case ENTYPE_PLAYER:
            player_logic(game);
            break;

        case ENTYPE_NPC:
            npc_logic(game, current);
            break;

        case ENTYPE_ITEM:
            //item_logic(game, current);
            break;

        case ENTYPE_DOOR:
            door_logic(game, current);
            break;
        
        case ENTYPE_OBJECT:
            object_logic(game, current);
            break;
        
        default:
            break;
        }

        current = current->next;
    }
}

void entity_draw(t_game *game) {
    t_entity *current = game->entities;

    while (current != NULL) {
        switch (current->type) {
        case ENTYPE_PLAYER:
            
            break;

        case ENTYPE_NPC:
            npc_draw(game, current);
            break;

        case ENTYPE_ITEM:
            item_draw(game, current);
            break;

        case ENTYPE_DOOR:
            door_draw(game, current);
            break;

        case ENTYPE_OBJECT:
            object_draw(game, current);
            break;
        
        default:
            break;
        }

        current = current->next;
    }

    player_draw(game);
}

void entity_free(t_game *game) {
    t_entity *current = game->entities;

    while (current != NULL) {
        switch (current->type) {
        case ENTYPE_PLAYER:

            break;

        case ENTYPE_NPC:
            npc_free(current);
            break;

        case ENTYPE_ITEM:
            item_free(current);
            break;

        case ENTYPE_DOOR:
            door_free(current);
            break;

        case ENTYPE_OBJECT:
            object_free(current);
            break;
        
        default:
            break;
        }

        animations_free(current);

        current = current->next;
    }


    while (game->entities != NULL) {
        t_entity *next = NULL;
        next = game->entities->next;

        free(game->entities);
        game->entities = next;
    }

	game->entities = NULL;
}

t_entity *entity_by_slag(t_game *game, const char *slag) {
    t_entity *current = game->entities;
    while (current != NULL) {
        if (current->slag == NULL) {
            current = current->next;
            continue;
        }
        if (!strcmp(current->slag, slag)) break;
        if (current->next == NULL) {
            return NULL;
        } 
        current = current->next;
    }

    return current;
}
