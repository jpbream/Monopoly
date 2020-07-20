#include "FreeParking.h"
#include "Player.h"
#include "Console.h"
#include "Monopoly.h"

const std::string FreeParking::NAME = "FREE PARKING";
int FreeParking::money = 0;

void FreeParking::Payout(Player* const player) {

	//double check that the free parking gamerule is enabled
	if (!Monopoly::free_parking_pot) {
		std::cout << "You called payout on free parking when it is disabled" << std::endl;
	}

	//if there is money in the free parking
	if (money > 0) {
	
		Console::Write(NAME + " pays " + player->GetDisplayName() + "$" + itos(money) + "\n");
		
		player->money += money;
		money = 0;

	}
	else {
		Console::Write("There is no money in " + NAME + "\n");
	}
}

int FreeParking::AmountMoney() {
	return money;
}