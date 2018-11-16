#include "PokeElectric.h"

static const int
HP_LEVELUP = 50, ATK_LEVELUP = 7, MAG_DEF_LEVELUP = 3, PHY_DEF_LEVELUP = 0;

PokeElectric::PokeElectric(int id, const std::string& n)
: Pokemon(id,n)
{
	HP = ELECTRIC_HP;
	ATK = ELECTRIC_ATK;
	MAG_DEF = ELECTRIC_MAG_DEF;
	PHY_DEF = ELECTRIC_PHY_DEF;
}
void PokeElectric::sufferDamage()
{
	if (burning)
	{
		std::cout << "\t\t\t" << name << "(" << HP << ") is burning!!\n";
		HP -= max(0, BURN_DAMAGE - MAG_DEF);
	}
	if (HP <= 0)
		alive = false;
	if (alive && drowning)
	{
		std::cout << "\t\t\t" << name << "(" << HP << ") is drowning!!\n";
		HP -= max(0, DROWN_DAMAGE - MAG_DEF);
	}
	if (HP <= 0)
		alive = false;
	if (alive && rooted)
	{
		std::cout << "\t\t\t" << name << "(" << HP << ") is rooted!!!!\n";
		HP -= max(0, 2*ROOT_DAMAGE - MAG_DEF);
	}
	if (HP <= 0)
		alive = false;
}
void PokeElectric::revive()
{
	burning = drowning = electrified = rooted = false;
	alive = true;
	HP = ELECTRIC_HP + level*HP_LEVELUP;
	ATK = ELECTRIC_ATK + level*ATK_LEVELUP;
	MAG_DEF = ELECTRIC_MAG_DEF + level*MAG_DEF_LEVELUP;
	PHY_DEF = ELECTRIC_PHY_DEF + level*PHY_DEF_LEVELUP;
}
void PokeElectric::setHPbyArena(Arena arena)
{
	if (arena == ELECTRICITY)
		HP += HP_MODIFIER;
	else if (arena == MAGMA || arena == FOREST)
		HP -= HP_MODIFIER;
}
void PokeElectric::attackTo(Pokemon *p, Arena arena)
{
	char sym = '/';
	int ATK_in_this_arena = ATK;

	if (arena == ELECTRICITY)
		ATK_in_this_arena += ATK_MODIFIER, sym = '+';
	else if (arena == MAGMA || arena == FOREST)
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
void PokeElectric::setAbnormalStatus(Pokemon *target) const
{
	target->setElectrified(true);
}
void PokeElectric::levelUp()
{
	HP += HP_LEVELUP;
	ATK += ATK_LEVELUP;
	MAG_DEF += MAG_DEF_LEVELUP;
	level++;
}
void PokeElectric::setElectrified(bool)
{
}
