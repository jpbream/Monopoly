//#pragma once
//#include "PaymentErrors.h"
//
//class Player;
//
////holds the number of each type of bill a player has
//class Wallet {
//
//public:
//	int bill_1 = 0;
//	int bill_5 = 0;
//	int bill_10 = 0;
//	int bill_20 = 0;
//	int bill_50 = 0;
//	int bill_100 = 0;
//	int bill_500 = 0;
//	
//	Wallet();
//
//	//sets the state of the wallet
//	void Set(int n1, int n5, int n10, int n20, int n50, int n100, int n500);
//
//	//returns the total amount of cash in this wallet
//	int Total() const;
//
//	//returns if this wallet has enough money to complete the transfer to the other wallet
//	LackOfFunds TransferTo(Wallet& other, int amount, Player* const transferer);
//	LackOfBills TransferTo(Wallet& other, int num_1, int num_5, int num_10, int num_20, int num_50, int num_100, int num_500);
//
//	void Print();
//
//};
