#pragma once
#include <string>
#include <vector>
#include "Dice.h"
#include "Board.h"
#include "Property.h"
#include "Executables.h"

//highest value for risk, inclusive
#define MAX_RISK 100

//lowest value for risk, inclusive
#define MIN_RISK 15

//number of properties on the board
#define PROPERTY_ARRAY_SIZE 28

class DecisionActions;
class Bank;
class FreeParking;

//base class for user playing the game
class Player
{

	friend class Bank;
	friend class FreeParking;

private:

	//whether the player is in jail
	bool inJail = false;

	//the number of turns the player has spent in jail
	int turnsInJail = 0;

	//whether this player is still in the game
	bool inGame = true;

	//number of get out of jail free cards the player has
	int numGetOutOfJailFree = 0;

	//helper method for the pay player/bank/free parking methods
	// determines whether the player will need to scrounge for cash to make this payment,
	// if so, it scrounges for the appropriate amount
	bool VerifyPayment(int amount);
	
	//Query when in a simulation, will return their expected decision based on risk
	Executable* QueryWhenInSimulation(Executable* decision1, Executable* decision2);

	//liquidates assests to come up with amount of cash. returns if the player
	// was able to come up with the money
	bool ScroungeCash(int amount);

	// use when in a simulation. randomly picks an item to sell
	// returns amount actually sold
	int ScroungeCashWhenInSimulation(int requiredAmount);

protected:

	//number representing the players willingness to risk/confidence
	int risk;

	//index of the square the player is at
	int currentSquare;

	//how much money the player has
	int money;

	//holds pointers to the properties owned by the player
	std::vector<Property*> properties;

	// implementation of the choosing. For players, they will type in their decision
	// bots will simulate games to make their decision
	virtual Executable* QueryImplementation(Executable* decision1, Executable* decision2) = 0;

	// player picks one more item to sell and sells it. returns how much it sold for
	// used when scrounging for cash, returns amount actuall sold
	virtual int ScroungeCashImplementation(int requiredAmount) = 0;

	// helper function for sell next and scrounge cash, determines how
	// many more items this player owns that they can sell
	// parameter is whether each item should be printed to the console
	int AllSellables(bool print) const;

	// returns a list of items that can be sold without causing
	// a house imbalance
	std::vector<SellItem> ImmediateSellables();

public:

	//the players name
	const std::string NAME;

	//the piece the player is using
	const std::string GAMEPIECE;

	// used during backups
	Player();
	Player(const Player& other);
	virtual Player& operator=(const Player& other);

	//use this constructor to make players that will be playing in the game
	Player(const std::string& name, const std::string& gamepiece);

	//returns the roll object that was rolled
	virtual Roll DiceRoll() = 0;

	//player evaluates the decision. returns the decision they choose
	Executable* Query(Executable* decision1, Executable* decision2);

	//Returns the index of the space the player is currently on
	int GetCurrentSquare() const;

	//if player has spent max turns in jail, releases them. otherwise asks them if they want to bail out or use 
	// get out of jail free card. Returns whether they got out of jail
	bool RunBailOutRoutine();

	// rolls the dice and moves the player. performs the action of the space they landed on.
	void RunRollAndMoveRoutine();

	//move forward an amount of spaces. performs the action of the space we land on on the player
	void Advance(int numSpaces);

	//move to the specified space. CollectGo is whether player should collect 200 if they pass go
	void MoveTo(int index, bool collectGo);

	//returns the players name with their gamepiece in parenthesis
	std::string GetDisplayName() const;

	//makes a payment to amother player, if the payment cannot be made, removes player from the game
	void PayPlayer(Player* const recipient, int amount);

	void PayBank(int amount);

	void PayFreeParking(int amount);

	//returns the number of properties owned by the player
	int NumProperties() const;

	//returns pointer the property at index
	Property* GetProperty(int index);

	// adds the property to the players list of properties
	void AddProperty(Property* prop);

	// removes the property from the players list of properties
	void RemoveProperty(Property* prop);

	//sets the players state to be in jail, does NOT move the player to the jail space
	void PutInJail();

	//sets the players state to be out of jail
	void ReleaseFromJail();

	//returns whether the player is currently in jail
	bool IsInJail() const;

	//the number of turns the player has spent in jail
	int TurnsInJail() const;

	//whether the player is in the game
	bool InGame() const;

	//removes the player from the game
	void RemoveFromGame();

	//gives the player a get out of jail free card
	void GiveGetOutOfJailFree();

	// removes one of the players get out of jail free cards
	void UseGetOutOfJailFree();

	//returns the players cash sum plus the amount of money they could make if they sold everything they owned
	int CalculateNetWorth() const;

	//returns the players cash sum
	int AmountMoney() const;

};

