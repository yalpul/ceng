#include <list>
#include "Tournament.h"

Tournament::Tournament(const std::string& name)
: tournamentName(name)
{
}
Tournament::~Tournament()
{
}
const std::string& Tournament::getTournamentName() const
{
	return tournamentName;
}
int Tournament::duelBetween(Pokemon *poke1, Pokemon *poke2, Arena arena)
{
	while (poke1->isAlive() && poke2->isAlive())
	{
		if (poke1->isAlive())
			poke1->sufferDamage();
		else break;

		if (poke1->isAlive())
			poke1->attackTo(poke2, arena);
		else break;

		if (poke2->isAlive())
			poke2->sufferDamage();
		else break;

		if (poke2->isAlive())
			poke2->attackTo(poke1, arena);
		else break;
	}
	if (poke1->isAlive())
		return (poke1->levelUp(), 1);
	else
		return (poke2->levelUp(), -1);
}
int Tournament::duelBetween(Trainer *t1, Trainer *t2, Arena arena)
{
	int i = 0, j = 0;
	std::cout << '\t' << t1->getName() << " vs " << t2->getName()
						<< ": " << Helpers::getArenaName(arena) << '\n';
	std::list<Pokemon*> l1 = t1->pokeList(), l2 = t2->pokeList();
	l1.front()->setHPbyArena(arena);
	l2.front()->setHPbyArena(arena);
	while (t1->getAlivePokemons() && t2->getAlivePokemons())
	{
		if (duelBetween(l1.front(), l2.front(), arena) > 0)
		{
			std::cout << "\t\tWinnerP:" << l1.front()->getName() << '\n';
			l2.pop_front();
			if (l2.size())
				l2.front()->setHPbyArena(arena);
			std::swap(l1, l2);
		}
		else
		{
			std::cout << "\t\tWinnerP:" << l2.front()->getName() << '\n';
			l1.pop_front();
			if (l1.size())
				l1.front()->setHPbyArena(arena);
		}
	}
	int winner = 0;
	if (t1->getAlivePokemons())
		(std::cout << "\tWinnerT:" << t1->getName() << "\n\n", winner = 1);
	else
		(std::cout << "\tWinnerT:" << t2->getName() << "\n\n", winner = -1);
	
	t1->revivePokemons();
	t2->revivePokemons();

	return winner;
}
void Tournament::registerTrainers(const std::vector<Trainer*>& t)
{
	trainers = t;
}
Trainer* Tournament::commence()
{
	std::vector<Trainer*> winners, t = trainers;

	while (t.size() != 1)
	{
		int i = 0, j = t.size() -1;
		while (i < j)
		{
			Trainer *t1 = t[i], *t2 = t[j];
			int t1_wins = 0, t2_wins = 0;

			std::cout << "Started Round: " << i++ << " vs " << j-- << '\n';

			if (duelBetween(t1, t2, t1->getFavoriteArena()) > 0)
				t1_wins++;
			else
				t2_wins++;

			if (duelBetween(t2, t1, t2->getFavoriteArena()) > 0)
				t2_wins++;
			else
				t1_wins++;

			if (duelBetween(t1, t2, STADIUM) > 0)
				t1_wins++;
			else
				t2_wins++;


			Trainer *winner = t1_wins > 1 ? t1 : t2;
			std::cout << "Round Winner: " << winner->getName() << "!\n";
			winners.push_back(winner);
		}
		t = winners;
		winners = std::vector<Trainer*>();
	}
	return t.front();
}
