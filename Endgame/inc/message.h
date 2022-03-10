// message.h
#ifndef MESSAGE_H
#define MESSAGE_H

#include "common.h"
#include "entity.h"
#include "sound.h"

t_message *message_add(t_entity *entity, char *header, char *text, int branch);
void message_draw(t_game *game);
void message_show(t_game *game, t_entity *entity);
void messages_free(t_entity *entity);

#endif
