#pragma once
#include "Property.h"

//type of property
class Utility : public Property
{
public:

	Utility();
	Utility(const Utility& other);
	virtual Utility& operator=(const Utility& other);

	Utility(int index, const std::string& name, int price, int mortgage);

	void LandOnOwned(Player* const p) override;

};

