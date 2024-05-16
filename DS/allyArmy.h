#ifndef ALLY_ARMY_H 
#define ALLY_ARMY_H
#include "Army.h"

class allyArmy : public Army
{
    // Lists 
    LinkedQueue<Unit*> saverUnitsList;
    LinkedQueue<Unit*>* SU_attacking_list;


    // Unit-Pointers
    Unit* allyUnit;
    Unit* SU_attack;

public:

    // constructor 
    allyArmy(Game* pGame);

    // battle related functions
    bool attack(Army* enemy, int timestep);
    void Withdrawal();

    // list controlling functions
    Unit* removeUnit(string type);
    void addUnit(Unit*);

    // getters
    int getSoldiersCount();

    // print functions
    void printArmy();
    void printFightingUnits();

    // outFile functions
    void Armyfile(fstream&, int, int, int, int, int,int);

    // destructor
    ~allyArmy();
};

#endif