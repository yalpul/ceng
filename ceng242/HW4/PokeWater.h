#ifndef POKEWATER_H
#define POKEWATER_H

#include "Pokemon.h"

const int
WATER_HP = 700, WATER_ATK = 50, WATER_MAG_DEF = 10, WATER_PHY_DEF = 20;

class PokeWater : public Pokemon
{
public:
	// Add your public methods/attributes here.
	PokeWater(int id, const std::string& name);

	void sufferDamage();
	void attackTo(Pokemon *target, Arena arena);
	void setAbnormalStatus(Pokemon *target) const;
	void levelUp();
	void revive();

	void setHPbyArena(Arena arena);
	void setDrowning(bool status);

protected:
	// Add your protected methods/attributes here.

private:
	// Add your private methods/attributes here.
	
};

#endif
