#include "Player.h"
#include "Bank.h"
#include "Board.h"
#include "Actions.h"
#include "Console.h"
#include "CardActions.h"
#include "FreeParking.h"
#include "Monopoly.h"
#include "Street.h"
#include "Streets.h"
#include <algorithm>

Player::Player() : NAME(""), GAMEPIECE("")
{	
	inJail = false;
	turnsInJail = 0;
	inGame = true;
	numGetOutOfJailFree = 0;
	risk = 0;
	currentSquare = 0;
	money = 0;
}
Player::Player(const Player& other)
	:
	NAME(other.NAME), GAMEPIECE(other.GAMEPIECE)
{
	inJail = other.inJail;
	turnsInJail = other.turnsInJail;
	inGame = other.inGame;
	numGetOutOfJailFree = other.numGetOutOfJailFree;
	risk = other.risk;
	currentSquare = other.currentSquare;
	money = other.money;

	// perform a deep copy of the properties
	properties = other.properties;
}
Player& Player::operator=(const Player& other)
{
	*(std::string*)& NAME = other.NAME;
	*(std::string*)& GAMEPIECE = other.GAMEPIECE;

	inJail = other.inJail;
	turnsInJail = other.turnsInJail;
	inGame = other.inGame;
	numGetOutOfJailFree = other.numGetOutOfJailFree;
	risk = other.risk;
	currentSquare = other.currentSquare;
	money = other.money;

	// perform a deep copy of the properties
	properties = other.properties;

	return *this;
}

Player::Player(const std::string& name, const std::string& gamepiece) : NAME(name), GAMEPIECE(gamepiece)
{

	risk = 0;

	//start at GO square
	currentSquare = 0;

	//start with 0 money
	money = 0;

	//transfer the starting cash to this player
	Bank::PayPlayer(this, Monopoly::START_CASH);

}

void Player::Advance(int numSpaces) {

	//stores previous square
	int prevSquare = currentSquare;

	//wraps back to zero if it passes the last square
	currentSquare = (currentSquare + numSpaces) % NUM_SPACES;

	//check if the player passes go but does not land on it
	// landing on go will be handled by the Go spaces LandOn override
	if (currentSquare != 0 && currentSquare < prevSquare) {
		Console::Write(GetDisplayName() + " passed go!\n");
		Actions::PassGo(this);
	}

	//prompt the movement
	const std::string& newSquareName = Board::Spaces[currentSquare]->NAME;
	Console::Write("Move " + GetDisplayName() + " " +
		itos(numSpaces) + " spaces forward to " + newSquareName + "\n");

	//cause subsequent action
	Board::Spaces[currentSquare]->LandOn(this);
	
}

int Player::GetCurrentSquare() const {
	return currentSquare;
}

void Player::MoveTo(int index, bool collectGo) {

	int prevSquare = currentSquare;
	currentSquare = index;

	//check if the player passes go but does not land on it, and player is allowed to collect go money
	if (currentSquare != 0 && currentSquare < prevSquare && collectGo) {
		Console::Write(GetDisplayName() + " passed go!\n");
		Actions::PassGo(this);
	}

	//prompt the movement
	const std::string& newSquareName = Board::Spaces[currentSquare]->NAME;
	Console::Write("Move " + GetDisplayName() + " to " + newSquareName + "\n");

	//cause subsequent action
	Board::Spaces[currentSquare]->LandOn(this);

}

