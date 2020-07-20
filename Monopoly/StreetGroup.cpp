#include "StreetGroup.h"
#include "Street.h"

StreetGroup::StreetGroup(std::string color, int numStreets, int houseCost, int hotelCost) 
	: COLOR(color), NUM_STREETS(numStreets), HOUSE_COST(houseCost), HOTEL_COST(hotelCost)
{
	streets = new Street*[numStreets];

}

Player* StreetGroup::QueryOwner() const {

	bool allEqual = true;
	Player* owner = streets[0]->GetOwner();

	for (int i = 1; i < NUM_STREETS; i++) {
		if (streets[i]->GetOwner() != owner) {
			allEqual = false;
		}
	}

	if (allEqual) {
		return owner;
	}
	else {
		return nullptr;
	}

}

bool StreetGroup::CheckForHouseImbalance() const
{
	int min = MAX_BUILDING;
	int max = 0;

	// find the min and max number of houses in the neighborhood
	for ( int i = 0; i < NUM_STREETS; ++i ) {

		Street* s = streets[i];
		if ( s->NumBuildings() > max )
			max = s->NumBuildings();

		if ( s->NumBuildings() < min )
			min = s->NumBuildings();

	}

	return max - min > 1;
}

StreetGroup::~StreetGroup() {
	delete[] streets;
}
