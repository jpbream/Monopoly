#pragma once
#include "Space.h"
#include "Player.h"

//type of space that makes the player take some action
class Action : public Space
{
public:

	//pointer to the function that completes the action on the player
	void (*action)(Player* const);

	Action();
	Action(const Action& other);
	virtual Action& operator=(const Action& other);

	//must be initialized with a pointer to its action function
	Action(int index, const std::string& name, void (*function)(Player*));

	//called when a player lands on this space
	void LandOn(Player* const p) override;
	
};

