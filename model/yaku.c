#include "yaku.h"
#include "pattern.h"

typedef enum Yaku {
    LIPEIKOU,
    // All other
} Yaku;

vec(yaku) max_yaku(const Hand *hand) {
    // no complete, no yaku
    if (!hand_is_complete(hand))
        return NULL;

    vec(Pattern *) patterns = hand_patterns(hand);
}

// return all the yaku for a given pattern
vec(yaku) find_yaku(Pattern *pat) {
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
        yaku y = {"Chinroutou", 13};
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
        yaku y = {"Chiitoitsu", 2};
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
        yaku y = {"Chinitsu", 6 - pattern_is_open(pat)};
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
bool lipeikou(Pattern *pat) {
    if (pattern_is_open(pat))
        return false;

    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            for (int k = 0; k < 3; k++) {
                if (pattern_get_group(pat)[i][k] !=
                    pattern_get_group(pat)[j][k]) {
                    break;
                }
                if (k == 2) {
                    return true;
                }
            }
        }
    }
    return false;
}

// deux doubles suites pures
bool ryanpeikou(Pattern *pat) {
    if (pattern_is_open(pat))
        return false;

    int count = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            for (int k = 0; k < 3; k++) {
                if (pattern_get_group(pat)[i][k] !=
                    pattern_get_group(pat)[j][k]) {
                    break;
                }
                if (k == 2) {
                    count++;
                }
            }
        }
    }
    return count == 2;
}

// aucun fu
bool pinfu(Pattern *pat) { return false; }

// triple suite
bool shanshoku_doujun(Pattern *pat) {
    Tile ***groups = pattern_get_group(pat);
    for (int k = 0; k < 4; k++) {
        if (tile_number(groups[(k) % 4][0]) ==
                tile_number(groups[(k + 1) % 4][0]) &&
            tile_number(groups[(k) % 4][0]) ==
                tile_number(groups[(k + 2) % 4][0]) &&
            tile_number(groups[(k) % 4][0]) + 1 ==
                tile_number(groups[(k) % 4][0]) &&
            tile_number(groups[(k + 1) % 4][0]) + 1 ==
                tile_number(groups[(k + 1) % 4][0]) &&
            tile_number(groups[(k + 2) % 4][0]) + 1 ==
                tile_number(groups[(k + 2) % 4][0])) {
            return true;
        }
    }
    return false;
}

// grande suite pure
bool ittsuu(Pattern *pat) {
    Tile ***groups = pattern_get_group(pat);
    for (int k = 0; k < 4; k++) {
        int count = 1;
        int v1 = tile_number(groups[(k) % 4][0]);
        int v2 = tile_number(groups[(k + 1) % 4][0]);
        int v3 = tile_number(groups[(k + 2) % 4][0]);
        if (v1 % 4 == 1 && v2 % 4 == 1 &&
            tile_same_family(groups[(k) % 4][0], groups[(k + 1) % 4][0]) &&
            v3 % 4 == 1 &&
            tile_same_family(groups[(k) % 4][0], groups[(k + 2) % 4][0]) &&
            v1 * v2 * v3 == 28) {
            return true;
        }
    }
    return false;
}

// tout ordinaire
bool tanyao(Pattern *pat) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            if (!tile_is_terminal(pattern_get_group(pat)[i][j])) {
                return false;
            }
        }
    }
    for (int i = 0; i < 2; i++) {
        if (!tile_is_terminal(pattern_get_pair(pat)[i])) {
            return false;
        }
    }
    return true;
}

// brelan de valeur
bool yakuhai(Pattern *pat) { return false; }

// trois petits dragons
bool shousangen(Pattern *pat) {
    int count = 0;
    if (tile_is_dragon(pattern_get_pair(pat)[0])) {
        count++;
    }
    for (int i = 0; i < 4; i++) {
        if (tile_is_dragon(pattern_get_group(pat)[i][0])) {
            count++;
        }
    }
    return count == 3;
}

// trois grands dragons
bool daisangen(Pattern *pat) {
    int count = 0;
    for (int i = 0; i < 4; i++) {
        if (tile_is_dragon(pattern_get_group(pat)[i][0])) {
            count++;
        }
    }
    return count == 3;
}

// quatre petits vents
bool shousuushi(Pattern *pat) {
    int count = 0;
    if (tile_is_wind(pattern_get_pair(pat)[0])) {
        count++;
    }
    for (int i = 0; i < 4; i++) {
        if (tile_is_wind(pattern_get_group(pat)[i][0])) {
            count++;
        }
    }
    return count == 4;
}

// quatre grands vents
bool daisuushi(Pattern *pat) {
    int count = 0;
    for (int i = 0; i < 4; i++) {
        if (tile_is_wind(pattern_get_group(pat)[i][0])) {
            count++;
        }
    }
    return count == 4;
}

// terminale et honneurs de partout
bool chanta(Pattern *pat) {
    Tile ***groups = pattern_get_group(pat);
    for (int i = 0; i < 4; i++) {
        if (!tile_is_terminal(groups[i][0]) &&
            !tile_is_terminal(groups[i][2]) && !tile_is_honor(groups[i][0])) {
            return false;
        }
    }
    if (!tile_is_terminal(pattern_get_pair(pat)[0]) &&
        !tile_is_honor(pattern_get_pair(pat)[0])) {
        return false;
    }
    return true;
}

