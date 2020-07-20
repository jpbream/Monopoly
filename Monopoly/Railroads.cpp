#include "Railroads.h"
#include "Player.h"

int Railroads::Rent_1 = 25;
int Railroads::Rent_2 = 50;
int Railroads::Rent_3 = 100;
int Railroads::Rent_4 = 200;

Railroad** Railroads::Railroads;

int Railroads::NumOwnedBy(const Player* const p) {

	int count = 0;
	for (int i = 0; i < NUM_RAILROADS; i++) {
		if (Railroads[i]->GetOwner() == p) {
			count++;
		}
	}
	
	return count;

}

void Railroads::Quit() {

	delete[] Railroads;
}