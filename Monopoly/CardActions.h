#pragma once
#include "Player.h"

//the set of actions that are used by community chest or chance cards
// called from the chance and community chest action spaces
namespace CardActions {

	//the multiple of the rent you will pay if you are sent to nearest railroad
	constexpr int RAILROAD_MULTIPLIER = 2;

	//the multiple of the dice you will pay if you are sent to a utility
	constexpr int UTILITY_MULTIPLIER = 10;

	//player is instructed to move to the nearest railroad and pay some multiple
	// of its current rent
	void NextRailroad(Player* player);

	//player is instructed to move to the nearest utility and pay some multiple
	// of its current rent
	void NextUtility(Player* player);

	//player is insructed to pay money (not to other players). if the free parking rule
	// is enabled, this goes to free parking. otherwise it goes to the bank
	void Pay(Player* player, int amount);

	//player is instructed to pay each other player some amount
	void PayEachPlayer(Player* player, int amount);

	//each other player is to pay this player some amount
	void CollectFromEachPlayer(Player* player, int amount);

	//the bank is to pay this player some amount
	void CollectFromBank(Player* player, int amount);

	//the player must go back some number of spaces
	void GoBack(Player* player, int numSpaces);

	//the player advances to the named space. returns if the move was successful.
	// will be unsucessful if they typed an invalid space name
	bool AdvanceTo(Player* player, std::string& spaceName);

	//the player recieves a get out of jail free card
	void GetOutOfJailFree(Player* player);

	//player pays a sum determined by the number of buildings they own. payment
	// is made using the pay function
	void PayForEachBuilding(Player* player, int perHouse, int perHotel);

	//sets players state to be in jail and moves them to the jail space
	void GoToJail(Player* player);


}
