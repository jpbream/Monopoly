#pragma once
#include "Property.h"

//type of property
class Railroad : public Property
{

protected:
	void LandOnOwned(Player* const p) override;

public:

	Railroad();
	Railroad(const Railroad& other);
	Railroad& operator=(const Railroad& other);
	Railroad(int index, const std::string& name, int price, int mortgage);
	
};

