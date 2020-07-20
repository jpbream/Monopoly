#include "Board.h"
#include "Street.h"
#include "Railroad.h"
#include "Utility.h"
#include "Action.h"
#include "Actions.h"
#include "StreetGroup.h"
#include "Railroads.h"
#include "Utilities.h"

Space** Board::Spaces;
std::map<std::string, int> Board::NameToIndexMap;

//initialize all the street groups
static StreetGroup brown("BROWN", 2, 50, 50);
static StreetGroup light_blue("LIGHT_BLUE", 3, 50, 50);
static StreetGroup pink("PINK", 3, 100, 100);
static StreetGroup orange("ORANGE", 3, 100, 100);
static StreetGroup red("RED", 3, 150, 150);
static StreetGroup yellow("YELLOW", 3, 150, 150);
static StreetGroup green("GREEN", 3, 200, 200);
static StreetGroup dark_blue("DARK_BLUE", 2, 200, 200);

void Board::Init() {

	//set up all the spaces
	//add streets to their street groups

	Spaces = new Space*[NUM_SPACES];
	Railroads::Railroads = new Railroad*[NUM_RAILROADS];
	Utilities::Utilities = new Utility*[NUM_UTILITIES];

	//go
	Spaces[0] = new Action(0, "GO", Actions::PassGo);

	//mediterranean avenue
	Spaces[1] = new Street(1, "MEDITERRANEAN AVENUE", &brown, 60, 2, 4, 10, 30, 90, 160, 250, 30);

	//community chest 1
	Spaces[2] = new Action(2, "COMMUNITY CHEST 1", Actions::CommunityChest);

	//baltic avenue
	Spaces[3] = new Street(3, "BALTIC AVENUE", &brown, 60, 4, 8, 20, 60, 180, 320, 450, 30);

	brown.streets[0] = (Street*)Spaces[1];
	brown.streets[1] = (Street*)Spaces[3];

	//income tax
	Spaces[4] = new Action(4, "INCOME TAX", Actions::IncomeTax);

	//reading railroad
	Spaces[5] = new Railroad(5, "READING RAILROAD", 200, 100);
	Railroads::Railroads[0] = (Railroad*)Spaces[5];

	//oriental avenue
	Spaces[6] =  new Street(6, "ORIENTAL AVENUE", &light_blue, 100, 6, 12, 30, 90, 270, 400, 550, 50);

	//chance
	Spaces[7] = new Action(7, "CHANCE 1", Actions::Chance);

	//vermont avenue
	Spaces[8] = new Street(8, "VERMONT AVENUE", &light_blue, 100, 6, 12, 30, 90, 270, 400, 550, 50);

	//connecticut avenue
	Spaces[9] = new Street(9, "CONNECTICUT AVENUE", &light_blue, 120, 8, 16, 40, 100, 300, 450, 600, 60);

	light_blue.streets[0] = (Street*)Spaces[6];
	light_blue.streets[1] = (Street*)Spaces[8];
	light_blue.streets[2] = (Street*)Spaces[9];

	//jail
	Spaces[10] = new Action(10, "JAIL", Actions::Jail);

	//st charles place
	Spaces[11] = new Street(11, "ST. CHARLES PLACE", &pink, 140, 10, 20, 50, 150, 450, 625, 750, 70);

	//electric company
	Spaces[12] = new Utility(12, "ELECTRIC COMPANY", 150, 75);
	Utilities::Utilities[0] = (Utility*)Spaces[12];

	//states avenue
	Spaces[13] = new Street(13, "STATES AVENUE", &pink, 140, 10, 20, 50, 150, 450, 625, 750, 70);

	//virginia avenue
	Spaces[14] = new Street(14, "VIRGINIA AVENUE", &pink, 160, 12, 24, 60, 180, 500, 700, 900, 80);

	pink.streets[0] = (Street*)Spaces[11];
	pink.streets[1] = (Street*)Spaces[13];
	pink.streets[2] = (Street*)Spaces[14];

	//pennsylvania railroad
	Spaces[15] = new Railroad(15, "PENNSYLVANIA RAILROAD", 200, 100);
	Railroads::Railroads[1] = (Railroad*)Spaces[15];

	//st james place
	Spaces[16] = new Street(16, "ST. JAMES PLACE", &orange, 180, 14, 28, 70, 200, 550, 750, 950, 90);

	//community chest 2
	Spaces[17] = new Action(17, "COMMUNITY CHEST 2", Actions::CommunityChest);

	//tennessee avenue
	Spaces[18] = new Street(18, "TENNESSEE AVENUE", &orange, 180, 14, 28, 70, 200, 550, 750, 950, 90);

	//new york avenue
	Spaces[19] = new Street(19, "NEW YORK AVENUE", &orange, 200, 16, 32, 80, 220, 600, 800, 1000, 100);

	orange.streets[0] = (Street*)Spaces[16];
	orange.streets[1] = (Street*)Spaces[18];
	orange.streets[2] = (Street*)Spaces[19];

	//free parking
	Spaces[20] = new Action(20, "FREE PARKING", Actions::FreeParking);

	//kentucky avenue
	Spaces[21] = new Street(21, "KENTUCKY AVENUE", &red, 220, 18, 36, 90, 250, 700, 875, 1050, 110);

	//chance 2
	Spaces[22] = new Action(22, "CHANCE 2", Actions::Chance);

	//indiana avenue
	Spaces[23] = new Street(23, "INDIANA AVENUE", &red, 220, 18, 36, 90, 250, 700, 875, 1050, 110);

	//illinois avenue
	Spaces[24] = new Street(24, "ILLINOIS AVENUE", &red, 240, 20, 40, 100, 300, 750, 925, 1100, 120);

	red.streets[0] = (Street*)Spaces[21];
	red.streets[1] = (Street*)Spaces[23];
	red.streets[2] = (Street*)Spaces[24];

	//b. & o. railroad
	Spaces[25] = new Railroad(25, "B. & O. RAILROAD", 200, 100);
	Railroads::Railroads[2] = (Railroad*)Spaces[25];

	//atlantic avenue
	Spaces[26] = new Street(26, "ATLANTIC AVENUE", &yellow, 260, 22, 44, 110, 330, 800, 975, 1150, 130);

	//ventnor avenue
	Spaces[27] = new Street(27, "VENTNOR AVENUE", &yellow, 260, 22, 44, 110, 330, 800, 975, 1150, 130);

	//water works
	Spaces[28] = new Utility(28, "WATER WORKS", 150, 75);
	Utilities::Utilities[1] = (Utility*)Spaces[28];

	//marvin gardens
	Spaces[29] = new Street(29, "MARVIN GARDENS", &yellow, 280, 24, 48, 120, 360, 850, 1025, 1200, 140);

	yellow.streets[0] = (Street*)Spaces[26];
	yellow.streets[1] = (Street*)Spaces[27];
	yellow.streets[2] = (Street*)Spaces[29];

	//go to jail
	Spaces[30] = new Action(30, "GO TO JAIL", Actions::GoToJail);

	//pacific avenue
	Spaces[31] = new Street(31, "PACIFIC AVENUE", &green, 300, 26, 52, 130, 390, 900, 1100, 1275, 150);

	//north carolina avenue
	Spaces[32] = new Street(32, "NORTH CAROLINA AVENUE", &green, 300, 26, 52, 130, 390, 900, 1100, 1275, 150);

	//community chest 3
	Spaces[33] = new Action(33, "COMMUNITY CHEST 3", Actions::CommunityChest);

	//pennsylvania avenue
	Spaces[34] = new Street(34, "PENNSYLVANIA AVENUE", &green, 320, 28, 56, 150, 450, 1000, 1200, 1400, 160);

	green.streets[0] = (Street*)Spaces[31];
	green.streets[1] = (Street*)Spaces[32];
	green.streets[2] = (Street*)Spaces[34];

	//short line
	Spaces[35] = new Railroad(35, "SHORT LINE", 200, 100);
	Railroads::Railroads[3] = (Railroad*)Spaces[35];

	//chance 3
	Spaces[36] = new Action(36, "CHANCE 3", Actions::Chance);

	//park place
	Spaces[37] = new Street(37, "PARK PLACE", &dark_blue, 350, 35, 70, 175, 500, 1100, 1300, 1500, 175);

	//luxury tax
	Spaces[38] = new Action(38, "LUXURY TAX", Actions::LuxuryTax);

	//boardwalk
	Spaces[39] = new Street(39, "BOARDWALK", &dark_blue, 400, 50, 100, 200, 600, 1400, 1700, 2000, 200);

	dark_blue.streets[0] = (Street*)Spaces[37];
	dark_blue.streets[1] = (Street*)Spaces[39];

	// populate the name to index map
	for ( int i = 0; i < NUM_SPACES; ++i ) {

		std::string name = Spaces[i]->NAME;
		int index = Spaces[i]->INDEX;

		Board::NameToIndexMap.emplace(name, index);
	}

}

//spaces is an array of pointers so a 2d loop will delete everything
void Board::Quit() {

	for (int i = 0; i < NUM_SPACES; i++) {
		if (Spaces[i] != nullptr) {
			delete Spaces[i];
		}
	}
	delete[] Spaces;

}