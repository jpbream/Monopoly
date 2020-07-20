#include "Dice.h"
#include "Random.h"

Roll::Roll(int d1, int d2) : die1(d1), die2(d2), total(d1 + d2), doubles(d1 == d2) {}


namespace Dice {

	Roll Toss() {

		int d1 = Random::Integer(1, 7);
		int d2 = Random::Integer(1, 7);

		return Roll(d1, d2);

	}

}