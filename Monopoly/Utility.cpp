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

	if (owner == p) {
		Console::Write(p->GetDisplayName() + " already owns " + NAME + "\n");
		return;
	}

	Roll r = p->DiceRoll();

	int amountToPay = 0;
	if (Utilities::NumOwnedBy(owner) == NUM_UTILITIES) {
		amountToPay = Utilities::Double_Multiplier * r.total;

	}
	else {
		amountToPay = Utilities::Single_Multiplier * r.total;

	}

	Console::Write(p->NAME + " will pay " + owner->NAME + "$" + itos(amountToPay) + "\n");
	p->PayPlayer(owner, amountToPay);

}

