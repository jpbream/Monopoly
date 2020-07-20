#pragma once
#include <string>
#include "Backup.h"

//holds a player instance that acts as the teller. if a payment is to be made by the teller,
// the PayPlayer function should be used, do not call MakePayment on the teller

class Player;

class Bank {

	friend class Player;
	friend void Backup::RestoreBackup();

private:

	//amount of money in the bank
	static int money;

	Bank() = delete;
	~Bank() = delete;

public:

	//the banks display name
	static const std::string NAME;

	//make a payment to a player
	static void PayPlayer(Player* const player, int amount);

	//returns the amount of money in the bank
	static int AmountMoney();

};
