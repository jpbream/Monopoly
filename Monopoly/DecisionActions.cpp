#include "DecisionActions.h"
#include "Player.h"
#include "Actions.h"
#include "CardActions.h"
#include "Bank.h"
#include "Property.h"
#include "Board.h"

//DecisionAction DecisionActions::DoNothing = [](Player* const player) {
//
//};
//
//DecisionAction DecisionActions::PayJailBail = [](Player* const player) {
//
//	CardActions::Pay(player, Actions::JAIL_BAIL);
//	player->ReleaseFromJail();
//
//};
//
//DecisionAction DecisionActions::UseGetOutOfJailFree = [](Player* const player) {
//
//	player->UseGetOutOfJailFree();
//	player->ReleaseFromJail();
//
//};
//
//DecisionAction DecisionActions::BuyProperty = [](Player* const player) {
//
//	//casts players current square to a property
//	Property* const property = dynamic_cast<Property*>(Board::Spaces[player->GetCurrentSquare()]);
//
//	//make the payment
//	player->PayBank(property->PRICE);
//
//	// remove from old owner
//	if ( property->GetOwner() != nullptr ) {
//		property->GetOwner()->RemoveProperty(property);
//	}
//	
//	//transfer ownership
//	property->SetOwner(player);
//
//	// add property to players list
//	player->AddProperty(property);
//
//};