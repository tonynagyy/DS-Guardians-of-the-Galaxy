#pragma once
#include "Army.h"
#include "AlienDrone.h"
#include "AlienMonster.h"
#include "AlienSoldier.h"

class AlienArmy : public Army
{

	LinkedQueue<Unit*> aSoldiersList;
	Array<Unit*> aMonstersList; //for monsters
	DoubleEndedQueue<Unit*> aDronesList;
	bool flag; //flag used in remove Unit to make it easy to remove drones
public:
	AlienArmy(Game *pgame);
	void attack(Army* enemy);
	void addUnit(Unit*);
	Unit* removeUnit(string type); // index for the monster list and the Unit pointer used if type is Drone
};
