#pragma once
#include <string>
#include "Backup.h"

class Player;

//holds a dummy player Attendant to hold any money that comes here.
class FreeParking {

	friend class Player;
	friend void Backup::RestoreBackup();

private:

	static const std::string NAME;

	//amount of money in the pot
	static int money;

	FreeParking() = delete;
	~FreeParking() = delete;


public:
	//make a payment to a player
	static void Payout(Player* const player);

	//returns the amount of money in the pot
	static int AmountMoney();

};
