//#include "Wallet.h"
//#include "Bank.h"
//#include "Console.h"
//#include "Players.h"
//
//Wallet::Wallet() {}
//
//void Wallet::Set(int n1, int n5, int n10, int n20, int n50, int n100, int n500) {
//	
//	bill_1 = n1;
//	bill_5 = n5;
//	bill_10 = n10;
//	bill_20 = n20;
//	bill_50 = n50;
//	bill_100 = n100;
//	bill_500 = n500;
//
//}
//
//int Wallet::Total() const {
//
//	return bill_500 * 500 +
//		bill_100 * 100 +
//		bill_50 * 50 +
//		bill_20 * 20 +
//		bill_10 * 10 +
//		bill_5 * 5 +
//		bill_1;
//
//}
//
//LackOfBills Wallet::TransferTo(Wallet& other, int num1, int num5, int num10, 
//						int num20, int num50, int num100, int num500) {
//
//	LackOfBills error;
//
//	if (num500 > bill_500) {
//		error.lackingBills = true;
//		error.num500 = num500 - bill_500;
//	}
//	other.bill_500 += num500;
//	bill_500 -= num500;
//
//	if (num100 > bill_100) {
//		error.lackingBills = true;
//		error.num100 = num100 - bill_100;
//	}
//	other.bill_100 += num100;
//	bill_100 -= num100;
//
//	if (num50 > bill_50) {
//		error.lackingBills = true;
//		error.num50 = num50 - bill_50;
//	}
//	other.bill_50 += num50;
//	bill_50 -= num50;
//
//	if (num20 > bill_20) {
//		error.lackingBills = true;
//		error.num20 = num20 - bill_20;
//	}
//	other.bill_20 += num20;
//	bill_20 -= num20;
//
//	if (num10 > bill_10) {
//		error.lackingBills = true;
//		error.num10 = num10 - bill_10;
//	}
//	other.bill_10 += num10;
//	bill_10 -= num10;
//
//	if (num5 > bill_5) {
//		error.lackingBills = true;
//		error.num5 = num5 - bill_5;
//	}
//	other.bill_5 += num5;
//	bill_5 -= num5;
//
//	if (num1 > bill_1) {
//		error.lackingBills = true;
//		error.num1 = num1 - bill_1;
//	}
//	other.bill_1 += num1;
//	bill_1 -= num1;
//
//	error.totalLacking = error.num500 * 500 + error.num100 * 100 + error.num50 * 50 + error.num20 * 20 + error.num10 * 10 +
//		error.num5 * 5 + error.num1;
//
//	return error;
//
//}
//
//LackOfFunds Wallet::TransferTo(Wallet& other, int amount, Player* const transferer) {
//	
//	LackOfFunds error;
//
//	//check if this wallet can afford the payment
//	if (Total() < amount) {
//		error.lackingFunds = true;
//		error.totalLacking = amount - Total();
//		return error;
//	}
//
//	error.lackingFunds = false;
//
//	//algorithm: try every combination of bills. if we find one that equals amount, we are done.
//	// otherwise, choose combination that is closest to amount and greater than amount
//	// trade in largest bill closest to the difference for its smallest amount of sub-bills
//	//repeat trying every combination and trade ins
//
//	//the number of each bill given to the bank
//	int g500 = 0, g100 = 0, g50 = 0, g20 = 0, g10 = 0, g5 = 0;
//
//	//the number of each bill recieved from the bank
//	int r100 = 0, r50 = 0, r20 = 0, r10 = 0, r5 = 0, r1 = 0;
//
//	Console::Write("{\n");
//	Console::IncreaseIndent();
//
//	//inside of this loop is guaranteed to reach a return
//
//	int numIter = 0;
//	while (true) {
//
//		numIter++;
//		if (numIter > 100000) {
//			std::cout << "aye";
//		}
//
//		//smallest difference between the selected bills total and amount
//		int smallestDiff = 100000000;
//
//		//loop in this order so bigger bills are used first
//		for (int i1 = 0; i1 <= bill_1; i1++) {
//			for (int i5 = 0; i5 <= bill_5; i5++) {
//				for (int i10 = 0; i10 <= bill_10; i10++) {
//					for (int i20 = 0; i20 <= bill_20; i20++) {
//						for (int i50 = 0; i50 <= bill_50; i50++) {
//							for (int i100 = 0; i100 <= bill_100; i100++) {
//								for (int i500 = 0; i500 <= bill_500; i500++) {
//
//									//the amount reached by this combination of bills
//									int reached = i500 * 500 + i100 * 100 + i50 * 50 + i20 * 20 + i10 * 10 + i5 * 5 + i1;
//
//									//only consider this combination if it is >= amount
//									if (reached >= amount) {
//										
//										//have found a combination
//										if (reached == amount) {
//
//											//prompt which bills need to be traded to the bank and what is recieved
//											if (g5 > 0 || g10 > 0 || g20 > 0 || g50 > 0 || g100 > 0 || g500 > 0) {
//												Console::Write("Give the bank:\n");
//												if (g5 > 0) {
//													Console::Write(itos(g5) + " fives, ");
//												}
//												if (g10 > 0) {
//													Console::Write(itos(g10) + " tens, ");
//												}
//												if (g20 > 0) {
//													Console::Write(itos(g20) + " twenties, ");
//												}
//												if (g50 > 0) {
//													Console::Write(itos(g50) + " fifties, ");
//												}
//												if (g100 > 0) {
//													Console::Write(itos(g100) + " one-hundreds, ");
//												}
//												if (g500 > 0) {
//													Console::Write(itos(g500) + " five-hundreds, ");
//												}
//
//												Console::Write("in exchange for:\n");
//
//												if (r1 > 0) {
//													Console::Write(itos(r1) + " ones, ");
//												}
//												if (r5 > 0) {
//													Console::Write(itos(r5) + " fives, ");
//												}
//												if (r10 > 0) {
//													Console::Write(itos(r10) + " tens, ");
//												}
//												if (r20 > 0) {
//													Console::Write(itos(r20) + " twenties, ");
//												}
//												if (r50 > 0) {
//													Console::Write(itos(r50) + " fifties, ");
//												}
//												if (r100 > 0) {
//													Console::Write(itos(r100) + " one-hundreds.");
//												}
//												Console::Write("\n");
//											}
//
//											//perform the transaction
//											other.bill_500 += i500;
//											bill_500 -= i500;
//
//											other.bill_100 += i100;
//											bill_100 -= i100;
//
//											other.bill_50 += i50;
//											bill_50 -= i50;
//
//											other.bill_20 += i20;
//											bill_20 -= i20;
//
//											other.bill_10 += i10;
//											bill_10 -= i10;
//
//											other.bill_5 += i5;
//											bill_5 -= i5;
//
//											other.bill_1 += i1;
//											bill_1 -= i1;
//
//											//prompt which bills to give
//											Console::Write("Give the recipient ");
//											if (i1 > 0) {
//												Console::Write(itos(i1) + " ones, ");
//											}
//											if (i5 > 0) {
//												Console::Write(itos(i5) + " fives, ");
//											}
//											if (i10 > 0) {
//												Console::Write(itos(i10) + " tens, ");
//											}
//											if (i20 > 0) {
//												Console::Write(itos(i20) + " twenties, ");
//											}
//											if (i50 > 0) {
//												Console::Write(itos(i50) + " fifties, ");
//											}
//											if (i100 > 0) {
//												Console::Write(itos(i100) + " one-hundreds, ");
//											}
//											if (i500 > 0) {
//												Console::Write(itos(i500) + " five-hundreds.");
//											}
//											Console::Write("\n");
//
//											Console::DecreaseIndent();
//											Console::Write("}\n");
//
//											return error;
//										}
//
//										//update smallest difference with this combination if necessary
//										if (reached - amount < smallestDiff) {
//											smallestDiff = reached - amount;
//										}
//
//									}
//
//
//								}
//							}
//						}
//					}
//				}
//			}
//		}
//
//		//process is the same for every type of trade in
//
//		//if 5 is the smallest bill larger than the difference
//		// and the wallet has a 5 to trade, or we have recieved one from the bank to trade
//		if (smallestDiff < 5 && (bill_5 > 0 || r5 > 0)) {
//			//trade a 5 for five 1
//
//			//use a recieved bank bill to trade first if we have one to simplify the overall trade
//			if (r5 > 0) {
//				r5--;
//			}
//			else {
//
//				//otherwise trade in one of this wallet's fives
//				bill_5--;
//				g5++;
//			}
//			
//			
//
//			//make sure the bank has atleast 5 ones to make a trade
//			if (Bank::Teller->wallet.bill_1 < 5) {
//
//				//loop through all players
//				for (int p = 0; p < Players::NumPlayers; p++) {
//
//					Player* const player = Players::Players[p];
//					if (player == transferer || transferer == Bank::Teller)
//						continue;
//
//					//this player will give the bank 5 ones in exchange for a 5 if the bank has a five to give
//					if (player->wallet.bill_1 >= 5 && Bank::Teller->wallet.bill_5 > 0) {
//						Console::Write(player->GetDisplayName() + ": give " + Bank::Teller->NAME + "5 ones in exchange for 1 five.\n");
//
//						player->wallet.bill_1 -= 5;
//						Bank::Teller->wallet.bill_5--;
//
//						player->wallet.bill_5++;
//						Bank::Teller->wallet.bill_1 += 5;
//						break;
//
//					}
//					//player will give the bank 10 ones in exchange for a ten if the bank has a ten to give
//					else if (player->wallet.bill_1 >= 10 && Bank::Teller->wallet.bill_10 > 0) {
//						Console::Write(player->GetDisplayName() + ": give " + Bank::Teller->NAME + "10 ones in exchange for 1 ten.\n");
//
//						player->wallet.bill_1 -= 10;
//						Bank::Teller->wallet.bill_10--;
//
//						player->wallet.bill_10++;
//						Bank::Teller->wallet.bill_1 += 10;
//						break;
//					}
//					//player will give the bank 20 ones in exchange for a twenty if the bank has a twenty to give
//					else if (player->wallet.bill_1 >= 20 && Bank::Teller->wallet.bill_20 > 0) {
//						Console::Write(player->GetDisplayName() + ": give " + Bank::Teller->NAME + "20 ones in exchange for 1 twenty.\n");
//
//						player->wallet.bill_1 -= 20;
//						Bank::Teller->wallet.bill_20--;
//
//						player->wallet.bill_20++;
//						Bank::Teller->wallet.bill_1 += 20;
//						break;
//					}
//
//				}
//
//				if (Bank::Teller->wallet.bill_1 < 5) {
//					//unable to compute bill transfer
//					Players::ManualWalletReset();
//					return error;
//				}
//
//			}
//			
//			//update this wallets bill ones and its number of recieved bills
//			bill_1 += 5;
//			r1 += 5;
//
//			Bank::Teller->wallet.bill_5++;
//			Bank::Teller->wallet.bill_1 -= 5;
//			continue;
//			
//		}
//		else if (smallestDiff < 10 && (bill_10 > 0 || r10 > 0)) {
//			//trade a 10 for two 5
//			if (r10 > 0) {
//				r10--;
//			}
//			else {
//				bill_10--;
//				g10++;
//			}
//
//			//make sure the bank has atleast 2 fives to trade
//			if (Bank::Teller->wallet.bill_5 < 2) {
//
//				//loop through all players
//				for (int p = 0; p < Players::NumPlayers; p++) {
//
//					Player* const player = Players::Players[p];
//
//					//if the bank already has 1 five, they only need one more
//					if (Bank::Teller->wallet.bill_5 == 1) {
//
//						//player will give the bank 1 five in exchange for 5 ones if the bank has 5 ones
//						if (player->wallet.bill_5 >= 1 && Bank::Teller->wallet.bill_1 >= 5) {
//							Console::Write(player->GetDisplayName() + ": give " + Bank::Teller->NAME + "1 five in exchange for 5 ones.\n");
//
//							player->wallet.bill_5--;
//							Bank::Teller->wallet.bill_1 -= 5;
//
//							player->wallet.bill_1 += 5;
//							Bank::Teller->wallet.bill_1 += 5;
//							break;
//						}
//
//					}
//
//										
//
//				}
//
//				if (Bank::Teller->wallet.bill_5 < 2) {
//					//unable to compute bill transfer
//					Players::ManualWalletReset();
//					return error;
//				}
//
//			}
//
//			//carry out the trade
//			bill_5 += 2;
//			r5 += 2;
//
//			Bank::Teller->wallet.bill_10++;
//			Bank::Teller->wallet.bill_5 -= 2;
//			continue;
//		}
//		else if (smallestDiff < 20 && (bill_20 > 0 || r20 > 0)) {
//			//trade a 20 for two 10
//			if (r20 > 0) {
//				r20--;
//			}
//			else {
//				bill_20--;
//				g20++;
//			}
//
//			bill_10 += 2;
//			r10 += 2;
//
//			Bank::Teller->wallet.bill_20++;
//			Bank::Teller->wallet.bill_10 -= 2;
//			continue;
//		}
//		else if (smallestDiff < 50 && (bill_50 > 0 || r50 > 0)) {
//			//trade a 50 for two 20 and one 10
//			if (r50 > 0) {
//				r50--;
//			}
//			else {
//				bill_50--;
//				g50++;
//			}
//
//			bill_20 += 2;
//			r20 += 2;
//
//			bill_10++;
//			r10++;
//
//			Bank::Teller->wallet.bill_50++;
//			Bank::Teller->wallet.bill_20 -= 2;
//			Bank::Teller->wallet.bill_10--;
//			continue;
//		}
//		else if (smallestDiff < 100 && (bill_100 > 0 || r100 > 0)) {
//			//trade a 100 for two 50
//			if (r100 > 0) {
//				r100--;
//			}
//			else {
//				bill_100--;
//				g100++;
//			}
//
//			bill_50 += 2;
//			r50 += 2;
//
//			Bank::Teller->wallet.bill_100++;
//			Bank::Teller->wallet.bill_50 -= 2;
//			continue;
//		}
//		else if (smallestDiff < 500 && (bill_500 > 0)) {
//			//trade a 500 for five 100
//			bill_500--;
//			g500++;
//
//			bill_100 += 5;
//			r100 += 5;
//
//			Bank::Teller->wallet.bill_500++;
//			Bank::Teller->wallet.bill_100 -= 5;
//			continue;
//		}
//
//	}
//
//}
//
//void Wallet::Print() {
//
//	std::cout << "Total: " << Total() << "    Ones: " << bill_1 << "    Fives: " << bill_5 << "    Tens: " << bill_10 <<
//		"    Twenties: " << bill_20 << std::endl << "Fifties: " << bill_50 << "    One-Hundreds: " << bill_100 <<
//		"    Five-Hundreds: " << bill_500 << std::endl;
//
//}