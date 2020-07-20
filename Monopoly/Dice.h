#pragma once

//represents a dice roll
struct Roll {

	//sum of die 1 and die 2
	int total;

	int die1;
	int die2;

	//if both dice show the same value
	bool doubles;

	Roll(int d1, int d2);

};

//functions representing two dice
namespace Dice {

	//rolls two rng dice and returns their roll
	Roll Toss();

}
