#ifndef GAME_H
#define GAME_H

#include "../utils/vec.h"
#include "event.h"
#include "player.h"
#include <pthread.h>

// 3 Thread have access to this struct
// # Client Receive Thread
// - Receive events from other players and add them
//
// # Client Send Thread
// - Receive events from the application of the current player and send them to
// other players
//
// # GUI Application Thread
// - Send to client the information that a event has to be send
typedef struct Game {
    // Thoses Events are either
    // - received from other players
    // - created by the current player (and send by the client)
    pthread_mutex_t events_mutex;
    vec(Event) events;
    u64 index_event;

    pthread_mutex_t events_to_send_mutex;
    // Indicates to client that something has to be send
    pthread_cond_t events_to_send_cond;
    vec(Event) events_to_send;

    Player player;
} Game;

Game game_empty();

// This structure is thread safe
void game_free(Game *game);
void game_push_event(Game *game, Event event);
Event game_process_event(Game *game);

void game_push_event_to_send(Game *game, Event event);
void game_send_one_event(Game *game);

#endif // GAME_H