bool Player::RunBailOutRoutine() {

	//ask them if they want to use a get out of jail free
	if (numGetOutOfJailFree > 0) {

		GetOutOfJailFree getOut(this);
		DoNothing doNothing;

		Console::Write(NAME + " may use a get out of jail free card.\n");
		Executable* wantToUse = Query(&getOut, &doNothing);

		if (wantToUse == &getOut) {

			// perform the action
			getOut.PerformAction();
			return true;
		}
	}

	//ask them if they want to pay the fee
	if (turnsInJail < Actions::MAX_TURNS_JAIL) {

		//only ask them if they want to pay if they have more than the bail in cash
		if (money >= Actions::JAIL_BAIL) {

			PayJailBail pay(this);
			DoNothing doNothing;

			Console::Write(NAME + " may pay the fee to get out of jail.\n");
			Executable* wantToPay = Query(&pay, &doNothing);

			if (wantToPay == &pay) {
				
				// perform the action
				pay.PerformAction();
				return true;
			}
		}
		else {
			Console::Write(GetDisplayName() + " does not have enough cash to pay the jail fee.\n");
		}

	}
	else {

		//they have spent the max time in jail
		Console::Write(GetDisplayName() + " has spent the max amount of turns in jail. They must pay "
			+ itos(Actions::JAIL_BAIL) + " to leave.\n");

		CardActions::Pay(this, Actions::JAIL_BAIL);
		ReleaseFromJail();
		return true;

	}

	//if the player has done nothing to release themselves from jail, increment turnsInJail
	turnsInJail++;

	return false;

}

void Player::RunRollAndMoveRoutine()
{
	//initial roll
	Roll roll = DiceRoll();

	//used if doubles are rolled
	bool doneRolling = false;
	int numDoubles = 0;

	while ( !doneRolling ) {

		//run the actions for the roll
		Advance(roll.total);

		// if that roll put them in jail, exit here
		if ( IsInJail() )
			return;

		//if they rolled doubles
		if ( roll.doubles ) {
			numDoubles++;

			//if they have not yet rolled enough doubles to get thrown in jail
			if ( numDoubles < Actions::JAIL_DOUBLES ) {
				Console::Write(GetDisplayName() + " rolled doubles and gets to go again!\n");
				Console::Pause();
				roll = DiceRoll();
			}
			else {
				//they rolled enough doubles to get thrown in jail
				Console::Write(GetDisplayName() + " rolled doubles " + itos(Actions::JAIL_DOUBLES)
					+ " times and will go to jail!\n");

				doneRolling = true;

				//put them in jail
				Actions::GoToJail(this);
			}

		}
		else {
			//otherwise, they are done rolling
			doneRolling = true;
		}

	}
}

void Player::RunInJailRoutine()
{
	//player doesnt get to do anything if they just got put in jail
	if ( TurnsInJail() > 0 ) {

		Console::Write(GetDisplayName() + " will try to roll doubles to get out of jail.\n");

		//try to roll doubles
		Roll roll = DiceRoll();

		//the player spending the max turns in jail is handled by the
		// player->QueryBailOut method

		if ( roll.doubles ) {

			Console::Write(GetDisplayName() + " has rolled doubles and is free from jail.\n");
			ReleaseFromJail();

			//they get to move by the doubles they just rolled
			Advance(roll.total);

		}
		else {

			//they stay in jail
			Console::Write(GetDisplayName() + " has failed to roll doubles and remains in jail.\n");

		}
	}
}

void Player::RunBuyBuildingsRoutine()
{
	bool canBuyBuildings = false;
	for ( Property* prop : properties ) {
		Street* street = dynamic_cast<Street*>(prop);
		if ( street ) {

			const StreetGroup* group = street->GetNeighborhood();
			if ( group->QueryOwner() == this ) {

				// if the street does not have a hotel, the player can build
				if ( street->NumHotels() == 0 )
					canBuyBuildings = true;

			}
		}
	}

	if ( canBuyBuildings ) {
		Console::Write(NAME + " has the option to buy houses.\n");
	}
	else {
		Console::Write(NAME + " is not able to buy houses at this time.\n");
		return;
	}

	if ( Monopoly::InSimulation() ) {
		BuyBuildingsWhenInSimulation();
	}
	else {

	}

}

void Player::BuyBuildingsWhenInSimulation()
{
	// want the simulator to be able to buy buildings to see
	// if buying a property will actually have a benefit for them

	if ( Monopoly::GetSimulator() == this ) {

		std::vector<BuyItem> buyables = ImmediateBuyables();
		int startCash = AmountMoney();

		for ( BuyItem& buyable : buyables ) {

			buyable.PerformAction();

			// quit if the bot has spent 75% of its money
			if ( AmountMoney() < (int)(startCash / 4) )
				return;
		}

	}

	// other players should not do anything so as to not discourage the simulator
	// from ever buying a property

}

