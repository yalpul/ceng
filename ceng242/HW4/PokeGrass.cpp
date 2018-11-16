#include "PokeGrass.h"

static const int
HP_LEVELUP = 80, ATK_LEVELUP = 4, MAG_DEF_LEVELUP = 0, PHY_DEF_LEVELUP = 3;

PokeGrass::PokeGrass(int id, const std::string& n)
: Pokemon(id,n)
{
	HP = GRASS_HP;
	ATK = GRASS_ATK;
	MAG_DEF = GRASS_MAG_DEF;
	PHY_DEF = GRASS_PHY_DEF;
}
void PokeGrass::sufferDamage()
{
	if (burning)
	{
		std::cout << "\t\t\t"<< name << "(" << HP << ") is burning!!!!\n";
		HP -= max(0, 2*BURN_DAMAGE - MAG_DEF);
	}
	if (HP <= 0)
		alive = false;
	if (alive && drowning)
	{
		std::cout << "\t\t\t"<< name << "(" << HP << ") is drowning!!\n";
		HP -= max(0, DROWN_DAMAGE - MAG_DEF);
	}
	if (HP <= 0)
		alive = false;
	if (alive && electrified)
	{
		std::cout << "\t\t\t"<< name << "(" << HP << ") is electrified!!\n";
		HP -= max(0, ELECTRIFY_DAMAGE - MAG_DEF);
	}
	if (HP <= 0)
		alive = false;
}
void PokeGrass::setAbnormalStatus(Pokemon *target) const
{
	target->setRooted(true);
}
void PokeGrass::setHPbyArena(Arena arena)
{
	if (arena == MAGMA || arena == SKY) 
		HP -= HP_MODIFIER;
	else if (arena == FOREST)
		HP += HP_MODIFIER;
}
void PokeGrass::attackTo(Pokemon *p, Arena arena)
{
	char sym = '/';
	int ATK_in_this_arena = ATK;

	if (arena == MAGMA || arena == SKY) 
		ATK_in_this_arena -= ATK_MODIFIER, sym = '-';
	else if (arena == FOREST)
		ATK_in_this_arena += ATK_MODIFIER, sym = '+';
	
	int damage = max(1,ATK_in_this_arena - p->getPHY_DEF());
	std::cout << "\t\t\t" << name << "(" << HP << ") hit " << p->getName()
						<< "(" << p->getHP() << ") " << damage
						<< "(" << sym << ")\n";
	p->setHP(p->getHP() - damage);

	setAbnormalStatus(p);

	if (p->getHP() <= 0)
		p->die();
}
void PokeGrass::revive()
{
	burning = drowning = electrified = rooted = false;
	alive = true;
	HP = GRASS_HP + level*HP_LEVELUP;
	ATK = GRASS_ATK + level*ATK_LEVELUP;
	MAG_DEF = GRASS_MAG_DEF + level*MAG_DEF_LEVELUP;
	PHY_DEF = GRASS_PHY_DEF + level*PHY_DEF_LEVELUP;
}
void PokeGrass::levelUp()
{
	HP += HP_LEVELUP;
	ATK += ATK_LEVELUP;
	PHY_DEF += PHY_DEF_LEVELUP;
	level++;
}
void PokeGrass::setRooted(bool)
{
}
