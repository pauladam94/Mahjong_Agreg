#ifndef GAME_H
#define GAME_H

#include "../utils/vec.h"
#include "event.h"
#include "player.h"
#include <pthread.h>

typedef struct Game {
    pthread_mutex_t events_mutex;
    vec(Event) events;
    u64 index_event;

    Player player;

} Game;

Game game_empty();

// This structure is thread safe

void game_free(Game *game);
#endif // GAME_H
