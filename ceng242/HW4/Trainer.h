#ifndef TRAINER_H
#define TRAINER_H

#include <string>
#include <vector>
#include <list>

#include "Pokemon.h"

class Trainer
{
public:
	// Public Methods
	Trainer(int trainerID, const std::string& name, Arena favoriteArena, std::vector<Pokemon *>& pokemons);
	~Trainer();

	// Getters

	int getTrainerID() const;
	const std::string& getName() const;
	Arena getFavoriteArena() const;

	// Own Methods
	int getAlivePokemons() const;
	std::list<Pokemon*> pokeList() const;
	void revivePokemons();

private:
	int trainerID; 		// Unique
	std::string name;
	Arena favoriteArena;

	std::vector<Pokemon *> pokemons;

	// Own Attributes
	
};

#endif
