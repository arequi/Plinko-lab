/* Sarah Gonzalez, section 1, sarahg.3545@gmail.com
*Description: Simulating the game of Plinko to compute average winnings based on where chips are dropped. Users input
*numbers to determine options, number of chips, and slot locations.
*Developed in Visual Studio.

*Test Case 1:
*Input: 2, 4, 6, 5
*Expected Output: $2100.00, $525.00, "Goodbye!"
*Result: Passed

*Test Case 2:
*Input: -1, 1, 2, 5
*Expected Output: [2.0, 1.5, 1.0, 1.5, 2.0, 1.5, 1.0, 1.5, 1.0, 1.5, 2.0, 1.5, 2.0], $1000.00, "Goodbye!"
*Result: Passed

*Test Case 3:
*Input: -1, 8, 2, 4, 6, 5
*Expected Output: $2100.00, $525.00, "Goodbye!"
*/

#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include<limits>
using namespace std;


void PrintMenu(int menuChoice) {
	const int SINGLE_OPTION = 1;
	const int MULTIPLE_OPTION = 2;
	const int MENU_OPTION = 4;
	const int QUIT_OPTION = 5;

	cout << endl;
	cout << "Menu: Please select one of the following options:" << endl << endl;
	cout << SINGLE_OPTION << " - Drop a single Chip into one slot" << endl;
	cout << MULTIPLE_OPTION << " - Drop multiple chips into one slot" << endl;
	cout << MENU_OPTION << " - Show the options menu" << endl;
	cout << QUIT_OPTION << " - Quit the program" << endl;
	cout << endl;

	return;
}

int GetMenuOption() {
	int menuChoice = 0;
	const int SINGLE_OPTION = 1;
	const int MENU_OPTION = 4;
	const int QUIT_OPTION = 5;

	cin >> menuChoice;
	do {
		if (cin.fail() || menuChoice < SINGLE_OPTION || menuChoice > QUIT_OPTION) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << endl;
			cout << "Invalid selection. Enter " << MENU_OPTION << " to see options." << endl << endl;
			cout << "Enter your selection now: ";
			cin >> menuChoice;
		}
	} while (menuChoice < SINGLE_OPTION || menuChoice > QUIT_OPTION);
	return menuChoice;
}

double ComputeWinnings(int slotLocation) {
	double rewardPrize = 0;
	const double PRIZE_REWARD[7] = { 300.00, 200.00, -600.42, 20000.00, 0.01, 800.00, -1400.00 };
	const int SLOT_MINIMUM = 0;
	const int SLOT_MAXIMUM = 6;

	if (slotLocation == SLOT_MINIMUM) {
		rewardPrize = PRIZE_REWARD[0];
	}
	else if (slotLocation == 1) {
		rewardPrize = PRIZE_REWARD[1];
	}
	else if (slotLocation == 2) {
		rewardPrize = PRIZE_REWARD[2];
	}
	else if (slotLocation == 3) {
		rewardPrize = PRIZE_REWARD[3];
	}
	else if (slotLocation == 4) {
		rewardPrize = PRIZE_REWARD[4];
	}
	else if (slotLocation == 5) {
		rewardPrize = PRIZE_REWARD[5];
	}
	else if (slotLocation == SLOT_MAXIMUM) {
		rewardPrize = PRIZE_REWARD[6];
	}

	return rewardPrize;
}

int CheckSlotNumber() {
	int slot = 0;
	const int SLOT_MINIMUM = 0;
	const int SLOT_MAXIMUM = 8;

	cin >> slot;
	while (cin.fail() || (slot < SLOT_MINIMUM) || (slot > SLOT_MAXIMUM)) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << endl << "Invalid slot." << endl << endl;
		cout << "Which slot do you want to drop the chip in (" << SLOT_MINIMUM << "-" << SLOT_MAXIMUM << ")?" << endl << endl;
		cin >> slot;
	}
	return slot;
}

double SingleChipOption(int menuChoice, int singleSlot) {
	double randomChoice = 0.0;
	const int SLOT_MINIMUM = 0;
	const int SLOT_MAXIMUM = 6;
	const int SINGLE_OPTION = 1;
	double slotLocation = 0.0;
	double rewardPrize = 0.0;
	const int PATH_DECIMAL = 1;
	const int NUMBER_OF_PEGS = 18;
	const int LESS_PEGS = 17;
	const int RANDOM_CHANCE = 2;
	const double RANDOM_OFFSET = 0.5;
	const double ZERO_RESULT = 0.5;
	const double EIGHT_RESULT = 5.5;
	const int RANDOM_NUMBER = 1;

	if (menuChoice == SINGLE_OPTION) {
		cout << "Path: [";
	}
	if ((singleSlot >= SLOT_MINIMUM) && (singleSlot <= SLOT_MAXIMUM)) {
		slotLocation = singleSlot;
		if (menuChoice == SINGLE_OPTION) {
			cout << fixed << setprecision(PATH_DECIMAL) << slotLocation << ", ";
		}
		for (int i = 0; i < NUMBER_OF_PEGS; ++i) {
			if ((slotLocation > SLOT_MINIMUM) && (slotLocation < SLOT_MAXIMUM)) {
				randomChoice = rand() % RANDOM_CHANCE;
				if (randomChoice < RANDOM_NUMBER) {
					slotLocation = slotLocation - RANDOM_OFFSET;
				}
				else {
					slotLocation = slotLocation + RANDOM_OFFSET;
				}
			}
			else if (slotLocation == SLOT_MINIMUM) {
				slotLocation = ZERO_RESULT;
			}
			else {
				slotLocation = EIGHT_RESULT;
			}
			if (menuChoice == SINGLE_OPTION) {
				if (i < LESS_PEGS) {
					cout << fixed << setprecision(PATH_DECIMAL) << slotLocation << ", ";
				}
				else {
					cout << fixed << setprecision(PATH_DECIMAL) << slotLocation;
				}
			}
		}
		rewardPrize = ComputeWinnings(slotLocation);
	}
	if (menuChoice == SINGLE_OPTION) {
		cout << "]" << endl;
	}
	return rewardPrize;
}

