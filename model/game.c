#include "game.h"
#include "pthread.h"
#include <threads.h>

Game game_empty() {
    Game res;
    pthread_mutex_init(&res.events_mutex, NULL);
    res.events = NULL;
    res.index_event = 0;
    return res;
}

void game_free(Game *game) {
    vec_free(game->events);
    free(game->events);
}

void game_push_event(Game *game, Event event) {
    pthread_mutex_lock(&game->events_mutex);
    vec_push(game->events, event);
    pthread_mutex_unlock(&game->events_mutex);
}

Event game_process_event(Game *game) {
    pthread_mutex_lock(&game->events_mutex);
    Event event = game->events[game->index_event];
    game->index_event++;
    pthread_mutex_unlock(&game->events_mutex);
    return event;
}

// Play an entire game from the events only
void game_play(Game *game){};

Game game_initial() {
    Game game = game_empty();
    game.index_event = 0;
    game_push_event(&game, event_pick(tile_from_string("1m")));

    return game;
}
