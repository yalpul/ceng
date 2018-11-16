#include "PokeFlying.h"

static const int
HP_LEVELUP = 65, ATK_LEVELUP = 5, MAG_DEF_LEVELUP = 0, PHY_DEF_LEVELUP = 3;

PokeFlying::PokeFlying(int id, const std::string& n)
: Pokemon(id,n)
{
	HP = FLYING_HP;
	ATK = FLYING_ATK;
	MAG_DEF = FLYING_MAG_DEF;
	PHY_DEF = FLYING_PHY_DEF;
}
void PokeFlying::sufferDamage()
{
}
void PokeFlying::setHPbyArena(Arena arena)
{
	if (arena == SKY)
		HP += HP_MODIFIER;
	else if (arena == OCEAN || arena == ELECTRICITY)
		HP -= HP_MODIFIER;
}
void PokeFlying::attackTo(Pokemon *p, Arena arena)
{
	char sym = '/';
	int ATK_in_this_arena = ATK;

	if (arena == SKY)
		ATK_in_this_arena += ATK_MODIFIER, sym = '+';
	else if (arena == OCEAN || arena == ELECTRICITY)
		ATK_in_this_arena -= ATK_MODIFIER, sym = '-';
	
	int damage = max(1,ATK_in_this_arena - p->getPHY_DEF());
	std::cout << "\t\t\t" << name << "(" << HP << ") hit " << p->getName()
						<< "(" << p->getHP() << ") " << damage
						<< "(" << sym << ")\n";
	p->setHP(p->getHP() - damage);

	setAbnormalStatus(p);

	if (p->getHP() <= 0)
		p->die();
}
void PokeFlying::revive()
{
	burning = drowning = electrified = rooted = false;
	alive = true;
	HP = FLYING_HP + level*HP_LEVELUP;
	ATK = FLYING_ATK + level*ATK_LEVELUP;
	MAG_DEF = FLYING_MAG_DEF + level*MAG_DEF_LEVELUP;
	PHY_DEF = FLYING_PHY_DEF + level*PHY_DEF_LEVELUP;
}
void PokeFlying::levelUp()
{
	HP += HP_LEVELUP;
	ATK += ATK_LEVELUP;
	PHY_DEF += PHY_DEF_LEVELUP;
	level++;
}
void PokeFlying::setAbnormalStatus(Pokemon *target) const
{
}
void PokeFlying::setBurning(bool)
{
}
void PokeFlying::setDrowning(bool)
{
}
void PokeFlying::setRooted(bool)
{
}
void PokeFlying::setElectrified(bool)
{
}
