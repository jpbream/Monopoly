#include "Street.h"
#include "Console.h"
#include "Bank.h"
#include "Player.h"

Street::Street() 
	: 
	Property(0, "", 0, 0), neighborhood(nullptr), RENT(0), RENT_FULL_STREET(0),
RENT_1HOUSE(0), RENT_2HOUSE(0), RENT_3HOUSE(0), RENT_4HOUSE(0),
RENT_HOTEL(0)
{
}
Street::Street(const Street& other)
	:
	Property(other), neighborhood(other.neighborhood), RENT(other.RENT), RENT_FULL_STREET(other.RENT_FULL_STREET),
	RENT_1HOUSE(other.RENT_1HOUSE), RENT_2HOUSE(other.RENT_2HOUSE), RENT_3HOUSE(other.RENT_3HOUSE), RENT_4HOUSE(other.RENT_4HOUSE),
	RENT_HOTEL(other.RENT_HOTEL), numBuilding(other.numBuilding)
{
}
Street& Street::operator=(const Street& other)
{
	Property::operator=(other);
	neighborhood = other.neighborhood;
	numBuilding = other.numBuilding;

	*(int*)&RENT = other.RENT;
	*(int*)&RENT_FULL_STREET = other.RENT_FULL_STREET;
	*(int*)&RENT_1HOUSE = other.RENT_1HOUSE;
	*(int*)&RENT_2HOUSE = other.RENT_2HOUSE;
	*(int*)&RENT_3HOUSE = other.RENT_3HOUSE;
	*(int*)&RENT_4HOUSE = other.RENT_4HOUSE;
	*(int*)&RENT_HOTEL = other.RENT_HOTEL;
	return *this;
}

Street::Street(int index, const std::string& name, const StreetGroup* const neighborhood, int price, int rent, int rent_full_street,
	int rent_1house, int rent_2house, int rent_3house, int rent_4house, int rent_hotel, int mortgage)
	:
	Property(index, name, price, mortgage), neighborhood(neighborhood), RENT(rent), RENT_FULL_STREET(rent_full_street),
	RENT_1HOUSE(rent_1house), RENT_2HOUSE(rent_2house), RENT_3HOUSE(rent_3house), RENT_4HOUSE(rent_4house),
	RENT_HOTEL(rent_hotel)
{
}

// returns the street group this street belongs to
const StreetGroup* Street::GetNeighborhood() const
{
	return neighborhood;
}

int Street::NumHouses() const
{
	if ( numBuilding == MAX_BUILDING ) {
		return 0;
	}

	return numBuilding;
}

int Street::NumHotels() const
{
	return numBuilding == MAX_BUILDING ? 1 : 0;
}

int Street::NumBuildings() const
{
	return numBuilding;
}

bool Street::AddHouse()
{
	if ( NumHotels() > 0 )
		return false;
	if ( NumHouses() == MAX_HOUSE )
		return false;

	numBuilding++;
	
	if ( GetNeighborhood()->CheckForHouseImbalance() ) {
		numBuilding--;
		return false;
	}

	return true;
}

bool Street::RemoveHouse()
{
	if ( NumHotels() > 0 )
		return false;
	if ( NumHouses() == 0 )
		return false;

	numBuilding--;

	if ( GetNeighborhood()->CheckForHouseImbalance() ) {
		numBuilding++;
		return false;
	}

	return true;
}

bool Street::AddHotel()
{
	if ( NumHotels() == MAX_HOTEL )
		return false;
	if ( NumHouses() != MAX_HOUSE )
		return false;

	numBuilding++;

	if ( GetNeighborhood()->CheckForHouseImbalance() ) {
		numBuilding--;
		return false;
	}

	return true;
}

bool Street::RemoveHotel()
{
	if ( NumHotels() == 0 )
		return false;

	numBuilding--;

	// i think its impossible for this to happen with hotels but
	// its here just in case
	if ( GetNeighborhood()->CheckForHouseImbalance() ) {
		numBuilding++;
		return false;
	}

	return true;
}

void Street::LandOnOwned(Player* p) {

	//check if p already owns this street, if so do nothing
	if (owner == p) {
		Console::Write(p->GetDisplayName() + " already owns " + NAME + "\n");
		return;
	}

	//check if one person owns all streets in the neighborhood
	bool allSame = (GetNeighborhood()->QueryOwner() != nullptr);

	//determine the appropriate fee
	int fee = 0;
	if (!allSame) {
		fee = RENT;
	}
	else {

		switch (numBuilding) {
		case 0:
			fee = RENT_FULL_STREET;
			break;
		case 1:
			fee = RENT_1HOUSE;
			break;
		case 2:
			fee = RENT_2HOUSE;
			break;
		case 3:
			fee = RENT_3HOUSE;
			break;
		case 4:
			fee = RENT_4HOUSE;
			break;
		case 5:
			fee = RENT_HOTEL;
			break;
		}
	}

	//complete the payment
	p->PayPlayer(owner, fee);

}