#include "../model/hand.h"
#include "../model/yaku.h"
#include "../model/patterns.h"
#include "../utils/error.h"
#include <assert.h>

int main() {
    purple();
    printf("[TEST Yakus 2]\n");
    reset();

    //lipeikou
    Hand *h = hand_from_string("789123m111222p33s");
    vec(Pattern *) patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    Pattern *pat = patterns[vec_len(patterns) - 1];
    test(lipeikou(pat) == 0, "789123m111222p33s is not lipeikou");

    patterns_free(&patterns);
    hand_free(h);

    //ryanpeikou
    h = hand_from_string("789123m123123p33s");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[vec_len(patterns) - 1];
    test(ryanpeikou(pat) == 0, "789123m123123p33s is not ryanpeikou");

    patterns_free(&patterns);
    hand_free(h);

    //pinfu
    // TODO

    //shanshoku_doujun
    h = hand_from_string("123m234p12355566s");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[vec_len(patterns) - 1];
    test(shanshoku_doujun(pat) == 0, "123m234p12355566s is not shanshoku_doujun");

    patterns_free(&patterns);
    hand_free(h);

    //ittsuu
    h = hand_from_string("123456777m111p99s");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[vec_len(patterns) - 1];
    test(ittsuu(pat) == 0, "123456777m111p99s is not ittsuu");

    patterns_free(&patterns);
    hand_free(h);

    //tanyao
    h = hand_from_string("111456777m222p88s");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[vec_len(patterns) - 1];
    test(tanyao(pat) == 0, "111456777m222p88s is not tanyao");

    patterns_free(&patterns);
    hand_free(h);

    //yakuhai
    // TODO

    //shousangen
    h = hand_from_string("111m123p555666s77z");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[vec_len(patterns) - 1];
    test(shousangen(pat) == 0, "111m123p555666s77z is not shousangen");

    patterns_free(&patterns);
    hand_free(h);

    //daisangen
    h = hand_from_string("111m22p555666s777z");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[vec_len(patterns) - 1];
    test(daisangen(pat) == 0, "111m222p555666s77z is not daisangen");

    patterns_free(&patterns);
    hand_free(h);

    // shousuushi
    h = hand_from_string("111m111222333s44z");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[vec_len(patterns) - 1];
    test(shousuushi(pat) == 0, "111m111222333s44z is not shousuushi");

    patterns_free(&patterns);
    hand_free(h);

    //daisuushi
    h = hand_from_string("11m111222333s444z");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[vec_len(patterns) - 1];
    test(daisuushi(pat) == 0, "11m111222333s444z is not daisuushi");

    patterns_free(&patterns);
    hand_free(h);

    //chanta
    h = hand_from_string("123789m111p22s777z");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[vec_len(patterns) - 1];
    test(chanta(pat) == 0, "123789m111p22s777z is not chanta");

    patterns_free(&patterns);
    hand_free(h);

    //junchan
    h = hand_from_string("123789m111p22789s");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[vec_len(patterns) - 1];
    test(junchan(pat) == 0, "123789m111p22789s is not junchan");

    patterns_free(&patterns);
    hand_free(h);

    //honroutou
    h = hand_from_string("111999m111p888s11z");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[vec_len(patterns) - 1];
    test(honroutou(pat) == 0, "111999m111p888s11z is not honroutou");

    patterns_free(&patterns);
    hand_free(h);

    //chinroutou
    h = hand_from_string("111999m111p22999s");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[vec_len(patterns) - 1];
    test(chinroutou(pat) == 0, "111999m111p22999s is not chinroutou");

    patterns_free(&patterns);
    hand_free(h);

    //tsuuiisou
    h = hand_from_string("111222333444s55z");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[vec_len(patterns) - 1];
    test(tsuuiisou(pat) == 0, "111222333444s55z is not tsuuiisou");

    patterns_free(&patterns);
    hand_free(h);

    //kokuushi_musou
    // TODO

    //chiitoitsu
    // TODO

    //toitoi
    h = hand_from_string("111456m333444s55z");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[vec_len(patterns) - 1];
    test(toitoi(pat) == 0, "111456m333444s55z is not toitoi");

    patterns_free(&patterns);
    hand_free(h);

    //sanankou
    h = hand_from_string("123m123333p555s55z");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[vec_len(patterns) - 1];
    test(sanankou(pat) == 0, "123m123333p555s55z is not sanankou");

    patterns_free(&patterns);
    hand_free(h);

    //suuankou
    h = hand_from_string("111222789m444s55z");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[vec_len(patterns) - 1];
    test(suuankou(pat) == 0, "111222789m444s55z is not suuankou");

    patterns_free(&patterns);
    hand_free(h);

    //sanshoku_doukou
    h = hand_from_string("111m123p11123455s");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[vec_len(patterns) - 1];
    test(sanshoku_doukou(pat) == 0, "111m123p11123455s is not sanshoku_doukou");

    patterns_free(&patterns);
    hand_free(h);

    //sankatsu
    // TODO

    //suukantsu
    // TODO

    //honitsu
    h = hand_from_string("111456p333444m11z");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[vec_len(patterns) - 1];
    test(honitsu(pat) == 0, "111456p333444m11z is not honitsu");

    patterns_free(&patterns);
    hand_free(h);

    //chinitsu
    h = hand_from_string("111222789p44455m");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[vec_len(patterns) - 1];
    test(chinitsu(pat) == 0, "111222789p44455m is not chinitsu");

    patterns_free(&patterns);
    hand_free(h);

    //ryuuiisou
    h = hand_from_string("222333789p666s66z");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[vec_len(patterns) - 1];
    test(ryuuiisou(pat) == 0, "222333789p666s66z is not ryuuiisou");

    patterns_free(&patterns);
    hand_free(h);

    //churen_poutou
    h = hand_from_string("11123456789971m");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[vec_len(patterns) - 1];
    test(churen_poutou(pat) == 0, "11123456789971m is not churen_poutou");

    patterns_free(&patterns);
    hand_free(h);

    return 0;
}
