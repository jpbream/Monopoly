#pragma once
#include "Property.h"

//type of property
class Railroad : public Property
{
public:

	Railroad();
	Railroad(const Railroad& other);
	virtual Railroad& operator=(const Railroad& other);
	Railroad(int index, const std::string& name, int price, int mortgage);

	void LandOnOwned(Player* const p) override;
	
};

