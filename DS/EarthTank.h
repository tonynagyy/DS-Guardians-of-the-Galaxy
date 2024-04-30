#pragma once
#include "Unit.h"

class EarthTank : public Unit
{
	double originalHealth;

public:

	EarthTank(int id, int jointime, double health, double power, int attackcapacity);
	void attack(Unit* target) override;
	double getOriginalHealth() const;
};

