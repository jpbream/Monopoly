#pragma once
#include "Railroad.h"

#define NUM_RAILROADS 4

class Player;

//items related to the group of railroads
namespace Railroads {

	extern int Rent_1;
	extern int Rent_2;
	extern int Rent_3;
	extern int Rent_4;

	//the list of railroad properties
	extern Railroad** Railroads;

	//returns the number of railroads owned by p
	int NumOwnedBy(const Player* const p);

	void Quit();
}
