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
#include <locale>
#include <codecvt>
#include <Windows.h>
//#include"AlienArmy.h"
//#include"EarthArmy.h"
ostream& operator<<(ostream& os, const Unit* item) {
	os << item->getID();  // Print the ID of the unit
	if (item->getType() == "ES") {
		if(item->getInfectionStatus() == true)
			os << " infected ";
	}
	return os;
}
using namespace std;

int main() {

	string key;
	string mode;
	string restart="y";
	string fileName;
	// Open the input file
	fstream InputFile;
	cout << "Please enter the name of the input file: ";

	cin >> fileName;

	string temp = "inputs/" + fileName + ".txt";

	InputFile.open(temp);

	if (!InputFile.is_open()) {
		cerr << "Error: Could not open file " << fileName  << endl;
		return 1; // Exit program on error
	}
	// Create a game object
	Game* pGame = new Game(InputFile, fileName);
	bool flag = true;

	cout << endl;
	cout << endl;
	cout << "\033[1;38;5;12m";
	cout << R"(
				____                     _ _                 
				/ ___|_   _  __ _ _ __ __| (_) __ _ _ __  ___ 
				| |  _| | | |/ _` | '__/ _` | |/ _` | '_ \/ __|
				| |_| | |_| | (_| | | | (_| | | (_| | | | \__ \
				\____|\__,_|\__,_|_|  \__,_|_|\__,_|_| |_|___/
					____                                      
				____  / __/                                      
				/ __ \/ /_                                        
				/ /_/ / __/                                        
				\____/_/_            ______      __                
				/ /_/ /_  ___     / ____/___ _/ /___ __  ____  __
				/ __/ __ \/ _ \   / / __/ __ `/ / __ `/ |/_/ / / /
				/ /_/ / / /  __/  / /_/ / /_/ / / /_/ />  </ /_/ / 
				\__/_/ /_/\___/   \____/\__,_/_/\__,_/_/|_|\__, /  
									/____/   

			)" << endl;
	cout << "\033[0m";

	Sleep(2000);
		
	cout << "\033[1;44mdo you need Silent Mode? (y/n)\033[0m" << endl;
	cin >> mode;

	system("CLS");
	if (mode == "y") {
		cout << "Silent Mode is on" << endl;
		cout <<"Simulation Starts Now"<<endl;
	}


	while (flag){
		if (InputFile.is_open()) {
			//srand(time(0));
			pGame->GenerateArmy();
		}
		if (mode == "n") {
			cout << "before start the next timestep" << endl;
			pGame->print();
			// Start the war
			flag = pGame->StartWar();
			cout << "after start the next timestep" << endl;
			if(flag)
			pGame->print();
			cout << "Press 'q' to quit or any other key to continue: ";
				
			cin >> key;
			if (key == "q") {
				break;
			}
			/*if(flag)
			system("CLS");*/
		}
		else {
			flag = pGame->StartWar();
		}
	}
	if(mode == "y")
		cout << "Simulation Ends , Output file is created" << endl;

	InputFile.close();// Close the input file

	cout <<"\n\n";
	cout << "Do you want to play again? (y/n)" << endl;
	cout <<"\n\n";
	cin >> restart;
// Deallocate memory 
	delete pGame;

	

}
