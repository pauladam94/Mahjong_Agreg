#include "../model/hand.h"
#include "../model/yaku.h"
#include "../model/patterns.h"
#include "../utils/error.h"
#include <assert.h>

int main() {
    purple();
    printf("[TEST Yakus 1]\n");
    reset();

    //lipeikou
    Hand *h = hand_from_string("789789m111222p33s");
    vec(Pattern *) patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    Pattern *pat = patterns[vec_len(patterns) - 1];
    test(lipeikou(pat) == 1, "789789m111222p33s is lipeikou");

    patterns_free(&patterns);
    hand_free(h);

    //ryanpeikou
    h = hand_from_string("789789m123123p33s");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[vec_len(patterns) - 1];
    test(ryanpeikou(pat) == 3, "789789m123123p33s is ryanpeikou");

    patterns_free(&patterns);
    hand_free(h);

    //pinfu
    // TODO

    //shanshoku_doujun
    h = hand_from_string("123m123p12355566s");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[vec_len(patterns) - 1];
    test(shanshoku_doujun(pat) == 2, "123m123p12355566s is shanshoku_doujun");

    patterns_free(&patterns);
    hand_free(h);

    //ittsuu
    h = hand_from_string("123456789m111p99s");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[vec_len(patterns) - 1];
    test(ittsuu(pat) == 2, "123456789m111p99s is ittsuu");

    patterns_free(&patterns);
    hand_free(h);

    //tanyao
    h = hand_from_string("222456777m222p88s");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[vec_len(patterns) - 1];
    test(tanyao(pat) == 1, "222456777m222p88s is tanyao");

    patterns_free(&patterns);
    hand_free(h);

    //yakuhai
    // TODO

    //shousangen
    h = hand_from_string("111m222p55566677z");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[vec_len(patterns) - 1];
    test(shousangen(pat) == 2, "111m222p55566677z is shousangen");

    patterns_free(&patterns);
    hand_free(h);

    //daisangen
    h = hand_from_string("111m22p555666777z");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[vec_len(patterns) - 1];
    test(daisangen(pat) == 13, "111m222p55566677z is daisangen");

    patterns_free(&patterns);
    hand_free(h);

    // shousuushi
    h = hand_from_string("111m11122233344z");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[vec_len(patterns) - 1];
    test(shousuushi(pat) == 13, "111m11122233344z is shousuushi");

    patterns_free(&patterns);
    hand_free(h);

    //daisuushi
    h = hand_from_string("11m111222333444z");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[vec_len(patterns) - 1];
    test(daisuushi(pat) == 13, "11m111222333444z is daisuushi");

    patterns_free(&patterns);
    hand_free(h);

    //chanta
    h = hand_from_string("123789m111p11z777z");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[vec_len(patterns) - 1];
    test(chanta(pat) == 2, "123789m111p11z777z is chanta");

    patterns_free(&patterns);
    hand_free(h);

    //junchan
    h = hand_from_string("123789m111p11789s");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[vec_len(patterns) - 1];
    test(junchan(pat) == 3, "123789m111p11789s is junchan");

    patterns_free(&patterns);
    hand_free(h);

    //honroutou
    h = hand_from_string("111999m111p999s11z");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[vec_len(patterns) - 1];
    test(honroutou(pat) == 2, "111999m111p999s11z is honroutou");

    patterns_free(&patterns);
    hand_free(h);

    //chinroutou
    h = hand_from_string("111999m111p11999s");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[vec_len(patterns) - 1];
    test(chinroutou(pat) == 13, "111999m111p11999s is chinroutou");

    patterns_free(&patterns);
    hand_free(h);

    //tsuuiisou
    h = hand_from_string("11122233344455z");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[vec_len(patterns) - 1];
    test(tsuuiisou(pat) == 13, "11122233344455z is tsuuiisou");

    patterns_free(&patterns);
    hand_free(h);

    //kokuushi_musou
    // TODO

    // //chiitoitsu
    // h = hand_from_string("113355m4455p6677s");
    // patterns = hand_patterns(h);
    // assert(vec_len(patterns) >= 1);

    // pat = patterns[vec_len(patterns) - 1];
    // test(chiitoitsu(pat) == 2, "113355m4455p6677s is chiitoitsu");

    //toitoi
    h = hand_from_string("111222m333444s55z");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[vec_len(patterns) - 1];
    test(toitoi(pat) == 2, "111222m333444s55z is toitoi");

    patterns_free(&patterns);
    hand_free(h);

    //sanankou
    h = hand_from_string("123m222333555s55z");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[vec_len(patterns) - 1];
    test(sanankou(pat) == 2, "123m222333555s55z is sanankou");

    patterns_free(&patterns);
    hand_free(h);

    //suuankou
    h = hand_from_string("111222888444s55z");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[vec_len(patterns) - 1];
    test(suuankou(pat) == 13, "111222888444s55z is suuankou");

    patterns_free(&patterns);
    hand_free(h);

    //sanshoku_doukou
    h = hand_from_string("111m111p11123455s");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[vec_len(patterns) - 1];
    test(sanshoku_doukou(pat) == 2, "111m111p11123455s is sanshoku_doukou");

    patterns_free(&patterns);
    hand_free(h);

    //sankatsu
    // TODO

    //suukantsu
    // TODO

    //honitsu
    h = hand_from_string("111222333444m11z");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[vec_len(patterns) - 1];
    test(honitsu(pat) == 3, "111222333444m11z is honitsu");

    patterns_free(&patterns);
    hand_free(h);

    //chinitsu
    h = hand_from_string("11122233344455m");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[vec_len(patterns) - 1];
    test(chinitsu(pat) == 6, "11122233344455m is chinitsu");

    patterns_free(&patterns);
    hand_free(h);

    //ryuuiisou
    h = hand_from_string("222333444666s66z");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[vec_len(patterns) - 1];
    test(ryuuiisou(pat) == 13, "222333444666s66z is ryuuiisou");

    patterns_free(&patterns);
    hand_free(h);

    //churen_poutou
    h = hand_from_string("11123456789991m");
    patterns = hand_patterns(h);
    assert(vec_len(patterns) >= 1);

    pat = patterns[vec_len(patterns) - 1];
    test(churen_poutou(pat) == 13, "11123456789991m is churen_poutou");

    patterns_free(&patterns);
    hand_free(h);

    return 0;
}
