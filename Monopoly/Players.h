#pragma once
#include "Player.h"
#include <vector>

//holds info regarding all the players currently playing (no dummy players)
namespace Players {

	//the number of players in the game
	extern int NumPlayers;

	//pointer to the players
	extern Player** Players;

	//prompt user to enter player information
	void InputPlayers();

	//if a bill transfer is uncomputable, this is called, and the user will have to 
	// manually carry out the transaction and enter all new wallet bill counts
	void ManualWalletReset();

	//deallocates the player objects
	void Quit();

}
