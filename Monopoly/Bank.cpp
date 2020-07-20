#include "Monopoly.h"
#include "Bank.h"
#include "Player.h"
#include "Console.h"

const std::string Bank::NAME = "BANK";
int Bank::money = Monopoly::CASH_IN_BOX;

void Bank::PayPlayer(Player* const player, int amount) {
	
	//if for whatever reason the bank runs out of money, printing this on debug because it shouldn't happen
	if (amount > money) {
		std::cout << "The bank ran out of money! Find some way to give the bank $" << (amount - money) <<
			"so it can complete the payment" << std::endl;
		std::cin.get();
		money = amount;
	}

	Console::Write(NAME + " pays " + player->GetDisplayName() + " $" + itos(amount) + "\n");

	//give the player the money
	player->money += amount;

	//remove the money from bank
	money -= amount;
}

int Bank::AmountMoney() {
	return money;
}