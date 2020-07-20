#pragma once
#include <string>

class Player;

//base class for a square on the board
class Space
{

public:

	//the 0 based index of the space starting at GO
	const int INDEX;

	//the text name of the space
	const std::string NAME;

	Space();
	Space(const Space& other);
	virtual Space& operator=(const Space& other);

	Space(int index, const std::string& name);

	//action to take when the space is landed on
	virtual void LandOn(Player* const player) = 0;

};

