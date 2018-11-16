#ifndef TRAINER_H
#define TRAINER_H

#include "pokemon.h"
#include "region.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Trainer {
	private:
		// Add private members, methods and constructors here as you need
		string name;
		vector<const Pokemon*> pokemons;
		int minFOV[3], maxFOV[3];
		int index;
		bool isLegalToScan(const int[3], const int[3]) const;
		void helperScanRegion(Region&, int, const int[3], const int[3]) ;
	public:
		// Do NOT make any modifications below
		Trainer(const string&, const Pokemon&, const int[3], const int[3]);
		Trainer(const Trainer&);
		~Trainer();
		void catchPokemon(const Pokemon& newPokemon) {
			pokemons.push_back(new Pokemon(newPokemon));
		}
		void scanRegion(Region&);
		friend ostream& showPokemons(ostream&, const Trainer&);
};

#endif
