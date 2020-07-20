#pragma once
#include <string>
#include "Board.h"

class Street;
class Player;

//a grouping of streets of a certain color
class StreetGroup
{

	// so that board init can populate the array of streets
	friend void Board::Init();

private:

	//list of street properties
	Street** streets;

public:

	//the color of this street group
	const std::string COLOR;

	//the number of street spaces in this street group
	const int NUM_STREETS;

	const int HOUSE_COST;
	const int HOTEL_COST;

	StreetGroup(std::string color, int numStreets, int houseCost, int hotelCost);
	~StreetGroup();

	//if a single player owns this entire street group, returns that player. otherwise returns nullptr
	Player* QueryOwner() const;

	// returns true if there is a house imbalance on this street. the number of houses on each street
	// can differ by at most 1
	bool CheckForHouseImbalance() const;
};

