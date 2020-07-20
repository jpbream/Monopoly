#include "Person.h"
#include "Bank.h"
#include "Property.h"
#include "Actions.h"
#include "Board.h"
#include "Monopoly.h"
#include "Console.h"
#include "Street.h"
#include "Streets.h"

#include <sstream>
#include <algorithm>
#include <assert.h>

Person::Person() : Player() {}
Person::Person(const Person& other) : Player(other) {}
Person& Person::operator=(const Person& other)
{
	Player::operator=(other);
	return *this;
}

Person::Person(const std::string& name, const std::string& gamepiece) : Player(name, gamepiece)
{
}

Roll Person::DiceRoll() {

	if (Monopoly::InSimulation()) {

		return Dice::Toss();
	}
	else {
		Console::Write("Roll the dice and enter their values: ");

		int d1, d2;
		Console::Get<int>(2, &d1, &d2);

		return Roll(d1, d2);
	}
}

Executable* Person::QueryImplementation(Executable* decision1, Executable* decision2) {

	Console::Write(NAME + ", enter the number of your decision: ");
	char response;
	Console::Get<char>(1, &response);

	if ( response == '2' ) {
		return decision2;
	}
	else {
		return decision1;
	}
}

Street* Person::ValidateStreet(const std::string& spaceName)
{
	if ( Board::NameToIndexMap.find(spaceName) == Board::NameToIndexMap.end() )
		return nullptr;
	Space* space = Board::Spaces[Board::NameToIndexMap[spaceName]];
	Street* street = dynamic_cast<Street*>(space);

	return street;
}

Property* Person::ValidateProperty(const std::string& spaceName)
{
	if ( Board::NameToIndexMap.find(spaceName) == Board::NameToIndexMap.end() )
		return nullptr;

	Space* space = Board::Spaces[Board::NameToIndexMap[spaceName]];
	Property* prop = dynamic_cast<Property*>(space);

	return prop;
}

int Person::SellHouse(Street* street)
{
	if ( street->GetOwner() == this ) {
		if ( street->RemoveHouse() ) {

			int salePrice = street->GetNeighborhood()->HOUSE_COST * Streets::BUILDING_RESALE_DEPRECIATION;
			Console::Write(NAME + " sells a house on " + street->NAME + "\n");
			Bank::PayPlayer(this, salePrice);
			return salePrice;

		}
		else {
			Console::Write("A house cannot be removed from " + street->NAME + "\n");
		}
	}
	else {
		Console::Write(NAME + " does not own " + street->NAME + "\n");
	}

	return 0;
}

int Person::SellHotel(Street* street)
{
	if ( street->GetOwner() == this ) {
		if ( street->RemoveHotel() ) {

			int salePrice = street->GetNeighborhood()->HOTEL_COST * Streets::BUILDING_RESALE_DEPRECIATION;
			Console::Write(NAME + " sells a hotel on " + street->NAME + "\n");
			Bank::PayPlayer(this, salePrice);
			return salePrice;

		}
		else {
			Console::Write("A hotel cannot be removed from " + street->NAME + "\n");
		}
	}
	else {
		Console::Write(NAME + " does not own " + street->NAME + "\n");
	}

	return 0;
}

int Person::SellProperty(Property* prop)
{
	if ( prop->GetOwner() == this ) {

		Street* street = dynamic_cast<Street*>(prop);

		// if the building is a street, it must have 0 buildings
		if ( !street || street->NumBuildings() == 0 ) {

			// mortgage the property and give it back to the bank
			prop->SetMortgaged(true);
			prop->SetOwner(nullptr);

			// remove the property from this player
			RemoveProperty(prop);

			int salePrice = prop->MORTGAGE;
			Console::Write(NAME + " mortgages " + prop->NAME + "\n");
			Bank::PayPlayer(this, salePrice);
			return salePrice;
		}
		else {
			Console::Write("The buildings on " + prop->NAME + " must be sold first.\n");
		}
	}
	else {
		Console::Write(NAME + " does not own " + prop->NAME + "\n");
	}

	return 0;
}

int Person::ScroungeCashImplementation(int requiredAmount) {

	// this code could be greatly simplified using the sell item executables
	// but this way provides a better user experience

	Console::Write("Enter a command to sell an item. Type 'help' to see how to use the commands.\n");
	
	int amountScrounged = 0;

	while ( amountScrounged < requiredAmount && AllSellables(false) > 0 ) {

		Console::Write("Command> ");

		std::string rawResponse;
		Console::GetLine(rawResponse);

		std::stringstream responseStream(rawResponse);

		// get the command they entered
		std::string keyword;
		responseStream >> keyword;

		// get the space they entered and convert it to uppercase
		std::string space;
		std::getline(responseStream, space);

		// trim the rest of the line
		int start = space.find_first_not_of(" \n\r\t\f\v");
		if ( start != std::string::npos )
			space = space.substr(start);

		int end = space.find_last_not_of(" \n\r\t\f\v");
		if ( end != std::string::npos )
			space = space.substr(0, end + 1);

		std::for_each(space.begin(), space.end(), [](char& c) {c = ::toupper(c); });

		Console::IncreaseIndent();
		if ( keyword == "help" ) {
			Console::Write("Type 'house <property>' to sell a house.\n");
			Console::Write("Type 'hotel <property>' to sell a hotel.\n");
			Console::Write("Type 'prop <property>' to sell a property.\n");
			Console::Write("Type 'status' to see how much money you still need.\n");
			Console::Write("Type 'list' to see what you still can sell.\n");

		}
		else if ( keyword == "status" ) {
			Console::Write(NAME + " needs to come up with $" + itos(requiredAmount - amountScrounged) + "\n");
		}
		else if ( keyword == "list" ) {
			Console::Write("Here is what " + NAME + " still can sell:\n");
			AllSellables(true);
		}
		// SELLING A HOUSE
		else if ( keyword == "house" ) {

			// check if it was a valid space
			Street* street = ValidateStreet(space);
			if ( street ) {
				amountScrounged += SellHouse(street);
			}
			else {
				Console::Write(space + " is not a valid street space.\n");
			}
		}
		// SELLING A HOTEL
		else if ( keyword == "hotel" ) {

			// check if it was a valid space
			Street* street = ValidateStreet(space);
			if ( street ) {
				amountScrounged += SellHotel(street);
			}
			else {
				Console::Write(space + " is not a valid street space.\n");
			}
		}
		// SELLING A PROPERTY
		else if ( keyword == "prop" ) {

			// check if it was a valid space
			Property* prop = ValidateProperty(space);

			if ( prop ) {
				amountScrounged += SellProperty(prop);
			}
			else {
				Console::Write(space + " is not a valid property space.\n");
			}
		}
		else {
			Console::Write("You entered an invalid command.\n");
		}
		Console::DecreaseIndent();
	}

	return amountScrounged;
}