#include "CardActions.h"
#include "Board.h"
#include "Bank.h"
#include "FreeParking.h"
#include "Players.h"
#include "Railroads.h"
#include "Utilities.h"
#include "Monopoly.h"
#include "Street.h"
#include <algorithm>

void CardActions::NextRailroad(Player* player) {

	bool foundNextRailroad = false;

	//index of the square we are comparing to railroad names. start with the sqare in front of us
	int checkingSquare = player->GetCurrentSquare() + 1;

	while (!foundNextRailroad) {

		//name of the square we will check
		const std::string& squareName = Board::Spaces[checkingSquare]->NAME;

		//loop through all railroads
		for (int i = 0; i < NUM_RAILROADS; i++) {

			//if the square we are checking matches a railroad name, we are done
			if (Railroads::Railroads[i]->NAME == squareName) {

				foundNextRailroad = true;
				checkingSquare--;
				break;

			}

		}

		//increment checking square, or wrap it around if we pass go
		checkingSquare++;
		if (checkingSquare == NUM_SPACES) {
			checkingSquare = 0;
		}
	}

	//railroad rent changes when gone to by a card
	Railroads::Rent_1 *= RAILROAD_MULTIPLIER;
	Railroads::Rent_2 *= RAILROAD_MULTIPLIER;
	Railroads::Rent_3 *= RAILROAD_MULTIPLIER;
	Railroads::Rent_4 *= RAILROAD_MULTIPLIER;

	player->MoveTo(checkingSquare, true);

	//put railroad rent back to original values
	Railroads::Rent_1 /= RAILROAD_MULTIPLIER;
	Railroads::Rent_2 /= RAILROAD_MULTIPLIER;
	Railroads::Rent_3 /= RAILROAD_MULTIPLIER;
	Railroads::Rent_4 /= RAILROAD_MULTIPLIER;

}

void CardActions::NextUtility(Player* player) {

	bool foundNextUtility = false;

	//index of the square we are comparing to the utility names. start 
	// with the square in front of us
	int checkingSquare = player->GetCurrentSquare() + 1;

	while (!foundNextUtility) {

		//name of the square to check
		const std::string& squareName = Board::Spaces[checkingSquare]->NAME;

		//loop through each utility square
		for (int i = 0; i < NUM_UTILITIES; i++) {

			//if the square we are checking matches any of the utility names, we are done
			if (Utilities::Utilities[i]->NAME == squareName) {

				foundNextUtility = true;
				checkingSquare--;
				break;

			}

		}

		//increment checking square, or wrap it around if we pass go
		checkingSquare++;
		if (checkingSquare == NUM_SPACES) {
			checkingSquare = 0;
		}
	}

	//utility prices change when gone to by a card
	int oldSingleUtility = Utilities::Single_Multiplier;
	Utilities::Single_Multiplier = Utilities::Double_Multiplier;

	player->MoveTo(checkingSquare, true);

	//put old value back
	Utilities::Single_Multiplier = oldSingleUtility;

}

void CardActions::Pay(Player* player, int amount) {

	if (Monopoly::free_parking_pot) {

		player->PayFreeParking(amount);

	}
	else {
		player->PayBank(amount);
	}

}

void CardActions::PayEachPlayer(Player* player, int amount) {

	//loop through each player
	for (int i = 0; i < Players::NumPlayers; i++) {

		//pay all OTHER players the amount
		if (Players::Players[i] != player) {

			player->PayPlayer(Players::Players[i], amount);

		}
	}
}

void CardActions::CollectFromEachPlayer(Player* player, int amount) {

	//loop through each player
	for (int i = 0; i < Players::NumPlayers; i++) {

		//all OTHER players pay this player
		if (Players::Players[i] != player) {
			Players::Players[i]->PayPlayer(player, amount);
		}
	}

}

void CardActions::CollectFromBank(Player* player, int amount) {
	
	Bank::PayPlayer(player, amount);

}

void CardActions::GoBack(Player* player, int numSpaces) {
	
	//same as moving around the board totalspaces - numspaces spaces

	int spacesToAdvance = NUM_SPACES - numSpaces;

	int newSquare = (player->GetCurrentSquare() + spacesToAdvance) % NUM_SPACES;

	//signal to not collect pass go money
	player->MoveTo(newSquare, false);

}

bool CardActions::AdvanceTo(Player* player, std::string& spaceName) {

	//convert the string to uppercase
	std::transform(spaceName.begin(), spaceName.end(), spaceName.begin(), toupper);

	//check that a valid space name was entered
	if (Board::NameToIndexMap.find(spaceName) != Board::NameToIndexMap.end()) {
		player->MoveTo(Board::NameToIndexMap[spaceName], true);
		return true;
	}
	else {
		return false;
	}

}

void CardActions::GetOutOfJailFree(Player* player) {
	player->GiveGetOutOfJailFree();
}

void CardActions::PayForEachBuilding(Player* player, int perHouse, int perHotel) {
	
	int totalPayment = 0;

	int numProps = player->NumProperties();

	//loop through each property the player owns. these could also include railroads or utilities.
	for (int i = 0; i < numProps; i++) {

		Property* prop = player->GetProperty(i);

		//attempt to cast the property to a street
		Street* street = dynamic_cast<Street*>(prop);

		if (street != nullptr) {

			//this property is indeed a street

			totalPayment += perHouse * street->NumHouses();
			totalPayment += perHotel * street->NumHotels();

		}

	}

	CardActions::Pay(player, totalPayment);

}

void CardActions::GoToJail(Player* player) {

	//changes players state to be in jail
	player->PutInJail();

	//moves player piece to jail, does not collect go money
	player->MoveTo(Board::NameToIndexMap["JAIL"], false);

}