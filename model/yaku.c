#include "yaku.h"
#include "pattern.h"
#include "patterns.h"

int power(int b, int e) {
    if (e == 0)
        return 1;
    return b * power(b, e - 1);
}

int (*yakus_list[28])(const Pattern *pat) = {
    lipeikou,
    ryanpeikou,
    pinfu,
    shanshoku_doujun,
    ittsuu,
    tanyao,
    yakuhai,
    shousangen,
    daisangen,
    shousuushi,
    daisuushi,
    chanta,
    junchan,
    honroutou,
    chinroutou,
    tsuuiisou,
    kokuushi_musou,
    chiitoitsu,
    toitoi,
    sanankou,
    suuankou,
    sanshoku_doukou,
    sankatsu,
    suukantsu,
    honitsu,
    chinitsu,
    ryuuiisou,
    churen_poutou
};

char *yaku_name[28] = {
    "lipeikou",
    "ryanpeikou",
    "pinfu",
    "shanshoku_doujun",
    "ittsuu",
    "tanyao",
    "yakuhai",
    "shousangen",
    "daisangen",
    "shousuushi",
    "daisuushi",
    "chanta",
    "junchan",
    "honroutou",
    "chinroutou",
    "tsuuiisou",
    "kokuushi_musou",
    "chiitoitsu",
    "toitoi",
    "sanankou",
    "suuankou",
    "sanshoku_doukou",
    "sankatsu",
    "suukantsu",
    "honitsu",
    "chinitsu",
    "ryuuiisou",
    "churen_poutou"
};

// functions testing the yakus

// double suite pure
int lipeikou(const Pattern *pat) {
    if (pattern_is_open(pat) || ryanpeikou(pat))
        return 0;

    vec(vec(Tile *)) threes = pattern_without_pair(pat);
    vec(GroupType) types = pattern_get_group_type_without_pair(pat);

    for (u64 i = 0; i < 4; i++) {
        for (u64 j = i + 1; j < 4; j++) {
            if (
                (types[i] == SEQUENCE_CLOSE || types[j] == SEQUENCE_OPEN) &&
                (tile_equals(threes[i][0], threes[j][0]))
            ) {
                vec_free(threes);
                vec_free(types);
                return 1;
            }
        }
    }

    vec_free(threes);
    vec_free(types);
    return 0;
}

// deux doubles suites pures
int ryanpeikou(const Pattern *pat) {
    if (pattern_is_open(pat))
        return 0;

    int count = 0;
    vec(vec(Tile *)) threes = pattern_without_pair(pat);
    vec(GroupType) types = pattern_get_group_type_without_pair(pat);

    for (u64 i = 0; i < 4; i++) {
        for (u64 j = i + 1; j < 4; j++) {
            if (types[i] == SEQUENCE_CLOSE &&
                tile_equals(threes[i][0], threes[j][0]))
                count++;
        }
    }

    int bf = (int)(count == 2);
    vec_free(types);
    vec_free(threes);
    return 3 * bf;
}

// aucun fu
int pinfu(const Pattern *pat) {
    (void)pat;
    return 0;
}

// triple suite
int shanshoku_doujun(const Pattern *pat) {
    vec(vec(Tile *)) threes = pattern_without_pair(pat);
    vec(GroupType) types = pattern_get_group_type_without_pair(pat);

    for (u64 k = 0; k < 4; k++) {
        int v1 = tile_number(threes[k % 4][0]);
        int v2 = tile_number(threes[(k + 1) % 4][0]);
        int v3 = tile_number(threes[(k + 2) % 4][0]);
        if (
        (types[k % 4] == SEQUENCE_CLOSE || types[k % 4] == SEQUENCE_OPEN) &&
        (types[(k + 1) % 4] == SEQUENCE_CLOSE || types[(k + 1) % 4] == SEQUENCE_OPEN) &&
        (types[(k + 2) % 4] == SEQUENCE_CLOSE || types[(k + 2) % 4] == SEQUENCE_OPEN) &&
        !tile_same_family(threes[k % 4][0], threes[(k + 1) % 4][0]) &&
        !tile_same_family(threes[k % 4][0], threes[(k + 2) % 4][0]) &&
        !tile_same_family(threes[(k + 1) % 4][0],threes[(k + 2) % 4][0]) &&
        v1 == v2 && v2 == v3
        ) {
            int open = (int)pattern_is_open(pat);
            vec_free(types);
            vec_free(threes);
            return 2 - open;
        }
    }

    vec_free(types);
    vec_free(threes);
    return 0;
}

