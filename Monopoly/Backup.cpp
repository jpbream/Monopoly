#include "Backup.h"

#include "Bank.h"
#include "Board.h"
#include "FreeParking.h"
#include "Monopoly.h"
#include "Players.h"
#include "Railroads.h"
#include "Streets.h"
#include "Utilities.h"

#include "Street.h"
#include "Railroad.h"
#include "Utility.h"
#include "Action.h"

#include "Person.h"
#include "Bot.h"

namespace Backup {

	static Space** Spaces;
	static int turn_count;
	static Player** Players;

	static int bankMoney;
	static int fpMoney;

	static int Rent_1;
	static int Rent_2;
	static int Rent_3;
	static int Rent_4;

	static int Single_Multiplier;
	static int Double_Multiplier;

	void MakeBackup() {

		bankMoney = Bank::AmountMoney();
		fpMoney = FreeParking::AmountMoney();

		Spaces = new Space*[NUM_SPACES];
		for (int i = 0; i < NUM_SPACES; i++) {

			//each space must be casted to its lowest level of class
			// so everything is copied

			Street* street = dynamic_cast<Street*>(Board::Spaces[i]);
			Railroad* railroad = dynamic_cast<Railroad*>(Board::Spaces[i]);
			Utility* utility = dynamic_cast<Utility*>(Board::Spaces[i]);
			Action* action = dynamic_cast<Action*>(Board::Spaces[i]);

			if (street != nullptr) {
				Spaces[i] = new Street(*street);
			}
			else if (railroad != nullptr) {
				Spaces[i] = new Railroad(*railroad);
			}
			else if (utility != nullptr) {
				Spaces[i] = new Utility(*utility);
			}
			else if (action != nullptr) {
				Spaces[i] = new Action(*action);
			}

		}

		turn_count = Monopoly::turn_count;

		Players = new Player*[Players::NumPlayers];
		for (int i = 0; i < Players::NumPlayers; i++) {

			//each player must be casted to its lowest level of class
			// so everything is copied

			Person* person = dynamic_cast<Person*>(Players::Players[i]);
			Bot* bot = dynamic_cast<Bot*>(Players::Players[i]);

			if (person != nullptr) {
				Players[i] = new Person(*person);
			}
			else if (bot != nullptr) {
				Players[i] = new Bot(*bot);
			}
		}

		Rent_1 = Railroads::Rent_1;
		Rent_2 = Railroads::Rent_2;
		Rent_3 = Railroads::Rent_3;
		Rent_4 = Railroads::Rent_4;

		Single_Multiplier = Utilities::Single_Multiplier;
		Double_Multiplier = Utilities::Double_Multiplier;

	}

	static void PolySpaceCopy(Space* dest, Space* src)
	{
		// figure out which type of space each is and use the respective
		// assignment operator

		Street* streetSrc = dynamic_cast<Street*>(src);
		Railroad* railroadSrc = dynamic_cast<Railroad*>(src);
		Utility* utilitySrc = dynamic_cast<Utility*>(src);
		Action* actionSrc = dynamic_cast<Action*>(src);

		Street* streetDest = dynamic_cast<Street*>(dest);
		Railroad* railroadDest = dynamic_cast<Railroad*>(dest);
		Utility* utilityDest = dynamic_cast<Utility*>(dest);
		Action* actionDest = dynamic_cast<Action*>(dest);

		if ( streetSrc && streetDest ) {
			*streetDest = *streetSrc;
			delete streetSrc;
		}
		else if ( railroadSrc && railroadDest ) {
			*railroadDest = *railroadSrc;
			delete railroadSrc;
		}
		else if ( utilitySrc && utilityDest ) {
			*utilityDest = *utilitySrc;
			delete utilitySrc;
		}
		else if ( actionSrc && actionDest ) {
			*actionDest = *actionSrc;
			delete actionSrc;
		}
	}

	static void PolyPlayerCopy(Player* dest, Player* src)
	{
		// figure out what type of player each is and 
		// use the correct assigmnent operator

		Person* personSrc = dynamic_cast<Person*>(src);
		Bot* botSrc = dynamic_cast<Bot*>(src);

		Person* personDest = dynamic_cast<Person*>(dest);
		Bot* botDest = dynamic_cast<Bot*>(dest);

		if ( personSrc && personDest ) {
			*personDest = *personSrc;
			delete personSrc;
		}
		else if ( botSrc && botDest ) {
			*botDest = *botSrc;
			delete botSrc;
		}
	}

	void RestoreBackup() {

		Monopoly::turn_count = turn_count;

		Bank::money = bankMoney;
		FreeParking::money = fpMoney;

		for (int i = 0; i < NUM_SPACES; i++) {
			PolySpaceCopy(Board::Spaces[i], Spaces[i]);
		}
		delete[] Spaces;

		for (int i = 0; i < Players::NumPlayers; i++) {
			PolyPlayerCopy(Players::Players[i], Players[i]);
		}
		delete[] Players;

		Railroads::Rent_1 = Rent_1;
		Railroads::Rent_2 = Rent_2;
		Railroads::Rent_3 = Rent_3;
		Railroads::Rent_4 = Rent_4;

		Utilities::Single_Multiplier = Single_Multiplier;
		Utilities::Double_Multiplier = Double_Multiplier;

	}

}
