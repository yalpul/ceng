#ifndef TRAINER_CENTER_H
#define TRAINER_CENTER_H

#include <vector>
#include <string>
#include "Trainer.h"
#include "Pokemon.h"
#include "PokeFire.h"
#include "PokeGrass.h"
#include "PokeWater.h"
#include "PokeFlying.h"
#include "PokeElectric.h"

class TrainerCenter
{
public:
	// Public Methods

	TrainerCenter(const std::string& inputFileName);
    ~TrainerCenter();
    
	std::vector<Trainer*>& getAllTrainers();

	Trainer* getTrainerWithID(int trainerID);

	// Own Methods

private:
	// Own Attributes
	std::vector<Trainer*> trainers;

};

#endif
