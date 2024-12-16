#include "../model/hand.h"
#include "../model/yaku.h"
#include "../utils/error.h"

int main() {
    purple();
    printf("[TEST Yakus 2]\n");
    reset();

    //lipeikou
    Hand *h = hand_from_string("789999m111222p33s");
    vec(Pattern *) patterns = hand_patterns(h);

    Pattern *pat = patterns[vec_len(patterns) - 1];
    test(lipeikou(pat) == 0, "78999m111222p33s is not lipeikou");

    hand_free(h);

    //ryanpeikou
    h = hand_from_string("789999m123123p33s");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(ryanpeikou(pat) == 0, "789999m123123p33s is not ryanpeikou");

    hand_free(h);

    //pinfu
    // TODO

    //shanshoku_doujun
    h = hand_from_string("123m123p23455566s");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(shanshoku_doujun(pat) == 0, "123m123p23455566s is not shanshoku_doujun");

    hand_free(h);

    //ittsuu
    h = hand_from_string("234456789m111p99s");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(ittsuu(pat) == 0, "234456789m111p99s is not ittsuu");

    hand_free(h);

    //tanyao
    h = hand_from_string("123456777m222p88s");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(tanyao(pat) == 0, "123456777m222p88s is not tanyao");

    hand_free(h);

    //yakuhai
    // TODO

    //shousangen
    h = hand_from_string("111m222p555s666z77z");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(shousangen(pat) == 0, "111m222p555s666z77z is not shousangen");

    hand_free(h);

    //daisangen
    h = hand_from_string("111m22p555s666z777z");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(daisangen(pat) == 0, "111m222p555s666z77z is not daisangen");

    hand_free(h);

    //shousuushi
    h = hand_from_string("111m111s222z333z44z");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(shousuushi(pat) == 0, "111m111s222z333z44z is not shousuushi");

    hand_free(h);

    //daisuushi
    h = hand_from_string("11m111s222z333z444z");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(daisuushi(pat) == 0, "11m111s222z333z444z is not daisuushi");

    hand_free(h);

    //chanta
    h = hand_from_string("234789m111p11z777z");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(chanta(pat) == 0, "234789m111p11z777z is not chanta");

    hand_free(h);

    //junchan
    h = hand_from_string("234789m111p11789s");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(junchan(pat) == 0, "234789m111p11789s is not junchan");

    hand_free(h);

    //honroutou
    h = hand_from_string("123999m111p999s11z");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(honroutou(pat) == 0, "123999m111p999s11z is not honroutou");

    hand_free(h);

    //chinroutou
    h = hand_from_string("111999m111p11888s");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(chinroutou(pat) == 0, "111999m111p11888s is not chinroutou");

    hand_free(h);

    //tsuuiisou
    h = hand_from_string("111m22233344455z");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(tsuuiisou(pat) == 0, "111m22233344455z is not tsuuiisou");

    hand_free(h);

    //kokuushi_musou
    // TODO

    //chiitoitsu
    // TODO

    //toitoi
    h = hand_from_string("111222333456m55z");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(toitoi(pat) == 0, "111222333456m55z is not toitoi");

    hand_free(h);

    //sanankou
    h = hand_from_string("123m123333456s55z");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(sanankou(pat) == 0, "123m123333456s55z is not sanankou");

    hand_free(h);

    //suuankou
    h = hand_from_string("123m123333456s55z");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(suuankou(pat) == 0, "123m123333456s55z is not suuankou");

    hand_free(h);

    //sanshoku_doukou
    h = hand_from_string("111m111p22223455s");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(sanshoku_doukou(pat) == 0, "111m111p22223455s is not sanshoku_doukou");

    hand_free(h);

    //sankatsu
    // TODO

    //suukantsu
    // TODO

    //honitsu
    h = hand_from_string("111222333444m11s");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(honitsu(pat) == 0, "111222333444m11s is not honitsu");

    hand_free(h);

    //chinitsu
    h = hand_from_string("111222333444m55s");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(chinitsu(pat) == 0, "111222333444m55s is not chinitsu");

    hand_free(h);

    //ryuuiisou
    h = hand_from_string("222333444666s77z");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(ryuuiisou(pat) == 0, "222333444666s88z is not ryuuiisou");

    hand_free(h);

    //churen_poutou
    // TODO
}
