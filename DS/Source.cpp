#include<iostream>
#include <cstdlib>  
#include <time.h> 
#include"ArrayStack.h"
#include"NodeWithPrev.h"
#include"StackADT.h"
#include"DoubleEndedQueue.h"
#include<fstream>
#include "Unit.h"
//#include"Army.h"
#include"Game.h"
//#include"AlienArmy.h"
//#include"EarthArmy.h"
ostream& operator<<(ostream& os, const Unit* item) {
	os << item->getID();  // Print the ID of the unit
	return os;
}
using namespace std;

int main() {

	string key;
	// Open the input file
	fstream InputFile;
	InputFile.open("Test.txt");
	if (!InputFile.is_open()) {
		cerr << "Error: Could not open file 'Test.txt'." << endl;
		return 1; // Exit program on error
	}
	// Create a game object
	Game* pGame = new Game(InputFile);
	int i = 0;
	while (i<50){

		if (InputFile.is_open()) {
			srand(time(0));
			pGame->GenerateArmy();
        }
		cout<< "before start the next timestep"<<endl;
		pGame->print();

		// Start the war
		pGame->StartWar();
        cout << "after start the next timestep" << endl;
		pGame->print();
		cout << "Press 'q' to quit or any other key to continue: ";
		i++;
		cin >> key;

		if (key == "q") {
			break;

		}
		system("CLS");
	}

	// Deallocate memory 
	delete pGame;

	// Close the input file
	InputFile.close();

}
