#include "pokemon.h"

Pokemon::Pokemon(const string &n, const string &t, int exp)
: name(n), type(t), next_exp(exp), current_exp(0), t_ref_cnt(0)
{
}

Pokemon::~Pokemon()
{
}
Pokemon::Pokemon(const Pokemon &poke)
: name(poke.name), type(poke.type), next_exp(poke.next_exp),
	 current_exp(poke.current_exp), t_ref_cnt(poke.t_ref_cnt)
{
}

const string& Pokemon::getName() const
{
	return name;
}

bool Pokemon::operator>>(const Pokemon &poke)
{
	if (next_exp == -1 || current_exp < next_exp)
		return false;
	name = poke.name; type = poke.type; next_exp = poke.next_exp;
	return true;
}

Pokemon& Pokemon::operator=(const Pokemon &poke)
{
	name = poke.name; type = poke.type; next_exp = poke.next_exp;
	t_ref_cnt = poke.t_ref_cnt;
	return *this;
}
Pokemon operator&(Pokemon& poke1, Pokemon& poke2)
{
	static char table[5][5] = { {'\0', 't', 'r', 'r', 'y'},
															{'t', '\0', 'a', 'e', 't'},
															{'r', 'a', '\0', 'a', 'y'},
															{'r', 'e', 'a', '\0', 'e'},
															{'y', 't', 'y', 'e', '\0'}};

	int i=0,j=0;
	poke1.current_exp++;
	poke2.current_exp++;
	switch (poke1.type[2])
	{
		case 'r': i = 0; break;
		case 't': i = 1; break;
		case 'a': i = 2; break;
		case 'e': i = 3; break;
		case 'y': i = 4; break;
	}

	switch (poke2.type[2])
	{
		case 'r': j = 0; break;
		case 't': j = 1; break;
		case 'a': j = 2; break;
		case 'e': j = 3; break;
		case 'y': j = 4; break;
	}
	return (table[i][j] == poke1.type[2] ? poke1 : poke2);
	/*
	if (poke1.type == "fire" && 
		 (poke2.type == "grass" || poke2.type == "electric")
		 ||
		 poke1.type == "water" &&
		 (poke2.type == "fire" || poke2.type == "flying")
		 ||
		 poke1.type == "grass" &&
		 (poke2.type == "water" || poke2.type == "electric")
		 ||
		 poke1.type == "electric" &&
		 (poke2.type == "water" || poke2.type == "flying")
		 ||
		 poke1.type == "flying" &&
		 (poke2.type == "fire" || poke2.type == "grass"))
		 	return poke1;
		else
			return poke2;
			*/
}

