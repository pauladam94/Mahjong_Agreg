#include "../model/align.h"
#include "../view/context.h"
#include "../view/draw.h"
#include "pattern.h"
#include "patterns.h"
#include "player.h"
#include "pos.h"
#include "raylib.h"
#include "tiles.h"
#include <stdlib.h>

typedef struct Hand {
    Tiles *hand;
    Pos **hand_pos;
    int hand_pos_len;
    int hand_pos_cap;
    int hand_hover;
    int hand_pressed;

    Tiles *discard;
    Pos **discard_pos;
    int discard_pos_len;
    int discard_pos_cap;
    int discard_hover;

    Tiles **chi;
    int chi_len;
    int chi_cap;

    Tiles **pon;
    int pon_len;
    int pon_cap;

    Tiles **kan;
    int kan_len;
    int kan_cap;

    bool opened;
    Align align;
    Vector2 pos;
    Player player;
} Hand;

int hand_get_hand_hover(Hand *hand) { return hand->hand_hover; }
int hand_get_discard_hover(Hand *hand) { return hand->discard_hover; }

void hand_update_pos(Hand *hand) {
    hand->hand_pos_len = tiles_size(hand->hand);
    hand->discard_pos_len = tiles_size(hand->discard);
    hand->hand_pos =
        realloc(hand->hand_pos, sizeof(*hand->hand_pos) * hand->hand_pos_len);
    hand->discard_pos = realloc(hand->discard_pos, sizeof(*hand->discard_pos) *
                                                       hand->discard_pos_len);
    for (int i = 0; i < hand->hand_pos_len; i++) {
        hand->hand_pos[i] = pos_from_vec(
            align_pos_hand(hand->align, hand->pos.x, hand->pos.y, i));
    }
    for (int i = 0; i < hand->discard_pos_len; i++) {
        hand->discard_pos[i] = pos_from_vec(
            align_pos_discard(hand->align, hand->pos.x, hand->pos.y, i));
    }
}

void hand_draw(Hand *hand) {
    // hand_update_pos(hand);
    for (int i = 0; i < tiles_size(hand->hand); i++) {
        tile_draw(tiles_get(hand->hand, i), pos_get(hand->hand_pos[i]),
                  hand->align);
    }
    for (int i = 0; i < tiles_size(hand->discard); i++) {
        tile_draw(tiles_get(hand->discard, i), pos_get(hand->discard_pos[i]),
                  hand->align);
    }
    if (hand->hand_hover != -1) {
        highlight_tile_draw(pos_get(hand->hand_pos[hand->hand_hover]), ORANGE,
                            hand->align);
    }
    if (hand->discard_hover != -1) {
        highlight_tile_draw(pos_get(hand->discard_pos[hand->discard_hover]),
                            ORANGE, hand->align);
    }
}

Hand *hand_empty(Player player) {
    Hand *hand = calloc(sizeof(*hand), 1);
    hand->hand = tiles_empty();
    hand->discard = tiles_empty();
    hand->align = player_align(player);
    hand->pos = player_pos(player);
    hand->hand_pressed = -1;
    hand->hand_hover = -1;
    hand->discard_hover = -1;
    return hand;
}
void hand_remove_tile(Hand *hand, int pos) { tiles_remove(hand->hand, pos); }

void hand_add_discard(Hand *hand, Tile *tile) {
    tiles_add(hand->discard, tile);
}

Tiles *hand_discard(Hand *hand) { return hand->discard; }

void hand_discard_tile(Hand *hand, Tile *tile) {
    int pos = tiles_remove_equals(hand->hand, tile);
    Vector2 prev = pos_get(hand->hand_pos[pos]);
    hand_add_discard(hand, tile);
    hand_update_pos(hand);
    Vector2 next = pos_get(hand->discard_pos[hand->discard_pos_len - 1]);
    hand->discard_pos[hand->discard_pos_len - 1] = pos_transi(prev, next);
}

Tiles *hand_closed_tiles(const Hand *hand) { return hand->hand; }
Tiles *hand_discarded_tiles(const Hand *hand) { return hand->discard; }

void hand_add_tile(Hand *hand, Tile *tile) {
    tiles_add(hand->hand, tile);
    hand_update_pos(hand);
}

