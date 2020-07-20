#pragma once
#include "Utility.h"

#define NUM_UTILITIES 2

class Player;

//items related to the set of utilities
namespace Utilities {

	//list of the utility spaces
	extern Utility** Utilities;

	//multiple of dice roll if player owns one utility
	extern int Single_Multiplier;

	//multiple of dice roll if player owns both utilities
	extern int Double_Multiplier;

	//returns the number of utilities owned by p
	int NumOwnedBy(const Player* const p);

	void Quit();

}
