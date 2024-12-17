#include "yaku.h"
#include "pattern.h"

typedef enum Yaku {
    LIPEIKOU,
    RYANPEIKOU,
    PINFU,
    SHANSHOKU_DOUJUN,
    ITTSUU,
    TANYAO,
    YAKUHAI,
    SHOUSANGEN,
    DAISANGEN,
    SHOUSUUSHI,
    DAISUUSHI,
    CHANTA,
    JUNCHAN,
    HONROUTOU,
    CHINROUTOU,
    TSUUIISOU,
    KOKUUSHI_MUSOU,
    CHIITOITSU,
    TOITOI,
    SANANKOU,
    SUUANKOU,
    SANSHOKU_DOUKOU,
    SANKATSU,
    SUUKANTSU,
    HONITSU,
    CHINITSU,
    RYUUIISOU,
    CHUREN_POUTOU,
} Yaku;

vec(yaku) max_yaku(const Hand *hand) {
    // no complete, no yaku
    if (!hand_is_complete(hand))
        return NULL;

    return NULL;
}

// return all the yaku for a given pattern
vec(yaku) find_yaku(const Pattern *pat) {
    vec(yaku) yakus = NULL;

    if (lipeikou(pat)) {
        yaku y = {"Lipeikou", 1};
        vec_push(yakus, y);
    }
    if (ryanpeikou(pat)) {
        yaku y = {"Ryanpeikou", 3};
        vec_push(yakus, y);
    }
    if (pinfu(pat)) {
        yaku y = {"Pinfu", 1};
        vec_push(yakus, y);
    }
    if (shanshoku_doujun(pat)) {
        yaku y = {"Shanshoku Doujun", 2 - pattern_is_open(pat)};
        vec_push(yakus, y);
    }
    if (ittsuu(pat)) {
        yaku y = {"Ittsuu", 2 - pattern_is_open(pat)};
        vec_push(yakus, y);
    }
    if (tanyao(pat)) {
        yaku y = {"Tanyao", 1};
        vec_push(yakus, y);
    }
    if (yakuhai(pat)) {
        yaku y = {"Yakuhai", 1};
        vec_push(yakus, y);
    }
    if (shousangen(pat)) {
        yaku y = {"Shousangen", 2};
        vec_push(yakus, y);
    }
    if (daisangen(pat)) {
        yaku y = {"Daisangen", 13};
        vec_push(yakus, y);
    }
    if (shousuushi(pat)) {
        yaku y = {"Shousuushi", 13};
        vec_push(yakus, y);
    }
    if (daisuushi(pat)) {
        yaku y = {"Daisuushi", 13};
        vec_push(yakus, y);
    }
    if (chanta(pat)) {
        yaku y = {"Chanta", 2 - pattern_is_open(pat)};
        vec_push(yakus, y);
    }
    if (junchan(pat)) {
        yaku y = {"Junchan", 3 - pattern_is_open(pat)};
        vec_push(yakus, y);
    }
    if (honroutou(pat)) {
        yaku y = {"Honroutou", 2};
        vec_push(yakus, y);
    }
    if (chinroutou(pat)) {
        yaku y = {"CHInroutou", 13};
        vec_push(yakus, y);
    }
    if (tsuuiisou(pat)) {
        yaku y = {"Tsuuiisou", 13};
        vec_push(yakus, y);
    }
    if (kokuushi_musou(pat)) {
        yaku y = {"Kokuushi Musou", 13};
        vec_push(yakus, y);
    }
    if (chiitoitsu(pat)) {
        yaku y = {"CHIitoitsu", 2};
        vec_push(yakus, y);
    }
    if (toitoi(pat)) {
        yaku y = {"Toitoi", 2};
        vec_push(yakus, y);
    }
    if (sanankou(pat)) {
        yaku y = {"Sanankou", 2};
        vec_push(yakus, y);
    }
    if (suuankou(pat)) {
        yaku y = {"Suuankou", 13};
        vec_push(yakus, y);
    }
    if (sanshoku_doukou(pat)) {
        yaku y = {"Sanshoku Doukou", 2};
        vec_push(yakus, y);
    }
    if (sankatsu(pat)) {
        yaku y = {"Sankatsu", 2};
        vec_push(yakus, y);
    }
    if (suukantsu(pat)) {
        yaku y = {"Suukantsu", 13};
        vec_push(yakus, y);
    }
    if (honitsu(pat)) {
        yaku y = {"Honitsu", 3 - pattern_is_open(pat)};
        vec_push(yakus, y);
    }
    if (chinitsu(pat)) {
        yaku y = {"CHInitsu", 6 - pattern_is_open(pat)};
        vec_push(yakus, y);
    }
    if (ryuuiisou(pat)) {
        yaku y = {"Ryuuiisou", 13};
        vec_push(yakus, y);
    }
    if (churen_poutou(pat)) {
        yaku y = {"Churen Poutou", 13};
        vec_push(yakus, y);
    }

    return yakus;
}

