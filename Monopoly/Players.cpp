#include "Players.h"
#include <string>
#include "Person.h"
#include "Bot.h"
#include "Monopoly.h"
#include "Console.h"

int Players::NumPlayers;

Player** Players::Players;

void Players::ManualWalletReset() {

}

void Players::InputPlayers() {
	
	Console::Write("Lets go over who will be playing the game!\n");
	Console::IncreaseIndent();

	Console::Write("How many users will be playing the game (people and bots)? ");
	do {
		Console::Get<int>(1, &NumPlayers);
	} while (NumPlayers > Monopoly::MAX_PLAYERS || NumPlayers < Monopoly::MIN_PLAYERS);

	Console::Write("Lets enter the data for each of the " + itos(NumPlayers) + " players, in the order that they will take turns\n");
	Console::IncreaseIndent();

	Players = new Player*[NumPlayers];

	int numBot = 0;
	for (int i = 1; i <= NumPlayers; ++i) {

		std::string currentPlayer = "Player " + std::to_string(i);
		Console::Write("Is " + currentPlayer + " a person or a bot (p/b)? ");

		char pb;
		Console::Get<char>(1, &pb);

		std::string gamepiece;
		std::string name;

		if (pb == 'p') {

			Console::Write("What is the name of " + currentPlayer + "? ");
			Console::Get<std::string>(1, &name);
			Console::Write("What gamepiece is " + currentPlayer + " using? ");
			Console::Get<std::string>(1, &gamepiece);
			
			Player* p = new Person(name, gamepiece);
			Players[i - 1] = p;

		}
		else {

			name = "Bot " + std::to_string(++numBot);
			Console::Write("What gamepiece is " + currentPlayer + " using? ");
			Console::Get<std::string>(1, &gamepiece);

			Player* b = new Bot(name, gamepiece);
			Players[i - 1] = b;

		}

		if (i != NumPlayers)
			Console::Write("\n");

	}
	Console::DecreaseIndent();
	Console::DecreaseIndent();

	Console::Write("All player information has been entered.\n");
	Console::Write("\n");

}

void Players::Quit() {
	
	for (int i = 0; i < NumPlayers; i++) {
		delete Players[i];
	}
	delete[] Players;

}