#ifndef YAKU_C
#define YAKU_C
#include "yaku.h"

vec(yaku) max_yaku(const Hand *hand)
{
    // no complete, no yaku
    if (!hand_is_complete(hand)) return NULL;

    Patterns *patterns = hand_patterns(hand);
}

// return all the yaku for a given pattern
vec(yaku) find_yaku(Pattern *pat, bool open) {
    vec(yaku) yakus = NULL;

    if (lipeikou(pat, open)) {
        yaku y = {"Lipeikou", 1};
        vec_push(yakus, y);
    }
    if (ryanpeikou(pat, open)) {
        yaku y = {"Ryanpeikou", 3};
        vec_push(yakus, y);
    }
    if (pinfu(pat, open)) {
        yaku y = {"Pinfu", 1};
        vec_push(yakus, y);
    }
    if (shanshoku_doujun(pat, open)) {
        yaku y = {"Shanshoku Doujun", 2 - (int)open};
        vec_push(yakus, y);
    }
    if (ittsuu(pat, open)) {
        yaku y = {"Ittsuu", 2 - (int)open};
        vec_push(yakus, y);
    }
    if (tanyao(pat, open)) {
        yaku y = {"Tanyao", 1};
        vec_push(yakus, y);
    }
    if (yakuhai(pat, open)) {
        yaku y = {"Yakuhai", 1};
        vec_push(yakus, y);
    }
    if (shousangen(pat, open)) {
        yaku y = {"Shousangen", 2};
        vec_push(yakus, y);
    }
    if (daisangen(pat, open)) {
        yaku y = {"Daisangen", 13};
        vec_push(yakus, y);
    }
    if (shousuushi(pat, open)) {
        yaku y = {"Shousuushi", 13};
        vec_push(yakus, y);
    }
    if (daisuushi(pat, open)) {
        yaku y = {"Daisuushi", 13};
        vec_push(yakus, y);
    }
    if (chanta(pat, open)) {
        yaku y = {"Chanta", 2 - (int)open};
        vec_push(yakus, y);
    }
    if (junchan(pat, open)) {
        yaku y = {"Junchan", 3 - (int)open};
        vec_push(yakus, y);
    }
    if (honroutou(pat, open)) {
        yaku y = {"Honroutou", 2};
        vec_push(yakus, y);
    }
    if (chinroutou(pat, open)) {
        yaku y = {"Chinroutou", 13};
        vec_push(yakus, y);
    }
    if (tsuuiisou(pat, open)) {
        yaku y = {"Tsuuiisou", 13};
        vec_push(yakus, y);
    }
    if (kokuushi_musou(pat, open)) {
        yaku y = {"Kokuushi Musou", 13};
        vec_push(yakus, y);
    }
    if (chiitoitsu(pat, open)) {
        yaku y = {"Chiitoitsu", 2};
        vec_push(yakus, y);
    }
    if (toitoi(pat, open)) {
        yaku y = {"Toitoi", 2};
        vec_push(yakus, y);
    }
    if (sanankou(pat, open)) {
        yaku y = {"Sanankou", 2};
        vec_push(yakus, y);
    }
    if (suuankou(pat, open)) {
        yaku y = {"Suuankou", 13};
        vec_push(yakus, y);
    }
    if (sanshoku_doukou(pat, open)) {
        yaku y = {"Sanshoku Doukou", 2};
        vec_push(yakus, y);
    }
    if (sankatsu(pat, open)) {
        yaku y = {"Sankatsu", 2};
        vec_push(yakus, y);
    }
    if (suukantsu(pat, open)) {
        yaku y = {"Suukantsu", 13};
        vec_push(yakus, y);
    }
    if (honitsu(pat, open)) {
        yaku y = {"Honitsu", 3 - (int)open};
        vec_push(yakus, y);
    }
    if (chinitsu(pat, open)) {
        yaku y = {"Chinitsu", 6 - (int)open};
        vec_push(yakus, y);
    }
    if (ryuuiisou(pat, open)) {
        yaku y = {"Ryuuiisou", 13};
        vec_push(yakus, y);
    }
    if (churen_poutou(pat, open)) {
        yaku y = {"Churen Poutou", 13};
        vec_push(yakus, y);
    }

    return yakus;
}


// function testing the yakus