// grande suite pure
int ittsuu(const Pattern *pat) {
    vec(vec(Tile *)) threes = pattern_without_pair(pat);
    vec(GroupType) types = pattern_get_group_type_without_pair(pat);

    for (u64 k = 0; k < 4; k++) {
        int v1 = tile_number(threes[k % 4][0]);
        int v2 = tile_number(threes[(k + 1) % 4][0]);
        int v3 = tile_number(threes[(k + 2) % 4][0]);
        if (
        (types[k % 4] == SEQUENCE_OPEN || types[k % 4] == SEQUENCE_CLOSE) &&
        (types[(k + 1) % 4] == SEQUENCE_OPEN || types[(k + 1) % 4] == SEQUENCE_CLOSE) &&
        (types[(k + 2) % 4] == SEQUENCE_OPEN || types[(k + 2) % 4] == SEQUENCE_CLOSE) &&
        tile_same_family(threes[k % 4][0], threes[(k + 1) % 4][0]) &&
        tile_same_family(threes[k % 4][0], threes[(k + 2) % 4][0]) &&
        v1 % 3 == 1 && v2 % 3 == 1 && v3 % 3 == 1 && v1 * v2 * v3 == 28) {
            int open = (int)pattern_is_open(pat);
            vec_free(types);
            vec_free(threes);
            return 2 - open;
        }
    }

    vec_free(types);
    vec_free(threes);
    return 0;
}

// tout ordinaire
int tanyao(const Pattern *pat) {
    vec(vec(Tile *)) groups = pattern_get_group(pat);

    for (u64 i = 0; i < vec_len(groups); i++) {
        for (u64 j = 0; j < vec_len(groups[i]); j++) {
            if (tile_is_terminal(groups[i][j]) || tile_is_honor(groups[i][j])) {
                return 0;
            }
        }
    }

    return 1;
}

// brelan de valeur
int yakuhai(const Pattern *pat) {
    (void)pat;
    return 0;
}

// trois petits dragons
int shousangen(const Pattern *pat) {
    vec(vec(Tile *)) groups = pattern_get_group(pat);
    vec(GroupType) types = pattern_get_group_type(pat);

    int count_three = 0;
    int count_pair = 0;
    for (u64 i = 0; i < vec_len(groups); i++) {
        if (tile_is_dragon(groups[i][0])) {
            if (types[i] == PAIR_CLOSE) {
                count_pair++;
            } else {
                count_three++;
            }
        }
    }

    int bf = (int)(count_three == 2 && count_pair == 1);
    return 2 * bf;
}

// trois grands dragons
int daisangen(const Pattern *pat) {
    vec(vec(Tile *)) threes = pattern_without_pair(pat);

    int count = 0;
    for (u64 i = 0; i < 4; i++) {
        if (tile_is_dragon(threes[i][0]))
            count++;
    }

    int bf = (int)(count == 3);
    vec_free(threes);
    return 13 * bf;
}

// quatre petits vents
int shousuushi(const Pattern *pat) {
    vec(vec(Tile *)) groups = pattern_get_group(pat);
    vec(GroupType) types = pattern_get_group_type(pat);

    int count_three = 0;
    int count_pair = 0;
    for (u64 i = 0; i < vec_len(groups); i++) {
        if (tile_is_wind(groups[i][0])) {
            if (types[i] == PAIR_CLOSE) {
                count_pair++;
            } else {
                count_three++;
            }
        }
    }

    int bf = (int)(count_three == 3 && count_pair == 1);;
    return 13 * bf;
}

