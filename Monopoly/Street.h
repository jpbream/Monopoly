#pragma once
#include "Property.h"
#include "StreetGroup.h"

// the max number of buildings that can be on a street
#define MAX_BUILDING 5

// max number of houses that can be on a street
#define MAX_HOUSE 4

// max number of hotels that can be on a street
#define MAX_HOTEL 1

class StreetGroup;

//a type of property
class Street : public Property
{

private:
	int numBuilding = 0;

	//struct that holds the other streets the same color as this street, and the price to build houses and hotels on these streets
	const StreetGroup* neighborhood;

protected:

	//action to take when a player lands on this space and it is owned by another player
	void LandOnOwned(Player* const p) override;

public:

	//fee for landing on this property
	const int RENT;

	//fee for landing on this property if all streets in 'neighborhood' are owned by the same player
	const int RENT_FULL_STREET;

	//fee if this street has one house
	const int RENT_1HOUSE;

	//fee if this street has two houses
	const int RENT_2HOUSE;

	//fee if this street has three houses
	const int RENT_3HOUSE;

	//fee if this street has four houses
	const int RENT_4HOUSE;

	//fee if this street has a hotel
	const int RENT_HOTEL;

	// returns 0 or 1, the number of hotels on the street
	int NumHotels() const;

	// returns 0 to 4, the number of houses on the street
	int NumHouses() const;

	// returns the number of buildings on the street. a hotel counts as one
	// building plus the number of houses needed to form a hotel
	int NumBuildings() const;

	// attempts to add a house to this street. If adding was successful, it will return true.
	// if false is returned, that means adding a house here would cause a neighborhood house imbalance,
	// or because the street already had 4 houses
	bool AddHouse();

	// attempts to remove a house from this street. If removing was successful, it will return true.
	// if false is returned, that means removing a house here would cause a neighborhood house imbalance,
	// or because there are no houses on this street, or because there is only a hotel on this street
	bool RemoveHouse();

	// attempts to add a hotel to this street. If adding was successful, it will return true.
	// if false is returned, that means adding a hotel would cause a neighborhood house imbalance,
	// or because there is already a hotel on this street, or because there is not 4 houses on this street
	bool AddHotel();

	// attempts to remove a hotel from this street. If removing was successful, it will return true.
	// if false is returned, that means there is not a hotel on this street
	bool RemoveHotel();

	// returns the street group this street belongs to
	const StreetGroup* GetNeighborhood() const;

	Street();
	Street(const Street& other);
	Street& operator=(const Street& other);

	Street(int index, const std::string& name, const StreetGroup* const neighborhood, int price, int rent, int rent_full_street,
			int rent_1house, int rent_2house, int rent_3house, int rent_4house, int rent_hotel, int mortgage);
	
};

