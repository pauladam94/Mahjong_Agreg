#ifndef YAKU_H
#define YAKU_H
#include "../utils/vec.h"
#include "hand.h"

struct yaku {
    char *name;
    int han;
};
typedef struct yaku yaku;

vec(yaku) max_yaku(const Hand *hand); // TODO
vec(yaku) find_yaku(Pattern *pat);    // TODO

int fu(const Hand *hand); // TODO (attente)

// return the number of Han
int lipeikou(Pattern *pat);
int ryanpeikou(Pattern *pat);
int pinfu(Pattern *pat); // TODO (attente)
int shanshoku_doujun(Pattern *pat);
int ittsuu(Pattern *pat);
int tanyao(Pattern *pat);
int yakuhai(Pattern *pat); // TODO (vent du joueur)
int shousangen(Pattern *pat);
int daisangen(Pattern *pat);
int shousuushi(Pattern *pat);
int daisuushi(Pattern *pat);
int chanta(Pattern *pat);
int junchan(Pattern *pat);
int honroutou(Pattern *pat);
int chinroutou(Pattern *pat);
int tsuuiisou(Pattern *pat);
int kokuushi_musou(Pattern *pat); // TODO (13 orphelins)
int chiitoitsu(Pattern *pat);     // TODO (7 paires)
int toitoi(Pattern *pat);
int sanankou(Pattern *pat);
int suuankou(Pattern *pat);
int sanshoku_doukou(Pattern *pat);
int sankatsu(Pattern *pat);
int suukantsu(Pattern *pat);
int honitsu(Pattern *pat);
int chinitsu(Pattern *pat);
int ryuuiisou(Pattern *pat);
int churen_poutou(Pattern *pat); // TODO (flemme)

#endif
