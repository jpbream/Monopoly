#pragma once
#include "Property.h"

//type of property
class Utility : public Property
{
protected:
	void LandOnOwned(Player* const p) override;

public:

	Utility();
	Utility(const Utility& other);
	Utility& operator=(const Utility& other);
	Utility(int index, const std::string& name, int price, int mortgage);

};