// double suite pure
bool lipeikou(Pattern *pat, bool open) {
    if (open) return false;

    for (int i = 0; i < 4; i++) {
        for (int j = 1; j < 4; j++) {
            for (int k = 0; k < 3; k++) {
                if (pattern_get_group(pat)[i][k] != pattern_get_group(pat)[j][k]) {
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
bool ryanpeikou(Pattern *pat, bool open) {
    if (open) return false;

    int count = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            for (int k = 0; k < 3; k++) {
                if (pattern_get_group(pat)[i][k] != pattern_get_group(pat)[j][k]) {
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
bool pinfu(Pattern *pat, bool open) {
    return false;
}

// triple suite
bool shanshoku_doujun(Pattern *pat, bool open) {
    return false;
}

// grande suite pure
bool ittsuu(Pattern *pat, bool open) {
    return false;
}

// tout ordinaire
bool tanyao(Pattern *pat, bool open) {
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
bool yakuhai(Pattern *pat, bool open) {
    return false;
}

// trois petits dragons
bool shousangen(Pattern *pat, bool open) {
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
bool daisangen(Pattern *pat, bool open) {
    int count = 0;
    for (int i = 0; i < 4; i++) {
        if (tile_is_dragon(pattern_get_group(pat)[i][0])) {
            count++;
        }
    }
    return count == 3;
}

// quatre petits vents
bool shousuushi(Pattern *pat, bool open) {
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
bool daisuushi(Pattern *pat, bool open) {
    int count = 0;
    for (int i = 0; i < 4; i++) {
        if (tile_is_wind(pattern_get_group(pat)[i][0])) {
            count++;
        }
    }
    return count == 4;
}

// terminale et honneurs de partout
bool chanta(Pattern *pat, bool open) {
    return false;
}

// terminale partout
bool junchan(Pattern *pat, bool open) {
    return false;
}

// tout terminale et honneur
bool honroutou(Pattern *pat, bool open) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            if (!tile_is_terminal(pattern_get_group(pat)[i][j]) && !tile_is_honor(pattern_get_group(pat)[i][j])) {
                return false;
            }
        }
    }
    for (int i = 0; i < 2; i++) {
        if (!tile_is_terminal(pattern_get_pair(pat)[i]) && !tile_is_honor(pattern_get_pair(pat)[i])) {
            return false;
        }
    }
    return true;
}

// tout terminale
bool chinroutou(Pattern *pat, bool open) {
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
bool tsuuiisou(Pattern *pat, bool open) {
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
bool kokuushi_musou(Pattern *pat, bool open) {
    return false;
}

// 7 paires
bool chiitoitsu(Pattern *pat, bool open) {
    return false;
}

// tout brelan
bool toitoi(Pattern *pat, bool open) {
    for (int i = 0; i < 4; i++) {
        if (!tile_equals(pattern_get_group(pat)[i][0], pattern_get_group(pat)[i][1])) return false;
    }
    return true;
}

// trois brelans cachés
bool sanankou(Pattern *pat, bool open) {
    return false;
}

// quatre brelans cachés
bool suuankou(Pattern *pat, bool open) {
    if (open) return false;

    int count = 0;
    for (int i = 0; i < 4; i++) {
        if (tile_equals(pattern_get_group(pat)[i][0], pattern_get_group(pat)[i][1])) {
            count++;
        }
    }
    return count == 4;
}

// triple brelan
bool sanshoku_doukou(Pattern *pat, bool open) {
    return false;
}

// trois carrés
bool sankatsu(Pattern *pat, bool open) {
    return false;
}

// quatre carrés
bool suukantsu(Pattern *pat, bool open) {
    return false;
}

// semi-pure
bool honitsu(Pattern *pat, bool open) {
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
bool chinitsu(Pattern *pat, bool open) {
    if (!tile_is_family(pattern_get_pair(pat)[0])) {
        return false;
    }
    for (int i = 0; i < 4; i++) {
        if (!tile_same_family(pattern_get_pair(pat)[0], pattern_get_group(pat)[i][0])) {
            return false;
        }
    }
    return true;
}

// main verte
bool ryuuiisou(Pattern *pat, bool open) {

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            if (!tile_is_su(pattern_get_group(pat)[i][j]) && tile_number(pattern_get_group(pat)[i][j]) != 33) { // 33 = green dragon
                return false;
            }
        }
    }
    for (int i = 0; i < 2; i++) {
        if (!tile_is_su(pattern_get_pair(pat)[i]) && tile_number(pattern_get_pair(pat)[i]) != 33) {
            return false;
        }
    }
    return true;
}

// neuf portes
bool churen_poutou(Pattern *pat, bool open) {
    return false;
}

#endif