Executable* Player::QueryWhenInSimulation(Executable* decision1, Executable* decision2) {

	if ( Monopoly::GetSimulator() == this ) {
		return decision2;
	}
	else {

		// other players should choose the options that does less
		// we want the bot simulating to see the effects of its action alone
		if ( decision1->GetPrice() < decision2->GetPrice() )
			return decision1;
		return decision2;

	}
}

Executable* Player::Query(Executable* decision1, Executable* decision2)
{

	// if the game is in a simulation, use the randomized query function
	if ( Monopoly::InSimulation() ) {
		return QueryWhenInSimulation(decision1, decision2);
	}

	Console::Write(GetDisplayName() + " is faced with a decision: \n");
	Console::IncreaseIndent();
	Console::Write("Option 1: " + decision1->ToString() + "\n");
	Console::Write("Option 2: " + decision2->ToString() + "\n");
	Console::DecreaseIndent();

	Executable* chosen = QueryImplementation(decision1, decision2);
	if ( chosen == decision1 ) {
		Console::Write(NAME + " has chosen Option 1.\n");
	}
	else if (chosen == decision2) {
		Console::Write(NAME + " has chosen Option 2.\n");
	}

	return chosen;

}

bool Player::ScroungeCash(int amount)
{

	if ( AllSellables(false) )
		Console::Write("Here is what " + NAME + " has to sell:\n");
	else {
		Console::Write(NAME + " has no items they can sell to come up with the money.\n");
		return false;
	}

	// write out all the items the player can sell
	Console::IncreaseIndent();
	AllSellables(true);
	Console::DecreaseIndent();

	int actual = 0;
	
	if ( Monopoly::InSimulation() )
		actual = ScroungeCashWhenInSimulation(amount);
	else
		actual = ScroungeCashImplementation(amount);

	if ( actual >= amount ) {
		Console::Write(NAME + " was able to complete the payment.\n");
		return true;
	}
	else {
		Console::Write(NAME + " has nothing left to sell and still came up $" + itos((amount - actual)) + " short on the payment.\n");
		return false;
	}
}

int Player::ScroungeCashWhenInSimulation(int requiredAmount)
{

	int amountSold = 0;
	std::vector<SellItem> itemsToSell = ImmediateSellables();

	// loop while there are still things left, sell 1 item at a time
	while ( amountSold < requiredAmount && itemsToSell.size() > 0 ) {

		for ( SellItem& item : itemsToSell ) {

			amountSold += item.GetSalePrice();
			item.PerformAction();
			if ( amountSold >= requiredAmount )
				break;

		}

		itemsToSell = ImmediateSellables();
	}

	return amountSold;
}

int Player::AllSellables(bool print) const
{

	int numSellables = 0;

	// write out all the properties and buildings the player can sell
	for ( Property* prop : properties ) {

		// if it is a street, write out the number of houses and hotels
		Street* street = dynamic_cast<Street*>(prop);
		if ( street ) {

			Console::IncreaseIndent();
			if ( street->NumHouses() > 0 ) {

				int houseSell = (int)(street->GetNeighborhood()->HOUSE_COST * Streets::BUILDING_RESALE_DEPRECIATION);
				if ( print )
					Console::Write(itos(street->NumHouses()) + " houses on " + street->NAME + " for $" + itos(houseSell) + " each.");

				numSellables += street->NumHouses();
			}

			if ( street->NumHotels() > 0 ) {
				int hotelSell = (int)(street->GetNeighborhood()->HOTEL_COST * Streets::BUILDING_RESALE_DEPRECIATION);
				if ( print )
					Console::Write(itos(street->NumHouses()) + " hotel on " + street->NAME + " for $" + itos(hotelSell) + " each.");

				// a hotel counts as 5 sellable items
				numSellables += MAX_BUILDING;
			}
			Console::DecreaseIndent();

		}

		// write the property mortgage
		if ( print )
			Console::Write(prop->NAME + " for $" + itos(prop->MORTGAGE) + "\n");
		numSellables++;
	}

	return numSellables;
}

