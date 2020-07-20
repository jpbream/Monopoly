#pragma once
#include "Player.h"
#include "Street.h"

//a type of player, controlled by an actual human being
class Person : public Player
{

private:

	//queries the player with the given decision
	Executable* QueryImplementation(Executable* decision1, Executable* decision2) override;
	 
	//player liquidates their assets one by one in an attempt to come up with amount of cash.
	// returns how much the item sold for
	int ScroungeCashImplementation(int amount) override;

	// helper method for scrounge cash
	// ensures the string is the name of a valid street space
	Street* ValidateStreet(const std::string& spaceName);

	// helper method for scrounge cash
	// ensures the string is the name of a valid property space
	Property* ValidateProperty(const std::string& spaceName);

	// helper method for scrounge cash. attempts to sell a house on this property
	// if unsuccessful, prints a message why and returns 0. otherwise, 
	// returns how much it sold for
	int SellHouse(Street* prop);

	// helper method for scrounge cash. attempts to sell a hotel on this property
	// if unsuccessful, prints a message why and returns 0. otherwise,
	// returns how much it sold for
	int SellHotel(Street* prop);

	// helper method for scrounge cash. attempts to sell this property
	// is unsuccessful, prints a message why and returns 0. otherwise,
	// returns how much it sold for
	int SellProperty(Property* prop);

public:

	// used to hold a copy of a person during a backup
	Person();
	Person(const Person& other);
	virtual Person& operator=(const Person& other);

	Person(const std::string& name, const std::string& gamepiece);

	//will prompt the real life person to roll dice and enter their values. 
	// if in a simulation, dice are rolled automatically
	Roll DiceRoll() override;

};