// quatre grands vents
int daisuushi(const Pattern *pat) {
    vec(vec(Tile *)) threes = pattern_without_pair(pat);

    int count = 0;
    for (u64 i = 0; i < 4; i++) {
        if (tile_is_wind(threes[i][0]))
            count++;
    }

    int bf = (int)(count == 4);
    vec_free(threes);
    return 13 * bf;
}

// terminale et honneurs de partout
int chanta(const Pattern *pat) {
    vec(vec(Tile *)) groups = pattern_get_group(pat);

    for (u64 i = 0; i < vec_len(groups); i++) {
        if (!tile_is_terminal(groups[i][0]) &&
            !tile_is_terminal(groups[i][vec_len(groups[i]) - 1]) &&
            !tile_is_honor(groups[i][0]))
            return 0;
    }

    int open = (int)pattern_is_open(pat);
    return 2 - open;
}

// terminale partout
int junchan(const Pattern *pat) {
    vec(vec(Tile *)) groups = pattern_get_group(pat);

    for (u64 i = 0; i < vec_len(groups); i++) {
        if (!tile_is_terminal(groups[i][0]) &&
            !tile_is_terminal(groups[i][vec_len(groups[i]) - 1])) {
            return 0;
        }
    }

    int open = (int)pattern_is_open(pat);
    return 3 - open;
}

// tout terminale et honneur
int honroutou(const Pattern *pat) {
    vec(vec(Tile *)) groups = pattern_get_group(pat);

    for (u64 i = 0; i < vec_len(groups); i++) {
        for (u64 j = 0; j < vec_len(groups[i]); j++) {
            if (!tile_is_terminal(groups[i][j]) && !tile_is_honor(groups[i][j])) {
                return 0;
            }
        }
    }

    return 2;
}

// tout terminale
int chinroutou(const Pattern *pat) {
    vec(vec(Tile *)) groups = pattern_get_group(pat);

    for (u64 i = 0; i < vec_len(groups); i++) {
        for (u64 j = 0; j < vec_len(groups[i]); j++) {
            if (!tile_is_terminal(groups[i][j])) {
                return 0;
            }
        }
    }

    return 13;
}

// tout honneur
int tsuuiisou(const Pattern *pat) {
    vec(vec(Tile *)) groups = pattern_get_group(pat);

    for (u64 i = 0; i < vec_len(groups); i++) {
        for (u64 j = 0; j < vec_len(groups[i]); j++) {
            if (!tile_is_honor(groups[i][j])) {
                return 0;
            }
        }
    }

    return 13;
}

// 13 orphelins
int kokuushi_musou(const Pattern *pat) {
    (void) pat;
    return 0;
}

// 7 paires
int chiitoitsu(const Pattern *pat) {
    vec(vec(Tile *)) groups = pattern_get_group(pat);
    vec(GroupType) types = pattern_get_group_type(pat);

    for (u64 i = 0; i < vec_len(types); i++) {
        switch(types[i]) {
            case PAIR_CLOSE:
                break;
            default:
                return 0;
        }
    }

    for (u64 i = 0; i < vec_len(groups); i++) {
        for (u64 j = i + 1; j < vec_len(groups); j++) {
            if (tile_equals(groups[i][0], groups[j][0])) {
                return 0;
            }
        }
    }
    return 2;
}

// tout brelan
int toitoi(const Pattern *pat) {
    vec(GroupType) types = pattern_get_group_type(pat);

    for (u64 i = 0; i < vec_len(types); i++) {
        switch (types[i]) {
        case SEQUENCE_CLOSE:
        case SEQUENCE_OPEN:
            return 0;
        default:
            break;
        }
    }
    return 2;
}

