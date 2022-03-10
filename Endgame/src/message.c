// message.c

#include "message.h"

t_message *message_add(t_entity *entity, char *header, char *text, int branch) {
    t_message *current = ((t_entdata_npc *) entity->data)->messages;
    t_message *mes = (t_message *) malloc(sizeof(t_message));
    if (mes == NULL) exit(-5);

    memset(mes, 0, sizeof(t_message));

    mes->header = header;
    mes->text = text;
    mes->branch = branch;
    mes->timer = 0;
    mes->delay = strlen(text) * CHARACTER_TIME;

    if (current != NULL) {
        while (current->next != NULL) {
            current = current->next;
        }

        current->next = mes;
    }
    else {
        ((t_entdata_npc *) entity->data)->messages = mes;
    }

    return mes;
}

void message_show(t_game *game, t_entity *entity) {
    if (((t_entdata_npc *)entity->data)->current_branch < 0) return;

    game->message_entity = entity;
    game->control.is_locked = true;
    ((t_entdata_npc *)entity->data)->is_active = false;
}

void message_draw(t_game *game) {
    t_entity *entity = game->message_entity;
    if (entity == NULL) return;

    t_message *current = ((t_entdata_npc *) entity->data)->messages;

    while (current != NULL) {
        if ((current->branch == ((t_entdata_npc *) entity->data)->current_branch) && !current->is_shown) break;
        if (current->next == NULL)  {
            ((t_entdata_npc *)game->message_entity->data)->is_talk = false;
            game->message_entity = NULL;
            game->control.is_locked = false;
            return;
        }
        current = current->next;
    }

    if (current->timer == 0) {
        current->timer = SDL_GetTicks();
        return;
    }

    SDL_Rect message_rect;
    message_rect.w = SCREEN_WIDTH;
    message_rect.h = 90;
    message_rect.x = 0;
    message_rect.y = SCREEN_HEIGHT - message_rect.h;

    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 0);
	SDL_RenderFillRect(game->renderer, &message_rect);

    text_draw(game, current->header, 20, SCREEN_HEIGHT - 50, 32, ANCHOR_BOTTOM_LEFT);
    text_draw(game, current->text, 20, SCREEN_HEIGHT - 20, 24, ANCHOR_BOTTOM_LEFT);
    if (game->sound.timer == 0) game->sound.timer = SDL_GetTicks();

    if (SDL_GetTicks() > game->sound.timer + 2000 || game->dev_mode.skip) {
        sound_play(game, SND_NPC_SPEECH, CH_OTHER);
        game->sound.timer = 0;
    }

    if (SDL_GetTicks() > current->timer + current->delay || game->dev_mode.skip) {
        current->is_shown = true;
        current->timer = SDL_GetTicks();
    }
}

void messages_free(t_entity *entity) {
    while (entity->animations != NULL) {
        t_message *next = NULL;
        next = ((t_entdata_npc *) entity->data)->messages->next;

        free(((t_entdata_npc *) entity->data)->messages);
        ((t_entdata_npc *) entity->data)->messages = next;
    }

	((t_entdata_npc *) entity->data)->messages = NULL;
}
