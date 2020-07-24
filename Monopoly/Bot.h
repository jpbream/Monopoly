#pragma once
#include "Player.h"

//a type of player, controlled by the computer
class Bot : public Player
{

private:

	//simulates turnsAhead turns numGames times. runs the decision Action
	// on the bot in each simulation. returns bots average net worth at end of simulations.
	int SimulateTurns(int numGames, int turnsAhead, Executable* decision);

	// asks the bot a yes or no question. bot will simulate games to predict best choice.
	// choice is returned as bool
	Executable* QueryImplementation(Executable* decision1, Executable* decision2) override;

	//bot will liquidate assets in an attempt to come up with amount in cash.
	// returns if the bot was successful
	int ScroungeCashImplementation(int requiredAmount) override;

public:

	// used during backup
	Bot();
	Bot(const Bot& other);
	Bot& operator=(const Bot& other);

	Bot(const std::string& name, const std::string& gamepiece);

	//if the botautoroll gamerule is set, automatically rolls dice. otherwise prompt to enter dice roll values.
	// if a simulation is running, dice are automatically rolled.
	Roll DiceRoll() override;

};

