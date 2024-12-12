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

bool lipeikou(Pattern *pat);
bool ryanpeikou(Pattern *pat);
bool pinfu(Pattern *pat); // TODO (attente)
bool shanshoku_doujun(Pattern *pat);
bool ittsuu(Pattern *pat);
bool tanyao(Pattern *pat);
bool yakuhai(Pattern *pat); // TODO (vent du joueur)
bool shousangen(Pattern *pat);
bool daisangen(Pattern *pat);
bool shousuushi(Pattern *pat);
bool daisuushi(Pattern *pat);
bool chanta(Pattern *pat);
bool junchan(Pattern *pat);
bool honroutou(Pattern *pat);
bool chinroutou(Pattern *pat);
bool tsuuiisou(Pattern *pat);
bool kokuushi_musou(Pattern *pat); // TODO (13 orphelins)
bool chiitoitsu(Pattern *pat);     // TODO (7 paires)
bool toitoi(Pattern *pat);
bool sanankou(Pattern *pat); // TODO (flemme)
bool suuankou(Pattern *pat);
bool sanshoku_doukou(Pattern *pat);
bool sankatsu(Pattern *pat);  // TODO (carrés)
bool suukantsu(Pattern *pat); // TODO (carrés)
bool honitsu(Pattern *pat);
bool chinitsu(Pattern *pat);
bool ryuuiisou(Pattern *pat);
bool churen_poutou(Pattern *pat);

#endif
