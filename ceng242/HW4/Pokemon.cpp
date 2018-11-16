#include "Pokemon.h"

int max(int a, int b)
{
	return a > b ? a : b;
}
Pokemon::Pokemon(int id, const std::string& n)
: pokemonID(id), name(n), 
	burning(false), drowning(false), electrified(false), rooted(false),
	alive(true), level(0)
{
}
Pokemon::~Pokemon()
{
}
int Pokemon::getPokemonID() const
{
	return pokemonID;
}
const std::string& Pokemon::getName() const
{
	return name;
}
int Pokemon::getHP() const
{
	return HP;
}
int Pokemon::getATK() const
{
	return ATK;
}
int Pokemon::getMAG_DEF() const
{
	return MAG_DEF;
}
int Pokemon::getPHY_DEF() const
{
	return PHY_DEF;
}
bool Pokemon::isAlive() const
{
	return alive;
}
bool Pokemon::isBurning() const
{
	return burning;
}
bool Pokemon::isDrowning() const
{
	return drowning;
}
bool Pokemon::isElectrified() const
{
	return electrified;
}
bool Pokemon::isRooted() const
{
	return rooted;
}
void Pokemon::setHP(int hp)
{
	HP = hp;
}
void Pokemon::die()
{
	alive = false;
}
void Pokemon::setBurning(bool newstatus)
{
	burning = newstatus;
}
void Pokemon::setDrowning(bool newstatus)
{
	drowning = newstatus;
}
void Pokemon::setElectrified(bool newstatus)
{
	electrified = newstatus;
}
void Pokemon::setRooted(bool newstatus)
{
	rooted = newstatus;
}