// trois brelans cachés
int sanankou(const Pattern *pat) {
    vec(GroupType) types = pattern_get_group_type(pat);

    int count = 0;
    for (u64 i = 0; i < vec_len(types); i++) {
        switch (types[i]) {
        case THREE_CLOSE:
        case FOUR_CLOSE:
            count++;
            break;
        default:
            break;
        }
    }

    int bf = (int)(count == 3);
    return 2 * bf;
}

// quatre brelans cachés
int suuankou(const Pattern *pat) {
    vec(GroupType) types = pattern_get_group_type(pat);

    int count = 0;
    for (u64 i = 0; i < vec_len(types); i++) {
        switch (types[i]) {
        case THREE_CLOSE:
        case FOUR_CLOSE:
            count++;
            break;
        default:
            break;
        }
    }
    int bf = (int)(count == 4);
    return 13 * bf;
}

// triple brelan
int sanshoku_doukou(const Pattern *pat) {
    vec(vec(Tile *)) threes = pattern_without_pair(pat);
    vec(GroupType) types = pattern_get_group_type_without_pair(pat);

    for (u64 k = 0; k < 4; k++) {
        int v1 = tile_number(threes[k % 4][0]);
        int v2 = tile_number(threes[(k + 1) % 4][0]);
        int v3 = tile_number(threes[(k + 2) % 4][0]);
        if (
        (types[k % 4] == THREE_CLOSE || types[k % 4] == THREE_OPEN || types[k % 4] == FOUR_CLOSE || types[k % 4] == FOUR_OPEN) &&
        (types[(k + 1) % 4] == THREE_CLOSE || types[(k + 1) % 4] == THREE_OPEN || types[(k + 1) % 4] == FOUR_CLOSE || types[(k + 1) % 4] == FOUR_OPEN) &&
        (types[(k + 2) % 4] == THREE_CLOSE || types[(k + 2) % 4] == THREE_OPEN || types[(k + 2) % 4] == FOUR_CLOSE || types[(k + 2) % 4] == FOUR_OPEN) &&
        !tile_same_family(threes[k % 4][0], threes[(k + 1) % 4][0]) &&
        !tile_same_family(threes[k % 4][0], threes[(k + 2) % 4][0]) &&
        !tile_same_family(threes[(k + 1) % 4][0],threes[(k + 2) % 4][0]) &&
        v1 == v2 && v2 == v3) {
            int open = (int)pattern_is_open(pat);
            vec_free(types);
            vec_free(threes);
            return 2 - open;
        }
    }
    vec_free(types);
    vec_free(threes);
    return 0;
}

// trois carrés
int sankatsu(const Pattern *pat) {
    vec(GroupType) types = pattern_get_group_type(pat);

    int count = 0;
    for (u64 i = 0; i < vec_len(types); i++) {
        switch (types[i]) {
        case FOUR_OPEN:
        case FOUR_CLOSE:
            count++;
            break;
        default:
            break;
        }
    }

    int bf = (int)(count == 3);
    return 2 * bf;
}

// quatre carrés
int suukantsu(const Pattern *pat) {
    vec(GroupType) types = pattern_get_group_type(pat);

    int count = 0;
    for (u64 i = 0; i < vec_len(types); i++) {
        switch (types[i]) {
        case FOUR_OPEN:
        case FOUR_CLOSE:
            count++;
            break;
        default:
            break;
        }
    }

    int bf = (int)(count == 4);
    return 13 * bf;
}

// semi-pure
int honitsu(const Pattern *pat) {
    if (chinitsu(pat))
        return 0;

    vec(vec(Tile *)) groups = pattern_get_group(pat);

    Tile *ref = NULL;
    for (u64 i = 0; i < vec_len(groups); i++) {
        for (u64 j = 0; j < vec_len(groups[i]); j++) {
            if (!tile_is_honor(groups[i][j])) {
                if (ref == NULL) {
                    ref = groups[i][j];
                } else if (!tile_same_family(ref, groups[i][j])) {
                    return 0;
                }
            }
        }
    }

    int open = (int)pattern_is_open(pat);
    return 3 - open;
}