int GetChipNumber() {
	int chipNumber = 0;
	const int IGNORE_VAL = 100;
	const int CHIP_MINIMUM = 0;

	cin >> chipNumber;
	while (cin.fail() || (chipNumber <= CHIP_MINIMUM)) {
		cin.clear();
		cin.ignore(IGNORE_VAL, '\n');
		cout << "Invalid number of chips." << endl << endl;
		cout << "How many chips do you want to drop (>" << CHIP_MINIMUM << ")?";
		cin >> chipNumber;
	}
	return chipNumber;
}

void MultipleChipOption(int menuChoice, int chipNumber, int multipleSlot) {
	double slotLocation = 0.0;
	double randomChoice = 0.0;
	double totalWinnings = 0.0;
	double average = 0.0;
	const int SLOT_MINIMUM = 0;
	const int SLOT_MAXIMUM = 6;
	const int NUMBER_OF_PEGS = 18;
	const int RANDOM_CHANCE = 2;
	const double RANDOM_OFFSET = 0.5;
	const int DECIMAL_POINT = 2;
	const int RANDOM_NUMBER = 1;
	const double ZERO_RESULT = 0.5;
	const double EIGHT_RESULT = 5.5;
	const int MULTIPLE_OPTION = 2;
	const int ALL_SLOTS = 3;

	if ((multipleSlot >= SLOT_MINIMUM) && (multipleSlot <= SLOT_MAXIMUM)) {
		slotLocation = multipleSlot;

		for (int i = 0; i < chipNumber; ++i) {
			totalWinnings += SingleChipOption(menuChoice, slotLocation);
		}
		cout << fixed << setprecision(DECIMAL_POINT) << "Total Winnings on ";
		if (menuChoice == MULTIPLE_OPTION) {
			cout << chipNumber << " chips: $" << totalWinnings << endl;
		}
		else if (menuChoice == ALL_SLOTS) {
			cout << "slot " << (int)slotLocation << " chips: " << totalWinnings << endl;
		}
		average = totalWinnings / chipNumber;
		if (menuChoice == MULTIPLE_OPTION) {
			cout << fixed << setprecision(DECIMAL_POINT) << "Average winnings per chip: $" << average << endl << endl;
		}
		else {
			cout << fixed << setprecision(DECIMAL_POINT) << "Average winnings per chip: " << average << endl << endl;
		}
		totalWinnings = 0;
	}
}

int main() {
	int menuChoice = 0;
	const int SINGLE_OPTION = 1;
	const int MULTIPLE_OPTION = 2;
	const int ALL_SLOTS = 3;
	const int MENU_OPTION = 4;
	const int QUIT_OPTION = 5;
	const int RANDOM_SEED = 42;
	const int SLOT_MINIMUM = 0;
	const int SLOT_MAXIMUM = 6;
	const int CHIP_MINIMUM = 0;
	srand(RANDOM_SEED);
	int chipNumber = 0;
	int multipleSlot = 0;
	int singleSlot = 0;
	double rewardPrize = 0;
	const int DECIMAL_POINT = 2;

	cout << "Welcome to the Plinko simulator! Enter 4 to see options." << endl << endl;
	do {
		cout << "Enter your selection now: ";
		menuChoice = GetMenuOption();
		if (menuChoice == SINGLE_OPTION) {
			cout << endl;
			cout << "*** Drop a single chip ***" << endl << endl;
			cout << "Which slot do you want to drop the chip in (" << SLOT_MINIMUM << "-" << SLOT_MAXIMUM << ")?";
			singleSlot = CheckSlotNumber();
			cout << "*** Dropping chip into slot " << singleSlot << " ***" << endl;
			rewardPrize = SingleChipOption(menuChoice, singleSlot);
			cout << fixed << setprecision(DECIMAL_POINT) << "Winnings: $" << rewardPrize << endl;
		}
		if (menuChoice == MULTIPLE_OPTION) {
			cout << endl;
			cout << "*** Drop multiple chips ***" << endl << endl;
			cout << "How many chips do you want to drop (>" << CHIP_MINIMUM << ")?" << endl;
			chipNumber = GetChipNumber();
			cout << endl;
			cout << "Which slot do you want to drop the chip in (" << SLOT_MINIMUM << "-" << SLOT_MAXIMUM << ")?";
			multipleSlot = CheckSlotNumber();
			MultipleChipOption(menuChoice, chipNumber, multipleSlot);
		}
		if (menuChoice == ALL_SLOTS) {
			cout << "*** Sequentially drop multiple chips ***" << endl << endl;
			cout << "How many chips do you want to drop (>" << CHIP_MINIMUM << ")?" << endl;
			chipNumber = GetChipNumber();
			for (int i = SLOT_MINIMUM; i <= SLOT_MAXIMUM; ++i) {
				MultipleChipOption(menuChoice, chipNumber, i);
			}
		}
		if (menuChoice == MENU_OPTION) {
			PrintMenu(menuChoice);
		}
	} while (menuChoice != QUIT_OPTION);

	if (menuChoice == QUIT_OPTION) {
		cout << endl << "Goodbye!";
	}
	system("pause");
	return 0;
}

