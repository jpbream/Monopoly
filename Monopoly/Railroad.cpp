#include "Railroad.h"
#include "Railroads.h"
#include "Player.h"
#include "Console.h"

Railroad::Railroad() : Property() {}
Railroad::Railroad(const Railroad& other) : Property(other) {}
Railroad& Railroad::operator=(const Railroad& other)
{
	Property::operator=(other);
	return *this;
}

Railroad::Railroad(int index, const std::string& name, int price, int mortgage) : Property(index, name, price, mortgage)
{
}

void Railroad::LandOnOwned(Player* const p) {

	if (owner == p) {
		Console::Write(p->GetDisplayName() + " already owns " + NAME + "\n");
		return;
	}

	int numOwned = 0;
	for (int i = 0; i < NUM_RAILROADS; ++i) {
		if (Railroads::Railroads[i]->owner == owner) {
			numOwned++;
		}
	}

	int amountToPay = 0;
	if (numOwned == 1) {
		amountToPay = Railroads::Rent_1;
	}
	else if (numOwned == 2) {
		amountToPay = Railroads::Rent_2;
	}
	else if (numOwned == 3) {
		amountToPay = Railroads::Rent_3;
	}
	else if (numOwned == 4) {
		amountToPay = Railroads::Rent_4;
	}

	Console::Write(p->NAME + " will pay " + owner->NAME + "$" + itos(amountToPay) + "\n");
	p->PayPlayer(owner, amountToPay);

}

