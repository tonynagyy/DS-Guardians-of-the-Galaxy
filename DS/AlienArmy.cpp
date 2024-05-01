#include "AlienArmy.h"
#include "Game.h"


AlienArmy::AlienArmy(Game* pGame): Army(pGame)
{
	flag = 1; // so first remove for drones will remove the last one 
}

void AlienArmy::attack(Army* enemy,int timestep)
{
	Unit* EarthUnit;
	Unit* AlienUnit;
	/* Pointers for printing the fighting units*/
	AS_Attack=nullptr;
	AM_Attack=nullptr;
	AD_Attack=nullptr;
	AD2_Attack=nullptr;
	AS_attacking_list=new LinkedQueue<Unit*>;
	AM_attacking_list=new LinkedQueue<Unit*>;
	AD_attacking_list=new LinkedQueue<Unit*>;
	AD2_attacking_list=new LinkedQueue<Unit*>;
	/*Here Alien Soldier Will attack Earth Soldiers Depend on its attack capacity*/
	if (!aSoldiersList.isEmpty()) {
		aSoldiersList.peek(AlienUnit);
		LinkedQueue<Unit*> SoldierTemp;
		AS_Attack=AlienUnit;
		/*First we will get the soldiers that will be attacked*/
		for (int i = 0;i < AlienUnit->getAttackCapacity();i++) {
			EarthUnit = enemy->removeUnit("ES");
			if(EarthUnit == nullptr) break;
			SoldierTemp.enqueue(EarthUnit);

		}
		/* then we will start to attack them */
		int loopCount = SoldierTemp.getCount();
		for (int i = 0;i < loopCount ;i++) {
			SoldierTemp.dequeue(EarthUnit);

			if (!EarthUnit) break;

			EarthUnit->setfatime(timestep);
			AlienUnit->attack(EarthUnit);
			AS_attacking_list->enqueue(EarthUnit);
			if (EarthUnit->getHealth() <= 0)  // after attack i have to check is the soldier dead or not 
			{
				pGame->AddToKilled(EarthUnit);
			}
			else {
				enemy->addUnit(EarthUnit);
			}
		}
	}

	/*Here Alien Monster Will attack both tanks and Earth Soldiers Depend on its attack capacity*/

	if (!aMonstersList.isEmpty()) {

		aMonstersList.Remove(AlienUnit);
		AM_Attack=AlienUnit;
		LinkedQueue<Unit*> enemyTemp;

		int tankCapacity = AlienUnit->getAttackCapacity() / 2;
		int soldierCapacity = AlienUnit->getAttackCapacity() - tankCapacity;

		for (int i = 0; i < AlienUnit->getAttackCapacity(); i++) {

			if (enemyTemp.getCount() < tankCapacity) {
				EarthUnit = enemy->removeUnit("ET");

				if (EarthUnit == nullptr) {
					tankCapacity = 0;
					soldierCapacity = AlienUnit->getAttackCapacity() - i;
				}
				else {
					enemyTemp.enqueue(EarthUnit);
				}
			}
			else {
				EarthUnit = enemy->removeUnit("ES");
				if(EarthUnit == nullptr) break;
				enemyTemp.enqueue(EarthUnit);
			}
		}
        int loopCount = enemyTemp.getCount();
		for (int i = 0; i < loopCount; i++) {
			enemyTemp.dequeue(EarthUnit);

			if (!EarthUnit) break;

			EarthUnit->setfatime(timestep);

			AlienUnit->attack(EarthUnit);
			AM_attacking_list->enqueue(EarthUnit);
			if (EarthUnit->getHealth() <= 0)
			{
				pGame->AddToKilled(EarthUnit);
			}
			else {
				enemy->addUnit(EarthUnit);
			}
		}

		aMonstersList.AddElement(AlienUnit);

	}

	if (!aDronesList.isEmpty()) {
		Unit* secAlienUnit;
		aDronesList.dequeue(AlienUnit);
		AD_Attack=AlienUnit;
		aDronesList.RearDequeue(secAlienUnit);
		AD2_Attack=secAlienUnit;
		LinkedQueue<Unit*> enemyTemp;

		if (AlienUnit != nullptr && secAlienUnit != nullptr) {
			int firtankattacked = AlienUnit->getAttackCapacity()/2;
			int firgunneryattacked = AlienUnit->getAttackCapacity() - firtankattacked;
			int sectankattacked = secAlienUnit->getAttackCapacity()/2;
			int secgunneryattacked = secAlienUnit->getAttackCapacity() - sectankattacked;

			/////////first Drone////////////

			for (int i = 0; i < AlienUnit->getAttackCapacity(); i++) {
				bool isTankEmpty = false;
				if (i < firtankattacked) {
					EarthUnit = enemy->removeUnit("ET");
					if (EarthUnit == nullptr) {
						firtankattacked = 0;
						firgunneryattacked = AlienUnit->getAttackCapacity() - i;
						isTankEmpty = true;
					}
					else {
						enemyTemp.enqueue(EarthUnit);
					}

				}
				else {
					EarthUnit = enemy->removeUnit("EG");

					if (EarthUnit == nullptr) {
						if (!isTankEmpty) {
							firtankattacked = AlienUnit->getAttackCapacity() - i;
							firgunneryattacked = 0;
						}
						else {
							break;
						}
					}
					else {
						enemyTemp.enqueue(EarthUnit);
					}
				}
			}
			int loopCount = enemyTemp.getCount();
			for (int i = 0; i < loopCount; i++) {
				enemyTemp.dequeue(EarthUnit);

				if (!EarthUnit) break;
				EarthUnit->setfatime(timestep);

				AlienUnit->attack(EarthUnit);
				AD_attacking_list->enqueue(EarthUnit);
				if (EarthUnit->getHealth() <= 0)  // after attack i have to check is the Monster dead or not 
				{
					pGame->AddToKilled(EarthUnit);
				}
				else {
					enemy->addUnit(EarthUnit);
				}
			}
			
			///////////////Now second Drone//////////////////////

			for (int i = 0; i < secAlienUnit->getAttackCapacity(); i++) {
				bool isTankEmpty = false;
				if (i < sectankattacked) {
					EarthUnit = enemy->removeUnit("ET");
					if (EarthUnit == nullptr) {
						sectankattacked = 0;
						secgunneryattacked = secAlienUnit->getAttackCapacity() - i;
						isTankEmpty = true;
					}
					else {
						enemyTemp.enqueue(EarthUnit);
					}

				}
				else {
					EarthUnit = enemy->removeUnit("EG");

					if (EarthUnit == nullptr) {
						if (!isTankEmpty) {
							sectankattacked = AlienUnit->getAttackCapacity() - i;
							secgunneryattacked = 0;
						}
						else {
							break;
						}
					}
					else {
						enemyTemp.enqueue(EarthUnit);
					}
				}
			}
			int loopCount1 = enemyTemp.getCount();
			for (int i = 0; i < loopCount1; i++) {
				enemyTemp.dequeue(EarthUnit);

				if (!EarthUnit) break;

				EarthUnit->setfatime(timestep);
				secAlienUnit->attack(EarthUnit);
				AD2_attacking_list->enqueue(EarthUnit);
				if (EarthUnit->getHealth() <= 0)  // after attack i have to check is the Monster dead or not 
				{
					pGame->AddToKilled(EarthUnit);
				}
				else {
					enemy->addUnit(EarthUnit);
				}
			}
			
		}

		if (AlienUnit)
			aDronesList.enqueue(AlienUnit);
		if (secAlienUnit)
			aDronesList.enqueue(secAlienUnit);
	}
}

