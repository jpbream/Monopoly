#pragma once
#include "Player.h"

//the functions that action spaces point to
// are called by the action spaces LandOn override
namespace Actions {

	//number of doubles needed to roll in a row to get thrown in jail
	constexpr int JAIL_DOUBLES = 3;

	//amount to pay to get yourself out of jail
	constexpr int JAIL_BAIL = 50;

	//max number of turns you can spend in jail
	constexpr int MAX_TURNS_JAIL = 3;

	//amount recieved when passing go
	constexpr int PASS_GO_PAY = 200;

	//amount to pay on the income tax square
	constexpr int INCOME_TAX = 200;

	//amount to pay on the luxury tax square
	constexpr int LUXURY_TAX = 100;

	//automatically called if the player passes go but does not land on it
	// called by the go square if the player lands on go
	void PassGo(Player* const player);

	//prompts to enter a chance card and performs that action on the player
	void Chance(Player* const player);

	//prompts to enter a community chest card and performs that action on the player
	void CommunityChest(Player* const player);

	//makes the player pay the income tax to either free parking or the bank
	// calls the cardactions pay method
	void IncomeTax(Player* const player);

	//makes the player pay the luxury tax to either free parking or the bank
	// calls the cardactions pay method
	void LuxuryTax(Player* const player);

	//if the free parking gamerule is enabled, pays the money in free parking to the player
	void FreeParking(Player* const player);

	//if the player is actually in jail, has them roll the dice to try to get doubles
	// otherwise prompts that they are just visiting
	void Jail(Player* const player);

	//calls cardactions go to jail on the player
	// sets players state to be in jail and moves them to the jail space
	void GoToJail(Player* const player);

}
