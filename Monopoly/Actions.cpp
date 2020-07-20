#include "Actions.h"
#include "Bank.h"
#include "Board.h"
#include "CardActions.h"
#include "FreeParking.h"
#include "Monopoly.h"
#include "Console.h"
#include "Random.h"

// when a chance card or community chest is needed during a simluation, values are randomly selected from
// the arrays below
static constexpr int NUM_PAY_EACH_PLAYER = 1;
static const int PAY_EACH_PLAYER[NUM_PAY_EACH_PLAYER] = { 50 };

static constexpr int NUM_COLLECT_EACH_PLAYER = 1;
static const int COLLECT_EACH_PLAYER[NUM_COLLECT_EACH_PLAYER] = { 10 };

static constexpr int NUM_PAY = 4;
static const int PAY[NUM_PAY] = { 15, 50, 50, 100 };

static constexpr int NUM_PAY_EACH_PROPERTY = 2;
static const int PAY_EACH_HOUSE[NUM_PAY_EACH_PROPERTY] = {25, 40};
static const int PAY_EACH_HOTEL[NUM_PAY_EACH_PROPERTY] = { 100, 115 };

static constexpr int NUM_COLLECT = 9;
static const int COLLECT[NUM_COLLECT] = {10, 20, 25, 50, 100, 100, 100, 150, 200};

static constexpr int NUM_MOVE_TO = 6;
static const std::string MOVE_TO[NUM_MOVE_TO] = {"GO", "ST. CHARLES PLACE", "READING RAILROAD", "BOARDWALK", "ILLINOIS AVENUE", "GO"};

static constexpr int NUM_GO_BACK = 1;
static const int GO_BACK[NUM_GO_BACK] = { 3 };

void Actions::PassGo(Player* player) {

	//do not call Bank::Teller->Pay?!
	Bank::PayPlayer(player, PASS_GO_PAY);

}

void Actions::Chance(Player* const player) {

	Console::Write("Draw a Chance card and enter the number of its action: \n");

	Console::Write("    Get Out of Jail Free ... 1\n");
	Console::Write("    Go Directly to Jail .... 2\n");
	Console::Write("    Pay Each Player ........ 3\n");
	Console::Write("    Pay For Each Building .. 4\n");
	Console::Write("    Pay .................... 5\n");
	Console::Write("    Advance To ............. 6\n");
	Console::Write("    Advance To Next Railroad 7\n");
	Console::Write("    Advance To Next Utility  8\n");
	Console::Write("    Collect Money .......... 9\n");
	Console::Write("    Go Back ................ 10\n");
	Console::Write(" Enter the number: ");

	int number;
	if (Monopoly::InSimulation()) {
		number = Random::Integer(1, 11);
	}
	else {
		Console::Get<int>(1, &number);
	}

	if (number == 1) {

		CardActions::GetOutOfJailFree(player);
		
	}
	else if (number == 2) {

		CardActions::GoToJail(player);

	}
	else if (number == 3) {

		int amountPerPlayer;
		Console::Write("    How much is to be payed to each player? ");

		if (Monopoly::InSimulation()) {
			amountPerPlayer = PAY_EACH_PLAYER[Random::Integer(0, NUM_PAY_EACH_PLAYER)];
		}
		else {
			Console::Get<int>(1, &amountPerPlayer);
		}

		CardActions::PayEachPlayer(player, amountPerPlayer);

	}
	else if (number == 4) {

		int perHouse, perHotel;
		int rnd = Random::Integer(0, NUM_PAY_EACH_PROPERTY);

		Console::Write("    Enter the amount to pay for each house: ");
		if (Monopoly::InSimulation()) {
			perHouse = PAY_EACH_HOUSE[rnd];
		}
		else {
			Console::Get<int>(1, &perHouse);
		}

		Console::Write("    Enter the amount to pay for each hotel: ");
		if (Monopoly::InSimulation()) {
			perHotel = PAY_EACH_HOTEL[rnd];
		}
		else {
			Console::Get<int>(1, &perHotel);
		}

		CardActions::PayForEachBuilding(player, perHouse, perHotel);
		

	}
	else if (number == 5) {

		int amount;
		Console::Write("    Enter the amount to pay: ");
		
		if (Monopoly::InSimulation()) {
			amount = PAY[Random::Integer(0, NUM_PAY)];
		}
		else {
			Console::Get<int>(1, &amount);
		}

		CardActions::Pay(player, amount);

	}
	else if (number == 6) {

		Console::Write("    Enter the name of the space to move to in all caps: ");

		std::string targetSpace;
		
		if (Monopoly::InSimulation()) {
			targetSpace = MOVE_TO[Random::Integer(0, NUM_MOVE_TO)];
			CardActions::AdvanceTo(player, targetSpace);
		}
		else {

			//loop until they type a valid space name
			do {
				Console::Get<std::string>(1, &targetSpace);
			}
			while (!CardActions::AdvanceTo(player, targetSpace));
		}

		
		
	}
	else if (number == 7) {

		CardActions::NextRailroad(player);

	}
	else if (number == 8) {

		CardActions::NextUtility(player);

	}
	else if (number == 9) {

		int amount;
		Console::Write("    Enter the amount to collect from the bank: ");
		
		if (Monopoly::InSimulation()) {
			amount = COLLECT[Random::Integer(0, NUM_COLLECT)];
		}
		else {
			Console::Get<int>(1, &amount);
		}

		CardActions::CollectFromBank(player, amount);

	}
	else if (number == 10) {

		int numSpaces;
		Console::Write("    Enter the number of spaces to move back: ");
		
		if (Monopoly::InSimulation()) {
			numSpaces = GO_BACK[Random::Integer(0, NUM_GO_BACK)];
		}
		else {
			Console::Get<int>(1, &numSpaces);
		}

		CardActions::GoBack(player, numSpaces);

	}

}

