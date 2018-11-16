#include "TrainerCenter.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
void parse(
	std::string& line,
	const char *d,
	int& id,
	std::string& name,
	std::string& t)
{
	int i =line.find(d);
	id = atoi(line.substr(0,i).c_str());
	line = line.substr(i+2);
	i = line.find(d);
	name = line.substr(0, i);
	t = line.substr(i+2);
}
Pokemon *constructPokemon(int id, std::string name, std::string type)
{
	Pokemon *p = 0;
	if (type == "FLYING")
		p = new PokeFlying(id, name);
	else if (type == "GRASS")
		p = new PokeGrass(id, name);
	else if (type == "ELECTRIC")
		p = new PokeElectric(id, name);
	else if (type == "WATER")
		p = new PokeWater(id, name);
	else if (type == "FIRE")
		p = new PokeFire(id, name);

	return p;
}
TrainerCenter::TrainerCenter(const std::string& file)
{
	std::ifstream data;
	data.open(file.c_str());
	std::string s, ss, tmp, sss, token;
	int t,p;
	data >> s >> ss >> tmp >> sss;
	std::getline(data, tmp);
	std::getline(data, tmp);
	if (s == "Trainer")
		t = atoi(ss.substr(ss.find(":")+1).c_str()),
		p = atoi(sss.substr(sss.find(":")+1).c_str());
	else
		t = atoi(sss.substr(sss.find(":")+1).c_str()),
		p = atoi(ss.substr(ss.find(":")+1).c_str());

	std::string line;
	for (int i = 0; i < t; i++)
	{
		std::getline(data, line);
		int trainerID;
		std::string trainer_name, arena;
		parse(line, "--", trainerID, trainer_name, arena);
		std::vector<Pokemon*> poke;
		for (int j = 0; j < p; j++)
		{
			std::getline(data, line);
			int pokemonID;
			std::string pokemon_name, type;
			parse(line, "::", pokemonID, pokemon_name, type);
			poke.push_back(constructPokemon(pokemonID, pokemon_name, type));
		}
		trainers.push_back(
			new Trainer(trainerID, trainer_name, Helpers::getArena(arena), poke));
		std::getline(data,tmp);
	}
}
TrainerCenter::~TrainerCenter()
{
	for (int i = 0, size = trainers.size(); i < size; i++)
		delete trainers[i];
}

std::vector<Trainer*>& TrainerCenter::getAllTrainers()
{
	return trainers;
}

Trainer* TrainerCenter::getTrainerWithID(int id)
{
	for (int i = 0, size = trainers.size(); i < size; i++)
		if (trainers[i]->getTrainerID() == id)
			return trainers[i];
	return 0;
}
