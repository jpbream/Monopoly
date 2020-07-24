#include "Property.h"
#include "Board.h"
#include "Bank.h"
#include "Console.h"
#include "Player.h"
#include "Players.h"

Property::Property() : Space(), PRICE(0), MORTGAGE(0) 
{
	owner = nullptr;
	mortgaged = false;

}
Property::Property(const Property& other) : Space(other), PRICE(other.PRICE), MORTGAGE(other.MORTGAGE) 
{
	owner = other.owner;
	mortgaged = other.mortgaged;
}
Property& Property::operator=(const Property& other)
{
	Space::operator=(other);
	*(int*)&PRICE = other.PRICE;
	*(int*)&MORTGAGE = other.MORTGAGE;

	owner = other.owner;
	mortgaged = other.mortgaged;
	return *this;

}

Property::Property(int index, const std::string& name, int price, int mortgage) :
	Space(index, name), PRICE(price), MORTGAGE(mortgage)
{

}

void Property::LandOn(Player* const p) {

	//if no one owns this property
	if (owner == nullptr) {

		Console::Write(p->GetDisplayName() + " has landed on " + NAME + ", which is available for purchase. \n");

		//query the player if they want to buy
		BuyProperty buyThis(p, this);
		DoNothing doNothing;
		Executable* response = p->Query(&buyThis, &doNothing);

		//they said yes
		if (response == &buyThis) {

			//attempt to make the payment, will not let them sell other stuff to afford this payment
			if (p->AmountMoney() >= PRICE) {

				Console::Write(p->NAME + " has decided to buy " + NAME + "\n");

				//perform action to buy property
				buyThis.PerformAction();

				Console::Write("Great! " + p->GetDisplayName() + " now owns " + NAME + "\n");

			}
			else {
				//they don't have enough cash
				Console::Write(p->GetDisplayName() + " does not have enough money to afford " + NAME + "\n");
			}

		}
		else {
			//they said no
			Console::Write(p->GetDisplayName() + " has chosen not to buy " + NAME + "\n");
			doNothing.PerformAction();
		}

	}
	else if ( owner == p ) {
		
		// if p already owns this street, if so do nothing
		Console::Write(p->GetDisplayName() + " already owns " + NAME + "\n");
	}
	else {
		//if someone owns the property
		LandOnOwned(p);
		
	}

}

void Property::SetOwner(Player* const p) {

	owner = p;

	//if the property goes back to the bank it is unmortgaged
	if (p == nullptr) {
		mortgaged = false;
	}

	//otherwise, if it is mortgaged, the new owner is responsible to pay that

}

void Property::SetMortgaged(bool b) {

	//if property is owned by the bank, do not change its mortgage status
	if (owner != nullptr) {
		mortgaged = b;
	}

}

Player* const Property::GetOwner() const {
	
	return owner;

}

bool Property::IsMortgaged() const {
	return mortgaged;
}