// main pure
int chinitsu(const Pattern *pat) {
    vec(vec(Tile *)) groups = pattern_get_group(pat);

    if (tile_is_honor(groups[0][0])) {
        return 0;
    }

    Tile *ref = groups[0][0];
    for (u64 i = 0; i < vec_len(groups); i++) {
        for (u64 j = 0; j < vec_len(groups[i]); j++) {
            if (tile_is_honor(groups[i][j])) {
                return 0;
            }
            if (!tile_same_family(ref, groups[i][j])) {
                return 0;
            }
        }
    }

    int open = (int)pattern_is_open(pat);
    return 6 - open;
}

bool green_hand(Tile *t) {
    switch (tile_number(t)) {
    case 2:
    case 3:
    case 4:
    case 6:
    case 8:
        return true;
    default:
        return false;
    }
}

// main verte
int ryuuiisou(const Pattern *pat) {
    vec(vec(Tile *)) groups = pattern_get_group(pat);

    for (u64 i = 0; i < vec_len(groups); i++) {
        for (u64 j = 0; j < vec_len(groups[i]); j++) {
            if (!((u64)(groups[i][j]) == 33) &&
                !(tile_is_su(groups[i][j]) && green_hand(groups[i][j]))) {
                return 0;
            }
        }
    }

    return 13;
}

// neuf portes
int churen_poutou(const Pattern *pat) {
    vec(vec(Tile *)) groups = pattern_get_group(pat);

    if (!chinitsu(pat)) {
        return 0;
    }
    
    int count[10] = {0};
    for (u64 i = 0; i < vec_len(groups); i++) {
        for (u64 j = 0; j < vec_len(groups[i]); j++) {
            if (!tile_is_family(groups[i][j])) {
                return 0;
            }
            count[tile_number(groups[i][j])]++;
        }
    }
    
    if ((count[1] == 4 && count[9] == 3) || (count[1] == 3 && count[9] == 4)) {
        for (u64 i = 2; i < 9; i++) {
            if (count[i] != 1) {
                return 0;
            }
        }
        return 13;
    }
    if (count[1] != 3 || count[9] != 3) {
        return 0;
    }
    bool pair = 0;
    for (u64 i = 2; i < 9; i++) {
        if (count[i] == 2) {
            if (pair) {
                return 0;
            }
            pair = true;
        }
    }

    return 13;
}


// yakus detection

/**
 * @brief For a given pattern, find all the yakus that can be applied
 * @param pat the pattern to analyze
 * @return a vector of yakus that can be applied
 */
vec(Yaku) find_yaku(const Pattern *pat) { 
    vec(Yaku) res = NULL;

    for (u64 i = 0; i < 28; i++) {
        int han = yakus_list[i](pat);
        if (han > 0) {
            Yaku y = {
                (Yaku_id)i,
                han
            };
            vec_push(res, y);
        }
    }

    return res;
}

/**
 * @brief For a given hand, find the pattern that optimize the final score
 * @param hand the hand to analyze
 * @return a vector of yakus that can be applied to the best pattern
 */
vec(Yaku) find_max_yaku(const Hand *hand) {
    vec(vec(Yaku)) all_yakus = NULL;

    vec(Pattern *) patterns = hand_patterns(hand);
    for (u64 i = 0; i < vec_len(patterns); i++) {
        vec(Yaku) yakus = find_yaku(patterns[i]);
        vec_push(all_yakus, yakus);
    }

    int score = 0;
    vec(Yaku) res = all_yakus[0];
    for (u64 i = 0; i < vec_len(all_yakus); i++) {
        int h = 0;
        int fu = 1;
        for (u64 j = 0; j < vec_len(all_yakus[i]); j++) {
            h += all_yakus[i][j].han;
        }
        if (fu * power(2, h) > score) {
            score = fu * power(2, h);
            res = all_yakus[i];
        }
    }

    patterns_free(&patterns);
    vec_free(all_yakus);
    return res;
}