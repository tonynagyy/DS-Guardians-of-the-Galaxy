#include "AlienArmy.h"
#include "Game.h"


AlienArmy::AlienArmy(Game* pGame): Army(pGame)
{
	flag = 1; // so first remove for drones will remove the last one 
}

void AlienArmy::attack(Army* enemy)
{
	Unit* EarthUnit;
	Unit* AlienUnit;
	/*Here Alien Soldier Will attack Earth Soldiers Depend on its attack capacity*/
	if (!aSoldiersList.isEmpty()) {
		aSoldiersList.peek(AlienUnit);
		LinkedQueue<Unit*> SoldierTemp;
		/*First we will get the soldiers that will be attacked*/
		for (int i = 0;i < AlienUnit->getAttackCapacity();i++) {
			EarthUnit = enemy->removeUnit("ES");
			SoldierTemp.enqueue(EarthUnit);
		}
		/* then we will start to attack them */
		for (int i = 0;i < AlienUnit->getAttackCapacity();i++) {
			SoldierTemp.dequeue(EarthUnit);
			AlienUnit->attack(EarthUnit);
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

		LinkedQueue<Unit*> enemyTemp;

		int tankCapacity = AlienUnit->getAttackCapacity() / 2;
		int soldierCapacity = AlienUnit->getAttackCapacity() - tankCapacity;

		for (int i = 0; i < AlienUnit->getAttackCapacity(); i++) {

			if (enemyTemp.getCount() < tankCapacity) {
				EarthUnit = enemy->removeUnit("ET");
				enemyTemp.enqueue(EarthUnit);
			}
			else {
				EarthUnit = enemy->removeUnit("ES");
				enemyTemp.enqueue(EarthUnit);
			}
		}

		for (int i = 0; i < AlienUnit->getAttackCapacity(); i++) {
			enemyTemp.dequeue(EarthUnit);
			AlienUnit->attack(EarthUnit);
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
		aDronesList.RearDequeue(secAlienUnit);
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
			for (int i = 0; i < enemyTemp.getCount(); i++) {
				enemyTemp.dequeue(EarthUnit);
				AlienUnit->attack(EarthUnit);
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
			for (int i = 0; i < enemyTemp.getCount(); i++) {
				enemyTemp.dequeue(EarthUnit);
				secAlienUnit->attack(EarthUnit);
				if (EarthUnit->getHealth() <= 0)  // after attack i have to check is the Monster dead or not 
				{
					pGame->AddToKilled(EarthUnit);
				}
				else {
					enemy->addUnit(EarthUnit);
				}
			}
			
		}
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
		
