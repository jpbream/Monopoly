#pragma once
#include <string>

class Player;
class Property;

// an object of this class can perform an action in the game
// use its Perform Action function to do so
class Executable {

public:

	// performs the action of this executable
	virtual void PerformAction() = 0;

	// return the monetary cost of performing this action
	virtual int GetPrice() = 0;

	// prints out what this executable will do
	// used to display to human players what their options are
	virtual std::string ToString() = 0;

};

// take no action
class DoNothing : public Executable {

public:
	void PerformAction() override;
	int GetPrice() override;
	std::string ToString() override;
};

// pays the 50 dollar fine and releases the player from jail
class PayJailBail : public Executable {

private:
	Player* player;

public:
	PayJailBail(Player* player);
	void PerformAction() override;
	int GetPrice() override;
	std::string ToString() override;
};

// uses a get out of jail free and releases the player from jail
class GetOutOfJailFree : public Executable {

private:
	Player* player;

public:
	GetOutOfJailFree(Player* player);
	void PerformAction() override;
	int GetPrice() override;
	std::string ToString() override;

};

// buys a property
class BuyProperty : public Executable {

private:
	Player* player;
	Property* property;

public:
	BuyProperty(Player* player, Property* property);
	void PerformAction() override;
	int GetPrice() override;
	std::string ToString() override;

	Property* GetProperty();

};

// action that sells either a house, hotel, or property belonging to a specific player
class SellItem : public Executable {

public:
	enum class Items {
		PROPERTY,
		HOTEL,
		HOUSE
	};

private:

	// player who will be selling an item
	Player* player;

	// type of item that is being sold
	Items item;

	// the property that the sale is occuring on
	Property* property;

	// how much the sale is for
	int salePrice = 0;

public:

	SellItem(Player* player, Items item, Property* property);
	void PerformAction() override;

	// returns the negative of how much the item sold for
	int GetPrice() override;
	std::string ToString() override;

	// return how much the item sold for
	int GetSalePrice();
	Property* GetProperty();
	Items ItemType();
};

