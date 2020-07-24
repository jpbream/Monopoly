#pragma once
#include "Space.h"

class Player;

//a type of space that can be bought and mortgaged, and other players are charged when they land on
class Property : public Space
{

protected:

	//the player who owns this property
	Player* owner = nullptr;

	//whether or not the property is mortgaged
	bool mortgaged = false;

	//the action to take when p lands on this space when it is already owned by another player, is called by LandOn
	virtual void LandOnOwned(Player* const p) = 0;

public:

	//enum for the type that this property is
	//const Type TYPE;

	//the percent markup of the mortgage that must be payed to unmortgage a property
	constexpr static double UNMORTGAGE_MARKUP = 0.1;

	//how much it costs to buy this property
	const int PRICE;

	//how much you get from the bank to mortgage the property
	const int MORTGAGE;

	Property();
	Property(const Property& other);
	Property& operator=(const Property& other);

	Property(int index, const std::string& name, int price, int mortgage);

	//sets the player that owns this property
	void SetOwner(Player* const p);

	//sets whether the property is mortgaged, a property owned by the bank cannot be mortgaged
	void SetMortgaged(bool b);

	//returns a pointer to the player who owns this property, returns nullptr if the bank owns it
	Player* const GetOwner() const;

	//returns whether or not this property is currently mortgaged
	bool IsMortgaged() const;

	//the action to take when p lands on this space
	void LandOn(Player* const p) override;

};

