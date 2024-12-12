#ifndef YAKU_H
#define YAKU_H
#include "hand.h"
#include "../utils/vec.h"

struct yaku
{
    char *name;
    int han;
};
typedef struct yaku yaku;

vec(yaku) max_yaku(const Hand *hand); // TODO
vec(yaku) find_yaku(Pattern *pat, bool open); // TODO

int fu(const Hand *hand); // TODO (attente)

bool lipeikou(Pattern *pat, bool open);
bool ryanpeikou(Pattern *pat, bool open);
bool pinfu(Pattern *pat, bool open); // TODO (attente)
bool shanshoku_doujun(Pattern *pat, bool open);
bool ittsuu(Pattern *pat, bool open);
bool tanyao(Pattern *pat, bool open);
bool yakuhai(Pattern *pat, bool open); // TODO (vent du joueur)
bool shousangen(Pattern *pat, bool open);
bool daisangen(Pattern *pat, bool open);
bool shousuushi(Pattern *pat, bool open);
bool daisuushi(Pattern *pat, bool open);
bool chanta(Pattern *pat, bool open);
bool junchan(Pattern *pat, bool open);
bool honroutou(Pattern *pat, bool open);
bool chinroutou(Pattern *pat, bool open);
bool tsuuiisou(Pattern *pat, bool open);
bool kokuushi_musou(Pattern *pat, bool open); // TODO (13 orphelins)
bool chiitoitsu(Pattern *pat, bool open); // TODO (7 paires)
bool toitoi(Pattern *pat, bool open);
bool sanankou(Pattern *pat, bool open); // TODO (flemme)
bool suuankou(Pattern *pat, bool open);
bool sanshoku_doukou(Pattern *pat, bool open);
bool sankatsu(Pattern *pat, bool open); // TODO (carrés)
bool suukantsu(Pattern *pat, bool open); // TODO (carrés)
bool honitsu(Pattern *pat, bool open);
bool chinitsu(Pattern *pat, bool open);
bool ryuuiisou(Pattern *pat, bool open);
bool churen_poutou(Pattern *pat, bool open);

#endif