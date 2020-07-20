#include "Monopoly.h"
#include "Dice.h"
#include "Players.h"
#include "Actions.h"
#include "Bank.h"
#include "Backup.h"
#include "Console.h"

int main() {

	Console::Write("Hello! Press Enter to begin\n");
	Console::Pause();

	Monopoly::Init();

	Monopoly::InputSettings();
	Players::InputPlayers();

	Console::Write("START OF GAME----------------------------------------------------------------------\n\n");

	while (!Monopoly::ResolveGame()) {
		Monopoly::RunTurn();
	}
	Console::Write("END OF GAME----------------------------------------------------------------------\n\n");

	Console::Write("Thanks for playing, press Enter to quit.");
	Console::Pause();

	Monopoly::Quit();
	return 0;
}