std::vector<SellItem> Player::ImmediateSellables()
{

	std::vector<SellItem> sellables;
	for ( Property* prop : properties ) {

		Street* street = dynamic_cast<Street*>(prop);
		if ( street && street->NumBuildings() > 0) {

			// if the item is a street, add the top most building
			// if it can be removed

			if ( street->NumHotels() > 0 ) {
				if ( street->RemoveHotel() ) {

					street->AddHotel();
					sellables.emplace_back(this, SellItem::Items::HOTEL, street);
				}
			}
			else {
				if ( street->RemoveHouse() ) {

					street->AddHouse();
					sellables.emplace_back(this, SellItem::Items::HOUSE, street);
				}
			}
		}
		else {

			// otherwise, add the property as is
			sellables.emplace_back(this, SellItem::Items::PROPERTY, prop);

		}

	}

	// sort the sellables by priority, lower items will be sold first
	std::sort(sellables.begin(), sellables.end(), [](SellItem& s1, SellItem& s2) {

		if ( s1.ItemType() != s2.ItemType() ) {
			return s1.ItemType() < s2.ItemType();
		}

		if ( s1.ItemType() == SellItem::Items::PROPERTY ) {

			// sell properties not part of a complete set first
			if ( dynamic_cast<Street*>(s1.GetProperty()) ) {

				Street* s1Street = dynamic_cast<Street*>(s1.GetProperty());
				Street* s2Street = dynamic_cast<Street*>(s2.GetProperty());
				if ( !s2Street )
					return false;

				bool s1Complete = s1Street->GetNeighborhood()->QueryOwner();
				bool s2Complete = s2Street->GetNeighborhood()->QueryOwner();

				if ( s1Complete && !s2Complete )
					return false;
				else
					return true;

			}

			// if s1 is not a street, put it towards the front
			return true;
			
		}

		return false;
	});

	return sellables;
}

std::vector<BuyItem> Player::ImmediateBuyables()
{
	std::vector<BuyItem> buyables;
	int budget = AmountMoney();

	for ( Property* prop : properties ) {
		Street* street = dynamic_cast<Street*>(prop);
		if ( street ) {
			const StreetGroup* group = street->GetNeighborhood();
			if ( group->QueryOwner() == this ) {

				if ( street->AddHouse() ) {
					street->RemoveHouse();

					if ( budget >= group->HOUSE_COST ) {
						buyables.emplace_back(this, BuyItem::Items::HOUSE, street);
						budget -= group->HOUSE_COST;
					}
				}

				if ( street->AddHotel() ) {
					street->RemoveHotel();

					if ( budget >= group->HOTEL_COST ) {
						buyables.emplace_back(this, BuyItem::Items::HOTEL, street);
						budget -= group->HOTEL_COST;
					}
				}

			}
		}
	}

	std::sort(buyables.begin(), buyables.end(), [](BuyItem& b1, BuyItem& b2) {
		return b1.ItemType() < b2.ItemType();
	});

	return buyables;
}

bool Player::VerifyPayment(int amount) {

	//amount of cash the player lacks (if any)
	int lackingCash = amount - money;

	//if the player is lacking cash
	if (lackingCash > 0) {

		//it will be decided by if they can scrounge the cash
		return ScroungeCash(lackingCash);

	}

	//the player will be able to make the payment
	return true;

}

void Player::PayPlayer(Player* const recipient, int amount) {

	//verify the payment
	bool ableToPay = VerifyPayment(amount);

	if (!ableToPay) {
		//player can't pay

		Console::Write(GetDisplayName() + " pays $" + itos(money) + " to " + recipient->NAME + "\n");

		//player gives all remaining money to recipient
		recipient->money += money;
		money = 0;

		// player is out of the game

		// give all this players property to the other player
		for ( Property* prop : properties ) {

			prop->SetOwner(recipient);
			recipient->AddProperty(prop);

			Console::Write(GetDisplayName() + " gives " + prop->NAME + " to " + recipient->NAME + "\n");
		}

		throw this;
	}

	Console::Write(GetDisplayName() + " pays $" + itos(amount) + " to " + recipient->NAME + "\n");

	//make the payment
	recipient->money += amount;
	money -= amount;

}