bool is_opened(const Hand *hand) { return hand->opened; }
bool is_closed(const Hand *hand) { return !hand->opened; }

void hand_pick_from(Hand *hand, Tiles *from) {
    Tile *t = tiles_pick_from(from);
    hand_add_tile(hand, t);
}

void hand_pp(FILE *file, const Hand *hand) { tiles_pp(file, hand->hand); }

Patterns *hand_patterns(const Hand *hand) {
    tiles_sort(hand->hand);
    Patterns *res = patterns_empty();
    Patterns *todo = patterns_empty();
    Tiles *tiles = tiles_copy(hand->hand);

    // TODO: Add in the first pattern the different chi and su
    Pattern *pat = pattern_from_tiles(tiles);
    patterns_add_pattern(todo, pat);

    while (patterns_size(todo) != 0) {
        Pattern *pattern = patterns_pop(todo);

        if (pattern_is_complete(pattern)) {
            patterns_add_pattern(res, pattern);
            continue;
        }
        patterns_add_first_group_pattern(todo, pattern);

        // printf("\nRes:\n");
        // patterns_pp(stdout, res);
        // printf("\n");
        // printf("Todo:\n");
        // patterns_pp(stdout, todo);
        // printf("\n");
    }
    patterns_free(todo);
    return res;
}

bool hand_is_complete(const Hand *hand) {
    Patterns *patterns = hand_patterns(hand);

    // printf("Patterns :\n");
    // patterns_pp(stdout, patterns);
    // printf("\n");

    int n_patterns = patterns_size(patterns);
    patterns_free(patterns);
    return n_patterns >= 1;
}

void hand_sort(Hand *hand) { tiles_sort(hand->hand); }

bool hand_is_valid(const Hand *hand) {
    printf("TODO: hand_is_valid\nhand:");
    hand_pp(stdout, hand);
    return true;
}

Hand *hand_from_string(const char *s) {
    Hand *hand = hand_empty(Player0);
    tiles_free(hand->hand);
    hand->hand = tiles_from_string(s);
    return hand;
}

void hand_free(Hand *hand) {
    tiles_free(hand->hand);
    tiles_free(hand->discard);
    for (int i = 0; i < hand->chi_len; i++)
        tiles_free(hand->chi[i]);
    for (int i = 0; i < hand->kan_len; i++)
        tiles_free(hand->kan[i]);
    for (int i = 0; i < hand->pon_len; i++)
        tiles_free(hand->pon[i]);
    free(hand->pon);
    free(hand->chi);
    free(hand->kan);
    free(hand);
}

bool hand_update(Hand *hand, Tiles *tiles, Context ctx) {
    bool next_turn = false;
    // Hand
    hand->hand_pressed = -1;
    hand->hand_hover = -1;
    hand->discard_hover = -1;

    for (int i = 0; i < tiles_size(hand->hand); i++) {
        Rectangle rec = align_rect(hand->align, pos_get(hand->hand_pos[i]));
        if (CheckCollisionPointRec(ctx.mouse, rec)) {
            if (IsMouseButtonDown(0)) {
                hand->hand_pressed = i;
                next_turn = true;
                break;
            } else {
                hand->hand_hover = i;
            }
        }
    }
    // Discard
    for (int i = 0; i < tiles_size(hand->discard); i++) {
        Rectangle rec = align_rect(hand->align, pos_get(hand->discard_pos[i]));
        if (CheckCollisionPointRec(ctx.mouse, rec)) {
            hand->discard_hover = i;
            break;
        }
    }

    if (hand->hand_pressed != -1) {
        Tile *tile_pressed = tiles_get(hand->hand, hand->hand_pressed);

        Tile *random_tile = tiles_random_from(tiles);
        hand_add_tile(hand, random_tile);
        tiles_remove_equals(tiles, random_tile);

        hand_discard_tile(hand, tile_pressed);

        hand_sort(hand);
        hand->hand_pressed = -1; // Back to -1
        hand->hand_hover = -1;   // Back to -1
    }

    return next_turn;
}

void hand_update_pos_transi(Hand *hand) {
    for (int i = 0; i < hand->hand_pos_len; i++) {
        pos_update(hand->hand_pos[i]);
    }
    for (int i = 0; i < hand->discard_pos_len; i++) {
        pos_update(hand->discard_pos[i]);
    }
}
