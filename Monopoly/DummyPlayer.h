#pragma once
#include "Player.h"
#include <string>

class DummyPlayer : public Player
{
public:
	DummyPlayer(const std::string& name);

	Roll DiceRoll();
	bool ConsiderBuying(Property* property);
	bool ScroungeCash(int amount);
};

