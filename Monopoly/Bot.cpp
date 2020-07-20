#include "Bot.h"
#include "Monopoly.h"
#include "Property.h"
#include "Board.h"
#include "Actions.h"
#include "Console.h"
#include "Random.h"

Bot::Bot() : Player() {}
Bot::Bot(const Bot& other) : Player(other) {}
Bot& Bot::operator=(const Bot& other)
{
	Player::operator=(other);
	return *this;
}

Bot::Bot(const std::string& name, const std::string& gamepiece) : Player(name, gamepiece)
{
	//bots risk stat is randomly generated
	risk = Random::Integer(MIN_RISK, MAX_RISK + 1);
}

Roll Bot::DiceRoll() {

	if (Monopoly::InSimulation()) {
		
		//if in a simulation, dice are automatically rolled
		return Dice::Toss();
		std::cout << "simulation toss" << std::endl;

	}
	else {

		//if the bots should roll using rng
		if (Monopoly::bots_auto_roll) {

			Roll roll = Dice::Toss();

			Console::Write(NAME + " rolls (" + itos(roll.die1) + " " + itos(roll.die2) + ")\n");
			
			return roll;

		}
		else {

			//a person rolls dice in real life and types their values
			Console::Write("Roll the dice for " + NAME + " and enter their values: ");

			int d1, d2;
			Console::Get<int>(2, &d1, &d2);

			return Roll(d1, d2);

		}
	}
}

Executable* Bot::QueryImplementation(Executable* decision1, Executable* decision2) {

	//net worth if decision 1 is chosen
	int netWorth1 = 0;

	//net worth if decision 2 is chosen
	int netWorth2 = 0;

	//number of times to run the simulation
	int numGames = 1000;

	//number of turns into the future to run the simulations
	int turnsAhead = 25;

	netWorth1 = SimulateTurns(numGames, turnsAhead, decision1);
	netWorth2 = SimulateTurns(numGames, turnsAhead, decision2);

	if ( netWorth2 > netWorth1 && (netWorth2 - netWorth1) / (money + 1) < risk / 4 ) {
		return decision1;
	}
	else {
		return decision2;
	}
	
	Console::IncreaseIndent();
	Console::Write(NAME + " predicts an average net worth of $" + itos(netWorth1) + " if it chooses option 1.\n");
	Console::Write(NAME + " predicts an average net worth of $" + itos(netWorth2) + " if it chooses option 2.\n");
	Console::DecreaseIndent();

	if ( netWorth1 > netWorth2 ) {
		return decision1;
	}
	else {
		return decision2;
	}

}


//simulates turnsAhead turns numGames times. runs the decision Action
// on the bot in each simulation. returns bots average net worth at end of simulations.
int Bot::SimulateTurns(int numGames, int turnsAhead, Executable* decision) {

	//run once to make sure the decision doesn't immediatly bankrupt the bot
	try {
		Monopoly::StartSimulation();
		decision->PerformAction();
	}
	catch (Player* player) {
		Monopoly::EndSimulation();
		return 0;
	}
	Monopoly::EndSimulation();

	//used to calculate the average in the end
	int totalNetWorth = 0;

	//do this many times to get a good average
	for (int i = 0; i < numGames; ++i) {

		Monopoly::StartSimulation();
		decision->PerformAction();

		//run the desired amount of turns ahead
		for (int j = 0; j < turnsAhead; ++j) {
			Monopoly::RunTurn();
		}

		totalNetWorth += CalculateNetWorth();
		Monopoly::EndSimulation();
	}

	//return the average simulated net worth
	return totalNetWorth / numGames;

}

int Bot::ScroungeCashImplementation(int requiredAmount)
{
	return 0;
}