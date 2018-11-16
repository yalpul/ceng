#include "PokeWater.h"

static const int
HP_LEVELUP = 70, ATK_LEVELUP = 5, MAG_DEF_LEVELUP = 1, PHY_DEF_LEVELUP = 2;

PokeWater::PokeWater(int id, const std::string& n)
: Pokemon(id,n)
{
	HP = WATER_HP;
	ATK = WATER_ATK;
	MAG_DEF = WATER_MAG_DEF;
	PHY_DEF = WATER_PHY_DEF;
}
void PokeWater::sufferDamage()
{
	if (burning)
	{
		std::cout << "\t\t\t" << name << "(" << HP << ") is burning!!\n";
		HP -= max(0, BURN_DAMAGE - MAG_DEF);
	}
	if (HP <= 0)
		alive = false;
	if (alive && electrified)
	{
		std::cout << "\t\t\t" << name << "(" << HP << ") is electrified!!!!\n";
		HP -= max(0, 2*ELECTRIFY_DAMAGE - MAG_DEF);
	}
	if (HP <= 0)
		alive = false;
	if (alive && rooted)
	{
		std::cout << "\t\t\t" << name << "(" << HP << ") is rooted!!\n";
		HP -= max(0, ROOT_DAMAGE - MAG_DEF);
	}
	if (HP <= 0)
		alive = false;
}
void PokeWater::setHPbyArena(Arena arena)
{
	if (arena == OCEAN)
		HP += HP_MODIFIER;
	else if (arena == ELECTRICITY || arena == FOREST)
		HP -= HP_MODIFIER;
}
void PokeWater::attackTo(Pokemon *p, Arena arena)
{
	char sym = '/';
	int ATK_in_this_arena = ATK;

	if (arena == OCEAN)
		ATK_in_this_arena += ATK_MODIFIER, sym = '+';
	else if (arena == ELECTRICITY || arena == FOREST)
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
void PokeWater::setAbnormalStatus(Pokemon *target) const
{
	target->setDrowning(true);
}
void PokeWater::revive()
{
	burning = drowning = electrified = rooted = false;
	alive = true;
	HP = WATER_HP + level*HP_LEVELUP;
	ATK = WATER_ATK + level*ATK_LEVELUP;
	MAG_DEF = WATER_MAG_DEF + level*MAG_DEF_LEVELUP;
	PHY_DEF = WATER_PHY_DEF + level*PHY_DEF_LEVELUP;
}
void PokeWater::levelUp()
{
	HP += HP_LEVELUP;
	ATK += ATK_LEVELUP;
	MAG_DEF += MAG_DEF_LEVELUP;
	PHY_DEF += PHY_DEF_LEVELUP;
	level++;
}
void PokeWater::setDrowning(bool)
{
}