void AlienArmy::addUnit(Unit* AlienUnit)
{
	if (dynamic_cast<AlienSoldier*>(AlienUnit)) {
		aSoldiersList.enqueue(AlienUnit);
	}
	else if (dynamic_cast<AlienMonster*>(AlienUnit)) {
		aMonstersList.AddElement(AlienUnit);
	}
	else if (dynamic_cast<AlienDrone*>(AlienUnit)) {
		aDronesList.enqueue(AlienUnit);
	}
}

Unit* AlienArmy::removeUnit(string type)
{
	if (type == "AS") {
		if (!aSoldiersList.dequeue(AlienUnit)) {
			AlienUnit = nullptr;
		}
	}
	else if (type == "AM") {

		if (aMonstersList.getCount() != 0) {
			if (!aMonstersList.Remove(AlienUnit)) {
				AlienUnit = nullptr;
			}
		}

		else return nullptr;
		
	}

	else if (type == "AD") {

		bool res;

		if (flag) {
			res = aDronesList.dequeue(AlienUnit);
		}
		else {
			res = aDronesList.RearDequeue(AlienUnit);
		}

		if (!res) {
			AlienUnit = nullptr;
		}
		else {
			flag = !flag;
		}
	}
	return AlienUnit;
}
int AlienArmy::getSoldiersCount()
{
	return aSoldiersList.getCount();
}

void AlienArmy::printArmy()
{
	std::cout << "====================== Alien Army Alive Units ====================== " << endl;
	std::cout << aSoldiersList.getCount() << " AS ";
	aSoldiersList.print();
	std::cout << aMonstersList.getCount() << " AM ";
	aMonstersList.print();
	std::cout << aDronesList.getCount() << " AD ";
	aDronesList.print();

	std::cout << endl;


}

void AlienArmy::printFightingUnits()
{
	if (AS_Attack && !AS_attacking_list->isEmpty()) {
		std::cout << "AS " << AS_Attack->getID() << " Shots ";
		AS_attacking_list->print();
	}
	
	if (AM_Attack && !AM_attacking_list->isEmpty()) {
		std::cout << "AM " << AM_Attack->getID() << " Shots ";
		AM_attacking_list->print();
	}
	
	if (AD_Attack && !AD_attacking_list->isEmpty()) {
		std::cout << "AD " << AD_Attack->getID() << " Shots ";
		AD_attacking_list->print();
	}
	if (AD2_Attack && !AD2_attacking_list->isEmpty()) {
		std::cout << "AD " << AD2_Attack->getID() << " Shots ";
		AD2_attacking_list->print();
	}

	delete AS_attacking_list;
	delete AM_attacking_list;
	delete AD_attacking_list;
	delete AD2_attacking_list;
	AS_attacking_list = nullptr;
	AM_attacking_list = nullptr;
	AD_attacking_list = nullptr;
	AD2_attacking_list = nullptr;
	
	
}
		
