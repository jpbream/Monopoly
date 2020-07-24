#include "Utility.h"
#include "Utilities.h"
#include "Player.h"
#include "Console.h"

Utility::Utility() : Property() {}
Utility::Utility(const Utility& other) : Property(other) {}
Utility& Utility::operator=(const Utility& other)
{
	Property::operator=(other);
	return *this;
}

Utility::Utility(int index, const std::string& name, int price, int mortgage) : Property(index, name, price, mortgage)
{

}

void Utility::LandOnOwned(Player* const p) {

	Roll r = p->DiceRoll();

	int amountToPay = 0;
	if (Utilities::NumOwnedBy(owner) == NUM_UTILITIES) {
		amountToPay = Utilities::Double_Multiplier * r.total;

	}
	else {
		amountToPay = Utilities::Single_Multiplier * r.total;

	}

	p->PayPlayer(owner, amountToPay);

}