void Actions::CommunityChest(Player* const player) {
	
	Console::Write("Draw a Community Chest card and enter the number of its action: \n");

	Console::Write("    Get Out of Jail Free ... 1\n");
	Console::Write("    Go Directly to Jail .... 2\n");
	Console::Write("    Pay For Each Building .. 3\n");
	Console::Write("    Pay .................... 4\n");
	Console::Write("    Advance To ............. 5\n");
	Console::Write("    Collect Money .......... 6\n");
	Console::Write("    Collect From Each Player 7\n");
	Console::Write(" Enter the number: ");

	int number;
	if (Monopoly::InSimulation()) {
		number = Random::Integer(1, 11);
	}
	else {
		Console::Get<int>(1, &number);
	}

	if (number == 1) {

		CardActions::GetOutOfJailFree(player);

	}
	else if (number == 2) {

		CardActions::GoToJail(player);

	}
	else if (number == 3) {

		int perHouse, perHotel;
		int rnd = Random::Integer(0, NUM_PAY_EACH_PROPERTY);

		Console::Write("    Enter the amount to pay for each house: ");
		if (Monopoly::InSimulation()) {
			perHouse = PAY_EACH_HOUSE[rnd];
		}
		else {
			Console::Get<int>(1, &perHouse);
		}

		Console::Write("    Enter the amount to pay for each hotel: ");
		if (Monopoly::InSimulation()) {
			perHotel = PAY_EACH_HOTEL[rnd];
		}
		else {
			Console::Get<int>(1, &perHotel);
		}

		CardActions::PayForEachBuilding(player, perHouse, perHotel);

	}
	else if (number == 4) {

		int amount;
		Console::Write("    Enter the amount to pay: ");

		if (Monopoly::InSimulation()) {
			amount = PAY[Random::Integer(0, NUM_PAY)];
		}
		else {
			Console::Get<int>(1, &amount);
		}

		CardActions::Pay(player, amount);

	}
	else if (number == 5) {

		Console::Write("    Enter the name of the space to move to in all caps: ");

		std::string targetSpace;

		if (Monopoly::InSimulation()) {
			targetSpace = MOVE_TO[Random::Integer(0, NUM_MOVE_TO)];
		}
		else {
			Console::Get<std::string>(1, &targetSpace);
		}

		CardActions::AdvanceTo(player, targetSpace);

	}
	else if (number == 6) {

		int amount;
		Console::Write("    Enter the amount to collect from the bank: ");

		if (Monopoly::InSimulation()) {
			amount = COLLECT[Random::Integer(0, NUM_COLLECT)];
		}
		else {
			Console::Get<int>(1, &amount);
		}

		CardActions::CollectFromBank(player, amount);

	}
	else if (number == 7) {

		int amountPerPlayer;
		Console::Write("    Enter the amount to collect from each player: ");

		if (Monopoly::InSimulation()) {
			amountPerPlayer = COLLECT_EACH_PLAYER[Random::Integer(0, NUM_COLLECT_EACH_PLAYER)];
		}
		else {
			Console::Get<int>(1, &amountPerPlayer);
		}

		CardActions::CollectFromEachPlayer(player, amountPerPlayer);

	}

}

void Actions::IncomeTax(Player* const player) {
	CardActions::Pay(player, INCOME_TAX);
}

void Actions::LuxuryTax(Player* const player) {
	CardActions::Pay(player, LUXURY_TAX);
}

void Actions::FreeParking(Player* const player) {

	if (Monopoly::free_parking_pot) {
		FreeParking::Payout(player);
	}
}

void Actions::Jail(Player* const player) {

	//if the player is jailed
	if (player->IsInJail()) {

		//player doesnt get to do anything if they just got put in jail
		if (player->TurnsInJail() > 0) {

			Console::Write(player->GetDisplayName() + " will try to roll doubles to get out of jail.\n");

			//try to roll doubles
			Roll roll = player->DiceRoll();

			//the player spending the max turns in jail is handled by the
			// player->QueryBailOut method

			if (roll.doubles) {

				Console::Write(player->GetDisplayName() + " has rolled doubles and is free from jail.\n");
				player->ReleaseFromJail();

				//they get to move by the doubles they just rolled
				player->Advance(roll.total);

			}
			else {

				//they stay in jail
				Console::Write(player->GetDisplayName() + " has failed to roll doubles and remains in jail.\n");

			}
		}

	}
	else {
		//otherwise they are just visiting
		Console::Write(player->GetDisplayName() + " is just visiting jail.\n");
	}

}

void Actions::GoToJail(Player* const player) {
	CardActions::GoToJail(player);
}