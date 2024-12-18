#ifndef YAKU_H
#define YAKU_H
#include "../utils/vec.h"
#include "hand.h"

typedef enum Yaku_name {
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
} Yaku_name;

typedef struct yaku {
    Yaku_name name;
    int han;
} yaku;

vec(yaku) max_yaku(const Hand *hand); // TODO
vec(yaku) find_yaku(const Pattern *pat);

int fu(const Hand *hand); // TODO (attente)

// return the number of Han
int lipeikou(const Pattern *pat);
int ryanpeikou(const Pattern *pat);
int pinfu(const Pattern *pat); // TODO (attente)
int shanshoku_doujun(const Pattern *pat);
int ittsuu(const Pattern *pat);
int tanyao(const Pattern *pat);
int yakuhai(const Pattern *pat); // TODO (vent du joueur)
int shousangen(const Pattern *pat);
int daisangen(const Pattern *pat);
int shousuushi(const Pattern *pat);
int daisuushi(const Pattern *pat);
int chanta(const Pattern *pat);
int junchan(const Pattern *pat);
int honroutou(const Pattern *pat);
int chinroutou(const Pattern *pat);
int tsuuiisou(const Pattern *pat);
int kokuushi_musou(const Pattern *pat); // TODO (13 orphelins)
int chiitoitsu(const Pattern *pat);
int toitoi(const Pattern *pat);
int sanankou(const Pattern *pat);
int suuankou(const Pattern *pat);
int sanshoku_doukou(const Pattern *pat);
int sankatsu(const Pattern *pat);
int suukantsu(const Pattern *pat);
int honitsu(const Pattern *pat);
int chinitsu(const Pattern *pat);
int ryuuiisou(const Pattern *pat);
int churen_poutou(const Pattern *pat);

extern int (*yakus_list[])(const Pattern *pat);

#endif
