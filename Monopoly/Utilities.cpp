#include "Utilities.h"
#include "Player.h"

Utility** Utilities::Utilities;

int Utilities::Single_Multiplier;
int Utilities::Double_Multiplier;

int Utilities::NumOwnedBy(const Player* const p) {

	int count = 0;
	if (Utilities[0]->GetOwner() == p) {
		count++;
	}
	if (Utilities[1]->GetOwner() == p) {
		count++;
	}
	return count;

}

void Utilities::Quit() {

	delete[] Utilities;
}