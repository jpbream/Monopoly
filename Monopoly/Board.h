#pragma once
#include "Space.h"
#include <map>
#include <string>

#define NUM_SPACES 40

//holds all the board spaces as Space pointers
namespace Board {

	//array of board spaces, its spot in the array is its spot on the board
	//to get a space as a lower level class, use dynamic_cast
	extern Space** Spaces;

	//maps the name of a space to its index on the board
	extern std::map<std::string, int> NameToIndexMap;

	//initializes all spaces on the board
	void Init();

	//deletes all spaces on the board
	void Quit();

}
