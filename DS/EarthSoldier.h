#pragma once
#include "Unit.h"

class EarthSoldier : public Unit
{

	double originalHealth;

public:
	EarthSoldier(int id, int jointime, double health, double power, int attackcapacity);
	void attack(Unit* target) override;
	double getOriginalHealth() const;
	void setOriginalHealth(double health);
};