// function testing the yakus

// double suite pure
int lipeikou(const Pattern *pat) {
    if (pattern_is_open(pat))
        return 0;

    vec(vec(Tile *)) threes = pattern_without_pair(pat);
    vec(GroupType) types = pattern_get_group_type_without_pair(pat);

    for (u64 i = 0; i < 4; i++) {
        for (u64 j = i + 1; j < 4; j++) {
            if (types[i] == SEQUENCE && types[j] == SEQUENCE && tile_equals(threes[i][0], threes[j][0])) {
                vec_free(types);
                return 1;
            }
        }
    }

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
            if (types[i] == SEQUENCE && tile_equals(threes[i][0], threes[j][0]))
                count++;
        }
    }

    vec_free(types);
    return 3 * (int)(count == 2);
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
        (types[k % 4] == SEQUENCE || types[k % 4] == CHI) &&
        (types[(k + 1) % 4] == SEQUENCE || types[(k + 1) % 4] == CHI) &&
        (types[(k + 2) % 4] == SEQUENCE || types[(k + 2) % 4] == CHI) &&
        !tile_same_family(threes[k % 4][0], threes[(k + 1) % 4][0]) &&
        !tile_same_family(threes[k % 4][0], threes[(k + 2) % 4][0]) &&
        !tile_same_family(threes[(k + 1) % 4][0],threes[(k + 2) % 4][0]) &&
        v1 == v2 && v2 == v3
        ) {
            return 2 - (int)pattern_is_open(pat);
        }
    }

    vec_free(types);
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
        (types[k % 4] == SEQUENCE || types[k % 4] == CHI) &&
        (types[(k + 1) % 4] == SEQUENCE || types[(k + 1) % 4] == CHI) &&
        (types[(k + 2) % 4] == SEQUENCE || types[(k + 2) % 4] == CHI) &&
        tile_same_family(threes[k % 4][0], threes[(k + 1) % 4][0]) &&
        tile_same_family(threes[k % 4][0], threes[(k + 2) % 4][0]) &&
        v1 % 3 == 1 && v2 % 3 == 1 && v3 % 3 == 1 && v1 * v2 * v3 == 28) {
            vec_free(types);
            return 2 - (int)pattern_is_open(pat);
        }
    }

    vec_free(types);
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

    int count = 0;
    int count_pair = 0;
    for (u64 i = 0; i < vec_len(groups); i++) {
        if (tile_is_dragon(groups[i][0])) {
            count++;
            if (types[i] == PAIR) {
                count_pair++;
            }
        }
    }

    vec_free(types);
    return 2 * (int)(count == 3 && count_pair == 1);
}

// trois grands dragons
int daisangen(const Pattern *pat) {
    vec(vec(Tile *)) threes = pattern_without_pair(pat);

    int count = 0;
    for (u64 i = 0; i < 4; i++) {
        if (tile_is_dragon(threes[i][0]))
            count++;
    }

    return 13 * (int)(count == 3);
}

