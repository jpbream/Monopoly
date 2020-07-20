#pragma once

//functions and variables related to the game in general
namespace Monopoly {

	//total amount of cash that comes in the box
	constexpr int CASH_IN_BOX = 20580;

	//amount of cash each player starts with
	constexpr int START_CASH = 1500;

	//max number of players that can play the game
	constexpr int MAX_PLAYERS = 6;

	//min number of players that can play the game
	constexpr int MIN_PLAYERS = 1;

	//number of houses that come in the box
	constexpr int NUM_HOUSES = 32;
	//number of hotels that come in the box
	constexpr int NUM_HOTELS = 12;

	//whether tax and other payments should go to free parking
	extern bool free_parking_pot;

	//whether the bots should roll using rng
	extern bool bots_auto_roll;

	//the number of turns that have passed
	extern int turn_count;

	//initializes the game state
	void Init();

	//deallocates resources used by the game
	void Quit();

	//executes the next turn
	void RunTurn();

	//attempts to end the game by evaluating the win condition. returns true if the game was ended
	bool ResolveGame();

	//prompts the user to input their game rules
	void InputSettings();

	//indicates that a simulation is currently running. makes a backup and locks the console.
	void StartSimulation();

	//indicates that a simulation is not running. restores backup and unlocks the console
	void EndSimulation();

	//returns whether a simulation is currently running
	bool InSimulation();

}
