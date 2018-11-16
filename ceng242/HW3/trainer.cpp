#include "trainer.h"

Trainer::Trainer
(const string &n, const Pokemon &poke, const int *min, const int *max)
: name(n)
{
	minFOV[0] = min[0]; minFOV[1] = min[1]; minFOV[2] = min[2];
	maxFOV[0] = max[0]; maxFOV[1] = max[1]; maxFOV[2] = max[2];

	pokemons.push_back(new Pokemon(poke));
}

Trainer::Trainer(const Trainer &t)
: name(t.name)
{
	minFOV[0] = t.minFOV[0]; minFOV[1] = t.minFOV[1]; minFOV[2] = t.minFOV[2]; 
	maxFOV[0] = t.maxFOV[0]; maxFOV[1] = t.maxFOV[1]; maxFOV[2] = t.maxFOV[2];
	for (size_t i = 0; i < t.pokemons.size(); i++)
		pokemons.push_back(new Pokemon(*t.pokemons[i]));
}

Trainer::~Trainer()
{
	for (size_t i = 0; i < pokemons.size(); i++)
		delete pokemons[i];
}
ostream& showPokemons(ostream& out, const Trainer& t)
{
	for (size_t i = 0; i < t.pokemons.size(); i++)
		out << t.pokemons[i]->getName() << endl;
	return out;
}

void Trainer::scanRegion(Region& r)
{
	for (int i = minFOV[0]; i <= maxFOV[0]; i++)
		for (int j = minFOV[1]; j <= maxFOV[1]; j++)
			for (int k = minFOV[2]; k <= maxFOV[2]; k++)
				try{
					Pokemon& p = r(i,j,k);
					catchPokemon(p);
					delete &p;
				}
				catch (pokemonException&){
				}
}