// quatre petits vents
int shousuushi(const Pattern *pat) {
    vec(vec(Tile *)) groups = pattern_get_group(pat);
    vec(GroupType) types = pattern_get_group_type(pat);

    int count = 0;
    int count_pair = 0;
    for (u64 i = 0; i < vec_len(groups); i++) {
        if (tile_is_wind(groups[i][0])) {
            count++;
            if (types[i] == PAIR) {
                count_pair++;
            }
        }
    }

    vec_free(types);
    return 13 * (int)(count == 3 && count_pair == 1);
}

// quatre grands vents
int daisuushi(const Pattern *pat) {
    vec(vec(Tile *)) threes = pattern_without_pair(pat);

    int count = 0;
    for (u64 i = 0; i < 4; i++) {
        if (tile_is_wind(threes[i][0]))
            count++;
    }

    return 13 * (int)(count == 4);
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
    (void)pat;
    return 0;
}

// 7 paires
int chiitoitsu(const Pattern *pat) {
    (void)pat;
    return 0;
}

// tout brelan
int toitoi(const Pattern *pat) {
    vec(GroupType) types = pattern_get_group_type(pat);

    for (u64 i = 0; i < vec_len(types); i++) {
        switch (types[i]) {
        case SEQUENCE:
        case CHI:
            vec_free(types);
            return 0;
        default:
            break;
        }
    }

    vec_free(types);
    return 2;
}

// trois brelans cachés
int sanankou(const Pattern *pat) {
    vec(GroupType) types = pattern_get_group_type(pat);

    int count = 0;
    for (u64 i = 0; i < vec_len(types); i++) {
        switch (types[i]) {
        case THREE_OF_KIND:
        case FOUR_OF_KIND:
            count++;
            break;
        default:
            break;
        }
    }

    vec_free(types);
    return 2 * (int)(count == 3);
}

// quatre brelans cachés
int suuankou(const Pattern *pat) {
    vec(GroupType) types = pattern_get_group_type(pat);

    int count = 0;
    for (u64 i = 0; i < vec_len(types); i++) {
        switch (types[i]) {
        case THREE_OF_KIND:
        case FOUR_OF_KIND:
            count++;
            break;
        default:
            break;
        }
    }

    vec_free(types);
    return 13 * (int)(count == 4);
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
        (types[k % 4] == THREE_OF_KIND || types[k % 4] == PON || types[k % 4] == KAHN || types[k % 4] == FOUR_OF_KIND) &&
        (types[(k + 1) % 4] == THREE_OF_KIND || types[(k + 1) % 4] == PON || types[(k + 1) % 4] == KAHN || types[(k + 1) % 4] == FOUR_OF_KIND) &&
        (types[(k + 2) % 4] == THREE_OF_KIND || types[(k + 2) % 4] == PON || types[(k + 2) % 4] == KAHN || types[(k + 2) % 4] == FOUR_OF_KIND) &&
        !tile_same_family(threes[k % 4][0], threes[(k + 1) % 4][0]) &&
        !tile_same_family(threes[k % 4][0], threes[(k + 2) % 4][0]) &&
        !tile_same_family(threes[(k + 1) % 4][0],threes[(k + 2) % 4][0]) &&
        v1 == v2 && v2 == v3) {
            int open = (int)pattern_is_open(pat);
            vec_free(types);
            return 2 - open;
        }
    }

    vec_free(types);
    return 0;
}

// trois carrés
int sankatsu(const Pattern *pat) {
    vec(GroupType) types = pattern_get_group_type(pat);

    int count = 0;
    for (u64 i = 0; i < vec_len(types); i++) {
        switch (types[i]) {
        case KAHN:
        case FOUR_OF_KIND:
            count++;
            break;
        default:
            break;
        }
    }

    vec_free(types);
    return 2 * (int)(count == 3);
}

// quatre carrés
int suukantsu(const Pattern *pat) {
    vec(GroupType) types = pattern_get_group_type(pat);

    int count = 0;
    for (u64 i = 0; i < vec_len(types); i++) {
        switch (types[i]) {
        case KAHN:
        case FOUR_OF_KIND:
            count++;
            break;
        default:
            break;
        }
    }

    vec_free(types);
    return 13 * (int)(count == 4);
}

// semi-pure
int honitsu(const Pattern *pat) {
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
            if (!((int)(groups[i][j]) == 33) &&
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
