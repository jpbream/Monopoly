#include "Monopoly.h"
#include "Random.h"
#include "Bank.h"
#include "Board.h"
#include "Players.h"
#include "FreeParking.h"
#include "Actions.h"
#include "Railroads.h"
#include "Utilities.h"
#include "Console.h"
#include "Backup.h"

//number of players that must be left in the game to declare a winner
#define WIN_CONDITION 0

bool Monopoly::free_parking_pot = false;
bool Monopoly::bots_auto_roll = false;

int Monopoly::turn_count = 0;

static bool inSimulation = false;
static Player* simulator = nullptr;

void Monopoly::Init() {

	Console::Write("Initializing the monopoly game... ");
	Random::Init();
	Board::Init();
	Console::Write("Done Initializing\n\n");

}

void Monopoly::InputSettings() {

	Console::Write("Before we begin, lets set up your settings for this game...\n");
	Console::IncreaseIndent();

	//free parking rule
	Console::Write("Do you play with the free parking money pot ? (y/n) ");
	char fp;
	Console::Get<char>(1, &fp);

	free_parking_pot = fp == 'y';

	//should the bots roll using rng
	Console::Write("Should the bots roll dice digitally? (y/n) ");
	char br;
	Console::Get<char>(1, &br);

	bots_auto_roll = br == 'y';

	Console::DecreaseIndent();
	Console::Write("Ok, thats all the settings!\n");
	Console::Write("\n");

}

void Monopoly::RunTurn() {

	Console::Write("STARTING TURN " + itos(++turn_count) + "\n");

	//loop through all players, even if they are bankrupt.
	for (int playerIndex = 0; playerIndex < Players::NumPlayers; playerIndex++) {

		Player* currentPlayer = Players::Players[playerIndex];

		//filter out bankrupt players
		if (!currentPlayer->InGame())
			continue;

		Console::Write(currentPlayer->GetDisplayName() + " is up! Cash: $" + itos(currentPlayer->AmountMoney()) + "   Net Worth: $" + itos(currentPlayer->CalculateNetWorth()) + "\n");
		Console::IncreaseIndent();

		//try to run the players turn. An exception will be thrown if they go bankrupt
		try {
			
			if (turn_count == 5)
				Players::Players[0]->PayBank(1600);

			//if the current player is in jail, ask them if they want to bail out
			if (currentPlayer->IsInJail()) {

				Console::Write(currentPlayer->GetDisplayName() + " is in jail and cannot roll to move.\n");

				//if player has spent max turns in jail, releases them. otherwise asks them if they want to bail out or use 
				// get out of jail free card
				currentPlayer->RunBailOutRoutine();
			}

			//no one in jail gets to roll (for the purposes of moving their piece)
			if (!currentPlayer->IsInJail()) {

				currentPlayer->RunRollAndMoveRoutine();
			}
			else {

				//if they are in jail they will roll the dice and get out if they roll doubles
				currentPlayer->RunInJailRoutine();
			}

		}
		catch (Player* player) {
			//any player pointer exception will be thrown because that player went bankrupt

			//remove the player from the game
			Console::Write(player->GetDisplayName() + " is bankrupt and is out of the game.\n");
			player->RemoveFromGame();

		}

		Console::DecreaseIndent();
		Console::Write("End of " + currentPlayer->GetDisplayName() + "s turn. Cash: $" + itos(currentPlayer->AmountMoney()) + "   Net Worth: $" + itos(currentPlayer->CalculateNetWorth()) + "\n");
		if (playerIndex != Players::NumPlayers - 1) {
			Console::Pause();
		}

	}

	Console::Write("END OF TURN " + itos(turn_count) + "\n");
	Console::Pause();

}

bool Monopoly::ResolveGame() {

	//the number of players still in the game
	int playersInGame = 0;

	//index of player still in the game
	int playerIndex = -1;

	//find the number of players still in the game, playerIndex will store index of last
	for (int i = 0; i < Players::NumPlayers; i++) {
		if (Players::Players[i]->InGame()) {
			playersInGame++;
			playerIndex = i;
		}
	}

	//if there is only one player left in the game, end the game and display his stats
	if (playersInGame == WIN_CONDITION) {

		if (playerIndex >= 0) {
			Console::Write(Players::Players[playerIndex]->GetDisplayName() + " has won the game with a net worth of $" +
				itos(Players::Players[playerIndex]->CalculateNetWorth()) + "\n");
		}
		return true;

	}
	return false;
}

void Monopoly::StartSimulation(Player* p) {

	if (!inSimulation) {
		inSimulation = true;
		simulator = p;

		Backup::MakeBackup();
		Console::Lock();
	}

}

Player* Monopoly::GetSimulator()
{
	return simulator;
}

void Monopoly::EndSimulation() {

	if (inSimulation) {
		inSimulation = false;
		Backup::RestoreBackup();
		Console::Unlock();
	}

}

bool Monopoly::InSimulation() {
	return inSimulation;
}

void Monopoly::Quit() {

	Players::Quit();
	Board::Quit();
	Railroads::Quit();
	Utilities::Quit();

}