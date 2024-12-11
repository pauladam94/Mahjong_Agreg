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

vec(yaku) max_yaku(const Hand *hand);
vec(yaku) find_yaku(Pattern *pat, bool open);

bool lipeikou(Pattern *pat, bool open);
bool ryanpeikou(Pattern *pat, bool open);
bool pinfu(Pattern *pat, bool open); // TODO (attente)
bool shanshoku_doujun(Pattern *pat, bool open); // TODO
bool ittsuu(Pattern *pat, bool open); // TODO
bool tanyao(Pattern *pat, bool open);
bool yakuhai(Pattern *pat, bool open); // TODO
bool shousangen(Pattern *pat, bool open);
bool daisangen(Pattern *pat, bool open);
bool shousuushi(Pattern *pat, bool open);
bool daisuushi(Pattern *pat, bool open);
bool chanta(Pattern *pat, bool open); // TODO
bool junchan(Pattern *pat, bool open); // TODO
bool honroutou(Pattern *pat, bool open);
bool chinroutou(Pattern *pat, bool open);
bool tsuuiisou(Pattern *pat, bool open);
bool kokuushi_musou(Pattern *pat, bool open); // TODO
bool chiitoitsu(Pattern *pat, bool open); // TODO
bool toitoi(Pattern *pat, bool open);
bool sanankou(Pattern *pat, bool open); // TODO
bool suuankou(Pattern *pat, bool open);
bool sanshoku_doukou(Pattern *pat, bool open); // TODO
bool sankatsu(Pattern *pat, bool open); // TODO
bool suukantsu(Pattern *pat, bool open); // TODO
bool honitsu(Pattern *pat, bool open);
bool chinitsu(Pattern *pat, bool open);
bool ryuuiisou(Pattern *pat, bool open);
bool churen_poutou(Pattern *pat, bool open);

#endif