// terminale partout
bool junchan(Pattern *pat) {
    Tile ***groups = pattern_get_group(pat);
    for (int i = 0; i < 4; i++) {
        for (int k = 0; k < 3; k++) {
            if (!tile_is_terminal(groups[i][k])) {
                return false;
            }
        }
    }
    if (!tile_is_terminal(pattern_get_pair(pat)[0])) {
        return false;
    }
    return true;
}

// tout terminale et honneur
bool honroutou(Pattern *pat) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            if (!tile_is_terminal(pattern_get_group(pat)[i][j]) &&
                !tile_is_honor(pattern_get_group(pat)[i][j])) {
                return false;
            }
        }
    }
    for (int i = 0; i < 2; i++) {
        if (!tile_is_terminal(pattern_get_pair(pat)[i]) &&
            !tile_is_honor(pattern_get_pair(pat)[i])) {
            return false;
        }
    }
    return true;
}

// tout terminale
bool chinroutou(Pattern *pat) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            if (!tile_is_terminal(pattern_get_group(pat)[i][j])) {
                return false;
            }
        }
    }
    for (int i = 0; i < 2; i++) {
        if (!tile_is_terminal(pattern_get_pair(pat)[i])) {
            return false;
        }
    }
    return true;
}

// tout honneur
bool tsuuiisou(Pattern *pat) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            if (!tile_is_honor(pattern_get_group(pat)[i][j])) {
                return false;
            }
        }
    }
    for (int i = 0; i < 2; i++) {
        if (!tile_is_honor(pattern_get_pair(pat)[i])) {
            return false;
        }
    }
    return true;
}

// 13 orphelins
bool kokuushi_musou(Pattern *pat) { return false; }

// 7 paires
bool chiitoitsu(Pattern *pat) { return false; }

// tout brelan
bool toitoi(Pattern *pat) {
    for (int i = 0; i < 4; i++) {
        if (!tile_equals(pattern_get_group(pat)[i][0],
                         pattern_get_group(pat)[i][1]))
            return false;
    }
    return true;
}

// trois brelans cachés
bool sanankou(Pattern *pat) { return false; }

// quatre brelans cachés
bool suuankou(Pattern *pat) {
    if (pattern_is_open(pat))
        return false;

    int count = 0;
    for (int i = 0; i < 4; i++) {
        if (tile_equals(pattern_get_group(pat)[i][0],
                        pattern_get_group(pat)[i][1])) {
            count++;
        }
    }
    return count == 4;
}

// triple brelan
bool sanshoku_doukou(Pattern *pat) {
    Tile ***groups = pattern_get_group(pat);
    for (int k = 0; k < 4; k++) {
        if (tile_number(groups[(k) % 4][0]) ==
                tile_number(groups[(k) % 4][1]) &&
            tile_number(groups[(k + 1) % 4][0]) ==
                tile_number(groups[(k + 1) % 4][1]) &&
            tile_number(groups[(k + 2) % 4][0]) ==
                tile_number(groups[(k + 2) % 4][1]) &&
            tile_number(groups[(k) % 4][0]) ==
                tile_number(groups[(k + 1) % 4][0]) &&
            tile_number(groups[(k) % 4][0]) ==
                tile_number(groups[(k + 2) % 4][0]) &&
            !tile_same_family(groups[(k) % 4][0], groups[(k + 1) % 4][0]) &&
            !tile_same_family(groups[(k) % 4][0], groups[(k + 2) % 4][0])) {
            return true;
        }
    }
    return false;
}

// trois carrés
bool sankatsu(Pattern *pat) { return false; }

// quatre carrés
bool suukantsu(Pattern *pat) { return false; }

// semi-pure
bool honitsu(Pattern *pat) {
    Tile *ref = NULL;
    for (int i = 0; i < 4; i++) {
        if (tile_is_family(pattern_get_group(pat)[i][0])) {
            if (ref == NULL) {
                ref = pattern_get_group(pat)[i][0];
            } else if (!tile_same_family(ref, pattern_get_group(pat)[i][0])) {
                return false;
            }
        }
    }
    if (tile_is_family(pattern_get_pair(pat)[0])) {
        if (ref == NULL) {
            ref = pattern_get_pair(pat)[0];
        } else if (!tile_same_family(ref, pattern_get_pair(pat)[0])) {
            return false;
        }
    }
    return true;
}

// main pure
bool chinitsu(Pattern *pat) {
    if (!tile_is_family(pattern_get_pair(pat)[0])) {
        return false;
    }
    for (int i = 0; i < 4; i++) {
        if (!tile_same_family(pattern_get_pair(pat)[0],
                              pattern_get_group(pat)[i][0])) {
            return false;
        }
    }
    return true;
}

// main verte
bool ryuuiisou(Pattern *pat) {

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            if (!tile_is_su(pattern_get_group(pat)[i][j]) &&
                tile_number(pattern_get_group(pat)[i][j]) !=
                    33) { // 33 = green dragon
                return false;
            }
        }
    }
    for (int i = 0; i < 2; i++) {
        if (!tile_is_su(pattern_get_pair(pat)[i]) &&
            tile_number(pattern_get_pair(pat)[i]) != 33) {
            return false;
        }
    }
    return true;
}

// neuf portes
bool churen_poutou(Pattern *pat) { return false; }
