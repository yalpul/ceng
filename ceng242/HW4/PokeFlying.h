#ifndef POKEFLYING_H
#define POKEFLYING_H

#include "Pokemon.h"

const int
FLYING_HP = 650, FLYING_ATK = 55, FLYING_MAG_DEF = 0, FLYING_PHY_DEF = 15;

class PokeFlying : public Pokemon
{
public:
	// Add your public methods/attributes here.
	PokeFlying(int id, const std::string& name);

	void sufferDamage();
	void attackTo(Pokemon *target, Arena arena);
	void levelUp();
	void revive();

	void setHPbyArena(Arena arena);
	void setAbnormalStatus(Pokemon *target) const;
	void setBurning(bool status);
	void setDrowning(bool status);
	void setRooted(bool status);
	void setElectrified(bool status);

protected:
	// Add your protected methods/attributes here.

private:
	// Add your private methods/attributes here.
	
};

#endif
