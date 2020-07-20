#include "Action.h"
#include "Board.h"
#include <iostream>

Action::Action() : Space(), action(nullptr) {}
Action::Action(const Action& other) : Space(other), action(other.action) {}
Action& Action::operator=(const Action& other)
{
	Space::operator=(other);
	action = other.action;
	return *this;
}

Action::Action(int index, const std::string& name, void(*function)(Player*)) : Space(index, name), action(function)
{

}

void Action::LandOn(Player* const p) {

	//use the member function pointer on the player
	action(p);

}
