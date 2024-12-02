#include "../logic/hand.h"
#include "../logic/tile.h"

int main() {
	printf("In TEST HAND\n");
	Hand* hand = empty_hand();
	hand_add_tile(hand, tile_from_string("1m"));
}
