#ifndef POKEGRASS_H
#define POKEGRASS_H

#include "Pokemon.h"

const int
GRASS_HP = 800, GRASS_ATK = 40, GRASS_MAG_DEF = 0, GRASS_PHY_DEF = 30;

class PokeGrass : public Pokemon
{
public:
	// Add your public methods/attributes here.
	PokeGrass(int id, const std::string& name);

	void sufferDamage();
	void attackTo(Pokemon *target, Arena arena);
	void setAbnormalStatus(Pokemon *target) const;
	void levelUp();
	void revive();

	void setHPbyArena(Arena arena);
	void setRooted(bool status);

protected:
	// Add your protected methods/attributes here.

private:
	// Add your private methods/attributes here.
	
};

#endif
