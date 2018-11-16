#ifndef POKEELECTRIC_H
#define POKEELECTRIC_H

#include "Pokemon.h"

const int
ELECTRIC_HP = 500, ELECTRIC_ATK = 70, ELECTRIC_MAG_DEF = 30, ELECTRIC_PHY_DEF = 0;

class PokeElectric : public Pokemon
{
public:
	// Add your public methods/attributes here.
	PokeElectric(int id, const std::string& name);

	void sufferDamage();
	void attackTo(Pokemon *target, Arena arena);
	void setAbnormalStatus(Pokemon *target) const;
	void levelUp();
	void revive();

	void setElectrified(bool newstatus);
	void setHPbyArena(Arena arena);

protected:
	// Add your protected methods/attributes here.

private:
	// Add your private methods/attributes here.
	
};

#endif
