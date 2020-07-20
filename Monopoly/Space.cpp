#include "Space.h"
#include "Board.h"

#include <memory>

Space::Space() : INDEX(0), NAME("") {}
Space::Space(const Space& other) : INDEX(other.INDEX), NAME(other.NAME) {}
Space::Space(int index, const std::string& name) : INDEX(index), NAME(name) {}

Space& Space::operator=(const Space& other)
{
	// need to use this hack because the variables are const
	*(int*)&INDEX = other.INDEX;
	*(std::string*)& NAME = other.NAME;
	return *this;
}

