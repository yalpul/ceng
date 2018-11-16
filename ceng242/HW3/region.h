#ifndef REGION_H
#define REGION_H

#include "pokemon.h"
#include <iostream>
#include <exception>

using namespace std;

class Region {
	private:
		// Add private members, methods and constructors here as you need
		int minx, miny, minz, maxx, maxy, maxz;
		int numberOfPokemons; 		//number of pokemons living in this 
															//region (actually int its unit cells)
		char divCrd;
		Pokemon* pokemon;		// pokemon living in this region
		Region* firstHalf;
		Region* secondHalf;
		void deleteRegion();
		bool intersects(const int[3], const int[3]) const;
		void updatePokemonCount();
		bool isPokemon(int x, int y, int z) const;
		Region(int mins[3], int maxs[3], char nextcrd);
	public:
		// Do NOT make any modifications below
		Region(const int[3], const int[3]);
		Region(const Region&);
		~Region();
		int getMinBorder(char) const;
		int getMaxBorder(char) const;
		void placePokemon(const Pokemon&, int, int, int);
		Pokemon& operator()(int, int, int);
		int getPokemonCount(const int[3], const int[3]) const;
		Region crop(const int[3], const int[3]) const;
		void patch(Region);
		Region& operator=(const Region&);
};

class pokemonException: public exception {
 	virtual const char* what() const throw() {
    		return "There does not exist any pokemon in the given coordinates!";
	}
};

#endif
