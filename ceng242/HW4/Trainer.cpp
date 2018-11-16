#include "Trainer.h"

Trainer::Trainer
(int id, const std::string& n, Arena fav, std::vector<Pokemon*>& poke)
: trainerID(id), name(n), favoriteArena(fav), pokemons(poke)
{
}

Trainer::~Trainer()
{
	for (int i = 0, size = pokemons.size(); i < size; i++)
		delete pokemons[i];
}
int Trainer::getTrainerID() const
{
	return trainerID;
}

const std::string& Trainer::getName() const
{
	return name;
}

Arena Trainer::getFavoriteArena() const
{
	return favoriteArena;
}

int Trainer::getAlivePokemons() const
{
	int n = 0;
	for (int i = 0, size = pokemons.size(); i < size; i++)
		if (pokemons[i]->isAlive())
			n++;
	return n;
}

void Trainer::revivePokemons()
{
	for (int i = 0, size = pokemons.size(); i < size; i++)
		pokemons[i]->revive();
}

std::list<Pokemon*> Trainer::pokeList() const
{
	std::list<Pokemon*> l;

	for (int i = 0, size = pokemons.size(); i < size; i++)
		l.push_back(pokemons[i]);

	return l;
}