void Player::PayBank(int amount) {

	//verify the payment
	bool ableToPay = VerifyPayment(amount);

	if (!ableToPay) {
		//player can't pay

		Console::Write(GetDisplayName() + " pays $" + itos(money) + " to " + Bank::NAME + "\n");

		//player gives all remaining money to the bank
		Bank::money += money;
		money = 0;

		// player is out of the game

		// give all this players property to the bank
		for ( Property* prop : properties ) {

			prop->SetOwner(nullptr);

			Console::Write(GetDisplayName() + " gives " + prop->NAME + " to " + Bank::NAME + "\n");
		}

		throw this;
	}

	Console::Write(GetDisplayName() + " pays $" + itos(amount) + " to " + Bank::NAME + "\n");

	//make the payment
	Bank::money += amount;
	money -= amount;

}

void Player::PayFreeParking(int amount) {

	//verify the payment
	bool ableToPay = VerifyPayment(amount);

	if (!ableToPay) {
		//player can't pay

		Console::Write(GetDisplayName() + " pays $" + itos(money) + " to " + FreeParking::NAME + "\n");

		//player gives all remaining money to the bank
		FreeParking::money += money;
		money = 0;

		// player is out of the game

		// give all this players property to the bank
		for ( Property* prop : properties ) {

			prop->SetOwner(nullptr);

			Console::Write(GetDisplayName() + " gives " + prop->NAME + " to " + Bank::NAME + "\n");
		}

		throw this;
	}

	Console::Write(GetDisplayName() + " pays $" + itos(amount) + " to " + FreeParking::NAME + "\n");

	//make the payment
	FreeParking::money += amount;
	money -= amount;
}

int Player::CalculateNetWorth() const {

	if (!inGame) {
		return -1;
	}

	int netWorth = 0;

	// add in all the mortgage values of properties
	// and the house and hotel values
	for ( Property* p : properties ) {
		netWorth += p->MORTGAGE;

		// if the property is a street, add in the house and hotel values
		Street* s = dynamic_cast<Street*>(p);
		if ( s ) {

			netWorth += (int)(s->NumHouses() * s->GetNeighborhood()->HOUSE_COST * Streets::BUILDING_RESALE_DEPRECIATION);
			netWorth += (int)(s->NumHotels() * s->GetNeighborhood()->HOTEL_COST * Streets::BUILDING_RESALE_DEPRECIATION);
		}
	}

	// add in the players cash total
	netWorth += money;

	return netWorth;

}

int Player::NumProperties() const {
	
	return properties.size();
}

Property* Player::GetProperty(int index) {
	
	//checks that the index is valid
	return (index >= 0 && index < NumProperties()) ? properties[index] : nullptr;

}

void Player::AddProperty(Property* prop)
{
	if (std::find(properties.begin(), properties.end(), prop) == properties.end() )
		properties.push_back(prop);
}

void Player::RemoveProperty(Property* prop)
{
	
	for ( unsigned int i = 0; i < properties.size(); ++i ) {
		if ( properties[i] == prop ) {
			properties.erase(properties.begin() + i);
			return;
		}
	}

}

void Player::PutInJail() {
	inJail = true;
	turnsInJail = 0;
}

int Player::AmountMoney() const {
	return money;
}


void Player::ReleaseFromJail() {
	inJail = false;
	turnsInJail = 0;
}


bool Player::IsInJail() const {
	return inJail;
}

int Player::TurnsInJail() const {
	return turnsInJail;
}

std::string Player::GetDisplayName() const {
	return NAME + " (" + GAMEPIECE + ")";
}

bool Player::InGame() const {
	return inGame;
}

void Player::RemoveFromGame() {
	inGame = false;
}

void Player::GiveGetOutOfJailFree() {
	numGetOutOfJailFree++;
}

void Player::UseGetOutOfJailFree()
{
	numGetOutOfJailFree--;
}