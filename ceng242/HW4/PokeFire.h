#ifndef POKEFIRE_H
#define POKEFIRE_H

#include "Pokemon.h"

const int
FIRE_HP = 600, FIRE_ATK = 60, FIRE_MAG_DEF = 20, FIRE_PHY_DEF = 10;

class PokeFire : public Pokemon
{
public:
	// Add your public methods/attributes here.
	PokeFire(int id, const std::string& name);

	void sufferDamage();
	void attackTo(Pokemon *target, Arena arena);
	void setAbnormalStatus(Pokemon *target) const;
	void levelUp();
	void revive();

	void setHPbyArena(Arena arena);
	void setBurning(bool status);

protected:
	// Add your protected methods/attributes here.

private:
	// Add your private methods/attributes here.
	
};

#endif
