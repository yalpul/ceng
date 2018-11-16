#include "PokeFire.h"

static const int
HP_LEVELUP = 60, ATK_LEVELUP = 6, MAG_DEF_LEVELUP = 2, PHY_DEF_LEVELUP = 1;

PokeFire::PokeFire(int id, const std::string& n)
: Pokemon(id,n)
{
	HP = FIRE_HP;
	ATK = FIRE_ATK;
	MAG_DEF = FIRE_MAG_DEF;
	PHY_DEF = FIRE_PHY_DEF;
}
void PokeFire::sufferDamage()
{
	if (drowning)
	{
		std::cout << "\t\t\t" << name << "(" << HP << ") is drowning!!!!\n";
		HP -= max(0, 2*DROWN_DAMAGE - MAG_DEF);
	}
	if (HP <= 0)
		alive = false;
	if (alive && electrified)
	{
		std::cout << "\t\t\t" << name << "(" << HP << ") is electrified!!\n";
		HP -= max(0, ELECTRIFY_DAMAGE - MAG_DEF);
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
void PokeFire::setHPbyArena(Arena arena)
{
	if (arena == MAGMA)
		HP += HP_MODIFIER;
	else if (arena == OCEAN || arena == SKY)
		HP -= HP_MODIFIER;
}
void PokeFire::attackTo(Pokemon *p, Arena arena)
{
	char sym = '/';
	int ATK_in_this_arena = ATK;

	if (arena == MAGMA)
		ATK_in_this_arena += ATK_MODIFIER, sym = '+';
	else if (arena == OCEAN || arena == SKY)
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
void PokeFire::setAbnormalStatus(Pokemon *target) const
{
	target->setBurning(true);
}
void PokeFire::revive()
{
	burning = drowning = electrified = rooted = false;
	alive = true;
	HP = FIRE_HP + level*HP_LEVELUP;
	ATK = FIRE_ATK + level*ATK_LEVELUP;
	MAG_DEF = FIRE_MAG_DEF + level*MAG_DEF_LEVELUP;
	PHY_DEF = FIRE_PHY_DEF + level*PHY_DEF_LEVELUP;
}
void PokeFire::levelUp()
{
	HP += HP_LEVELUP;
	ATK += ATK_LEVELUP;
	MAG_DEF += MAG_DEF_LEVELUP;
	PHY_DEF += PHY_DEF_LEVELUP;
	level++;
}
void PokeFire::setBurning(bool)
{
}
