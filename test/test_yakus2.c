#include "../model/hand.h"
#include "../model/yaku.h"
#include "../model/patterns.h"
#include "../utils/error.h"

void free_patterns(vec(Pattern *) patterns) {
    // for (u64 i = 0; i < vec_len(patterns); i++) {
    //     pattern_free(patterns[i]);
    // }
    vec_free(patterns);
}

int main() {
    purple();
    printf("[TEST Yakus 2]\n");
    reset();

    //lipeikou
    Hand *h = hand_from_string("789678m111222p33s");
    vec(Pattern *) patterns = hand_patterns(h);

    test(vec_len(patterns) >= 1, "Almost one pattern from 789678m111222p33s");
    Pattern *pat = patterns[vec_len(patterns) - 1];
    test(lipeikou(pat) == 0, "789789m111222p33s is not lipeikou");

    free_patterns(patterns);
    hand_free(h);

    //ryanpeikou
    h = hand_from_string("789789m123234p33s");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(ryanpeikou(pat) == 0, "789789m123234p33s is not ryanpeikou");

    free_patterns(patterns);
    hand_free(h);

    //pinfu
    // TODO

    //shanshoku_doujun
    h = hand_from_string("123m123p23455566s");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(shanshoku_doujun(pat) == 0, "123m123p23455566s is not shanshoku_doujun");

    free_patterns(patterns);
    hand_free(h);

    //ittsuu
    h = hand_from_string("123456678m111p99s");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(ittsuu(pat) == 0, "123456678m111p99s is not ittsuu");

    free_patterns(patterns);
    hand_free(h);

    //tanyao
    h = hand_from_string("111456777m222p88s");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(tanyao(pat) == 0, "111456777m222p88s is not tanyao");

    free_patterns(patterns);
    hand_free(h);

    //yakuhai
    // TODO

    //shousangen
    h = hand_from_string("111m222p555678s77z");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(shousangen(pat) == 0, "111m222p555678s77z is not shousangen");

    free_patterns(patterns);
    hand_free(h);

    //daisangen
    h = hand_from_string("111m22p555s666z777z");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(daisangen(pat) == 0, "111m222p555s666z77z is not daisangen");

    free_patterns(patterns);
    hand_free(h);

    //shousuushi
    h = hand_from_string("111m111z222z333s44z");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(shousuushi(pat) == 0, "111m111z222z333s44z is not shousuushi");

    free_patterns(patterns);
    hand_free(h);

    //daisuushi
    h = hand_from_string("11m111s222z333z444z");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(daisuushi(pat) == 0, "11m111s222z333z444z is not daisuushi");

    free_patterns(patterns);
    hand_free(h);

    //chanta
    h = hand_from_string("123678m111p11z777z");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(chanta(pat) == 0, "123678m111p11z777z is not chanta");

    free_patterns(patterns);
    hand_free(h);

    //junchan
    h = hand_from_string("123789m111p789s11z");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(junchan(pat) == 0, "123789m111p789s11z is not junchan");

    free_patterns(patterns);
    hand_free(h);

    //honroutou
    h = hand_from_string("111999m111p888s11z");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(honroutou(pat) == 0, "111999m111p888s11z is not honroutou");

    free_patterns(patterns);
    hand_free(h);

    //chinroutou
    h = hand_from_string("123999m111p22999s");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(chinroutou(pat) == 0, "123999m111p22999s is not chinroutou");

    free_patterns(patterns);
    hand_free(h);

    //tsuuiisou
    h = hand_from_string("123456777m111p22s");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(tsuuiisou(pat) == 0, "123456777m111p22s is not tsuuiisou");

    free_patterns(patterns);
    hand_free(h);

    //kokuushi_musou
    // TODO

    //chiitoitsu
    // TODO

    //toitoi
    h = hand_from_string("123456777m111p22s");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(toitoi(pat) == 0, "123456777m111p22s is not toitoi");

    free_patterns(patterns);
    hand_free(h);

    //sanankou
    h = hand_from_string("123m123333555s55z");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(sanankou(pat) == 0, "123m123333555s55z is not sanankou");

    free_patterns(patterns);
    hand_free(h);

    //suuankou
    h = hand_from_string("111222888123s55z");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(suuankou(pat) == 0, "111222888123s55z is not suuankou");

    free_patterns(patterns);
    hand_free(h);

    //sanshoku_doukou
    h = hand_from_string("111m111p22223455s");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(sanshoku_doukou(pat) == 0, "111m111p22223455s is not sanshoku_doukou");

    free_patterns(patterns);
    hand_free(h);

    //sankatsu
    // TODO

    //suukantsu
    // TODO

    //honitsu
    h = hand_from_string("111222m333p444s11z");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(honitsu(pat) == 0, "111222m333p444s11z is not honitsu");

    free_patterns(patterns);
    hand_free(h);

    //chinitsu
    h = hand_from_string("111222m333p44455s");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(chinitsu(pat) == 0, "111222m333p44455s is not chinitsu");

    free_patterns(patterns);
    hand_free(h);

    //ryuuiisou
    h = hand_from_string("222333444666s77z");
    patterns = hand_patterns(h);

    pat = patterns[vec_len(patterns) - 1];
    test(ryuuiisou(pat) == 0, "222333444666s77z is not ryuuiisou");

    free_patterns(patterns);
    hand_free(h);

    //churen_poutou
    // TODO

    return 0;
}
