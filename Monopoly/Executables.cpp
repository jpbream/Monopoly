#include "Executables.h"
#include "Player.h"
#include "Property.h"
#include "CardActions.h"
#include "Actions.h"
#include "Console.h"
#include "Street.h"
#include "Streets.h"
#include "Bank.h"

void DoNothing::PerformAction()
{
	// do nothing
}
int DoNothing::GetPrice()
{
	return 0;
}
std::string DoNothing::ToString()
{
	return "Do Nothing";
}


PayJailBail::PayJailBail(Player* p) : player(p) {}
void PayJailBail::PerformAction()
{
	CardActions::Pay(player, Actions::JAIL_BAIL);
	player->ReleaseFromJail();
}
int PayJailBail::GetPrice()
{
	return Actions::JAIL_BAIL;
}
std::string PayJailBail::ToString()
{
	return "Pay $" + itos(Actions::JAIL_BAIL) + " to get out of jail";
}


GetOutOfJailFree::GetOutOfJailFree(Player* p) : player(p) {}
void GetOutOfJailFree::PerformAction()
{
	CardActions::Pay(player, Actions::JAIL_BAIL);
	player->ReleaseFromJail();
}
int GetOutOfJailFree::GetPrice()
{
	return 0;
}
std::string GetOutOfJailFree::ToString()
{
	return "Use a get out of jail free card";
}


BuyProperty::BuyProperty(Player* pl, Property* pr) : player(pl), property(pr) {}
void BuyProperty::PerformAction()
{
	//make the payment
	player->PayBank(property->PRICE);

	// remove from old owner
	if ( property->GetOwner() != nullptr ) {
		property->GetOwner()->RemoveProperty(property);
	}

	//transfer ownership
	property->SetOwner(player);

	// add property to players list
	player->AddProperty(property);
}
int BuyProperty::GetPrice()
{
	return property->PRICE;
}
Property* BuyProperty::GetProperty()
{
	return property;
}
std::string BuyProperty::ToString()
{
	return "Buy " + property->NAME + " for $" + itos(property->PRICE);
}


SellItem::SellItem(Player* player, SellItem::Items item, Property* property)
	: player(player), item(item), property(property)
{
	if ( item == Items::HOUSE ) {

		Street* street = dynamic_cast<Street*>(property);
		salePrice = (int)(street->GetNeighborhood()->HOUSE_COST * Streets::BUILDING_RESALE_DEPRECIATION);
	}
	else if ( item == Items::HOTEL ) {
		Street* street = dynamic_cast<Street*>(property);
		salePrice = (int)(street->GetNeighborhood()->HOTEL_COST * Streets::BUILDING_RESALE_DEPRECIATION);
	}
	else if ( item == Items::PROPERTY ) {
		salePrice = property->MORTGAGE;
	}
}
void SellItem::PerformAction()
{
	if ( item == Items::HOUSE ) {

		Street* street = dynamic_cast<Street*>(property);
		street->RemoveHouse();
		Bank::PayPlayer(player, salePrice);
	}
	else if ( item == Items::HOTEL ) {
		Street* street = dynamic_cast<Street*>(property);
		street->RemoveHotel();
		Bank::PayPlayer(player, salePrice);
	}
	else if ( item == Items::PROPERTY ) {

		property->SetMortgaged(true);
		property->SetOwner(nullptr);

		// remove the property from the player
		player->RemoveProperty(property);

		Bank::PayPlayer(player, salePrice);
	}
}
int SellItem::GetPrice()
{
	return -salePrice;
}
std::string SellItem::ToString()
{
	if ( item == Items::HOUSE ) {
		Street* street = dynamic_cast<Street*>(property);

		return "Sell a house on " + street->NAME + " for $" + itos(salePrice);
	}
	else if ( item == Items::HOTEL ) {
		Street* street = dynamic_cast<Street*>(property);

		return "Sell a hotel on " + street->NAME + " for $" + itos(salePrice);
	}
	else if ( item == Items::PROPERTY ) {

		return "Mortgage " + property->NAME + " for $" + itos(salePrice);
	}
}
int SellItem::GetSalePrice()
{
	return salePrice;
}
Property* SellItem::GetProperty()
{
	return property;
}
SellItem::Items SellItem::ItemType()
{
	return item;
}


BuyItem::BuyItem(Player* player, BuyItem::Items item, Street* property)
	:
	player(player), item(item), property(property)
{
	if ( item == Items::HOUSE ) {
		buyPrice = property->GetNeighborhood()->HOUSE_COST;
	}
	else if ( item == Items::HOTEL ) {
		buyPrice = property->GetNeighborhood()->HOTEL_COST;
	}
}
void BuyItem::PerformAction()
{
	if ( item == Items::HOUSE ) {

		property->AddHouse();
		player->PayBank(buyPrice);
	}
	else if ( item == Items::HOTEL ) {

		property->AddHotel();
		player->PayBank(buyPrice);
	}
}
int BuyItem::GetPrice()
{
	return buyPrice;
}
std::string BuyItem::ToString()
{
	if ( item == Items::HOUSE ) {

		return "Buy a house on " + property->NAME + " for $" + itos(buyPrice);
	}
	else if ( item == Items::HOTEL ) {

		return "Buy a hotel on " + property->NAME + " for $" + itos(buyPrice);
	}
}
Street* BuyItem::GetProperty()
{
	return property;
}
BuyItem::Items BuyItem::ItemType()
{
	return item;
}