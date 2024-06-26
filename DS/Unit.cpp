#include "Unit.h"

int Unit::infectedCount = 0;
int Unit::total_infected = 0;

Unit::Unit()
{
}
Unit::Unit(int id, string type, int jointime, double health, double power, int attackcapacity)
{
	ID = id;
	joinTime = jointime;
	Type = type;
	Health = health;
	originalHealth = health;
	Power = power;
	attackCapacity = attackcapacity;
	fAtime = 0;
	DEStime = 0;
	infected = false;
	immune = false;
	healingCounter = 0;
}

Unit::~Unit()
{
}

void Unit::setID(int id)
{
	ID = id;
}

int Unit::getID() const
{
	return ID;
}

void Unit::setfatime(int x)
{
	if (fAtime == 0) {
		fAtime = x;
	}

}

int Unit::getfatime() const
{
	return fAtime;
}

string Unit::getType() const
{
	return Type;
}

void Unit::setJoinTime(int jointime)
{
	joinTime = jointime;
}

int Unit::getJoinTime() const
{
	return joinTime;
}

void Unit::setDEStime(int x)
{
	DEStime = x;
}

int Unit::getDEStime() const
{
	return DEStime;
}

void Unit::setHealth(double health)
{
	Health = health;
}

double Unit::getHealth() const
{
	return Health;
}

void Unit::setPower(double power)
{
	Power = power;
}

double Unit::getPower() const
{
	return Power;
}

void Unit::setAttackCapacity(int attackcapacity)
{
	attackCapacity = attackcapacity;
}

int Unit::getAttackCapacity() const
{
	return attackCapacity;
}

double Unit::getPriority() const
{
	return 0.4 * Health + 0.6 * Power;   // means i give 40% of importance to Health and 60% to power
}

void Unit::setUMLJoinTime(int time)
{
	UMLJoinTime = time;
}

int Unit::getUMLJoinTime() const
{
	return UMLJoinTime;
}

double Unit::getOriginalHealth() const
{
	return originalHealth;
}

void Unit::print()
{
   

}

void Unit::setInfectionStatus(bool val)
{
	if (val == true)
	{
		total_infected++;
	}

	infected = val;
}

bool Unit::getInfectionStatus() const
{
	return infected;
}
void Unit::decrementInfectedCount()
{
	infectedCount--;
}
void Unit::incrementInfectedCount()
{
	infectedCount++;
}

int Unit::getInfectedCount()
{
	return infectedCount;
}

int Unit::getTotalInfected()
{
	return total_infected;
}

void Unit::setImmunityStatus(bool val)
{
	immune = val;
}

bool Unit::getImmunityStatus() const
{
	return immune;
}



void Unit::setHealingCounter(int val)
{
	healingCounter = val;
}

int Unit::getHealingCounter() const
{
	return healingCounter;
}
