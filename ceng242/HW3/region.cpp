#include "region.h"

Region::Region(const int *min, const int *max)
: minx(min[0]), miny(min[1]), minz(min[2]),
	maxx(max[0]), maxy(max[1]), maxz(max[2]),
	numberOfPokemons(0), divCrd('x'), 
	pokemon(0), firstHalf(0), secondHalf(0)
{
}

Region::Region(const Region &p)
: minx(p.minx), miny(p.miny), minz(p.minz),
	maxx(p.maxx), maxy(p.maxy), maxz(p.maxz),
	numberOfPokemons(p.numberOfPokemons),
	divCrd(p.divCrd),
	pokemon(p.pokemon ? new Pokemon(*p.pokemon) : 0),
	firstHalf(p.firstHalf ? new Region(*p.firstHalf) : 0),
	secondHalf(p.secondHalf ? new Region(*p.secondHalf) : 0)
{
}

Region::Region(int *mins, int *maxs, char nc)
: minx(mins[0]),miny(mins[1]),minz(mins[2]),maxx(maxs[0]),maxy(maxs[1]),maxz(maxs[2]),
	numberOfPokemons(0), pokemon(0),
	firstHalf(0), secondHalf(0)
{
	switch (nc)
	{
		case 'x':divCrd = minx==maxx ? (miny==maxy ? 'z':'y'): 'x'; break;
		case 'y':divCrd = miny==maxy ? (minz==maxz ? 'x':'z'): 'y'; break;
		case 'z':divCrd = minz==maxz ? (minx==maxx ? 'y':'x'): 'z'; break;
	}
}
Region& Region::operator=(const Region &p)
{
	Region t(p);
	swap(pokemon, t.pokemon);
	swap(firstHalf, t.firstHalf);
	swap(secondHalf, t.secondHalf);

	minx = p.minx; miny = p.miny; minz = p.minz;
	maxx = p.maxx; maxy = p.maxy; maxz = p.maxz;

	divCrd = p.divCrd;
	numberOfPokemons = p.numberOfPokemons;
	return *this;
}
Region::~Region()
{
	deleteRegion();
}

void Region::deleteRegion()
{
	delete pokemon; pokemon = 0;
	delete firstHalf; firstHalf = 0;
	delete secondHalf; secondHalf = 0;
}

int Region::getMinBorder(char c) const
{
	if 			(c == 'x') return minx;
	else if (c == 'y') return miny;
	else							 return minz;
}

int Region::getMaxBorder(char c) const
{
	if 			(c == 'x') return maxx;
	else if (c == 'y') return maxy;
	else							 return maxz;
}

void Region::placePokemon(const Pokemon &p, int x, int y, int z)
{
	if (minx == maxx && miny == maxy && minz == maxz)
	{
		pokemon = new Pokemon(p); numberOfPokemons++;
		return;
	}
	char nextcrd='\0';
	int crd=0, max=0, min=0, i=0;
	int mins[3] = {minx,miny,minz}, maxs[3] = {maxx,maxy,maxz};
	switch (divCrd)
	{
		case 'x': crd = x; max = maxx; min = minx; i = 0; nextcrd = 'y'; break;
		case 'y': crd = y; max = maxy; min = miny; i = 1; nextcrd = 'z'; break;
		case 'z': crd = z; max = maxz; min = minz; i = 2; nextcrd = 'x'; break;
	}
	int mid = (min+max)/2;
	Region* &half = (crd > mid) ? (static_cast<void>(mins[i] = mid+1), secondHalf) : (static_cast<void>(maxs[i] = mid), firstHalf);
	if (!half)
		half = new Region(mins, maxs, nextcrd);
	half->placePokemon(p,x,y,z); numberOfPokemons++;
}

int Region::getPokemonCount(const int *min, const int *max) const
{
	int sum = 0;
	for (int i = min[0]; i <= max[0]; i++)
		for (int j = min[1]; j <= max[1]; j++)
			for (int k = min[2]; k <= max[2]; k++)
				if (isPokemon(i,j,k))
					sum++;
	return sum;
}

bool Region::isPokemon(int x, int y, int z) const
{
	if (minx == maxx && miny == maxy && minz == maxz)
		return true;
	int crd=0, min=0, max=0;
	switch (divCrd)
	{
		case 'x': crd = x; min = minx; max = maxx; break;
		case 'y': crd = y; min = miny; max = maxy; break;
		case 'z': crd = z; min = minz; max = maxz; break;
	}
	Region*const &half = crd > (min+max)/2 ? secondHalf : firstHalf;
	return half ? half->isPokemon(x,y,z) : false;
}

Pokemon& Region::operator()(int x, int y, int z)
{
	if (minx == maxx && miny == maxy && minz == maxz)
	{
		Pokemon* p = pokemon;
		pokemon = 0;
		numberOfPokemons--;
		return *p;
	}
	int crd=0, min=0, max=0;
	switch (divCrd)
	{
		case 'x': crd = x; min = minx; max = maxx; break;
		case 'y': crd = y; min = miny; max = maxy; break;
		case 'z': crd = z; min = minz; max = maxz; break;
	}
	Region* &half = (crd > (min+max)/2) ? secondHalf : firstHalf;
	if (half)
	{
		Pokemon& p = (*half)(x,y,z);
		numberOfPokemons--;
		if (!half->numberOfPokemons)
		{
			delete half;
			half = 0;
		}
		return p;
	}
	else
		throw pokemonException();
}

Region Region::crop(const int *min, const int *max) const
{
	if (minx==min[0] && miny==min[1] && minz==min[2] &&
			maxx==max[0] && maxy==max[1] && maxz==max[2])
		return *this;
	int i=0;
	int Region::*m=0;
	switch (divCrd)
	{
		case 'x': i = 0; m = &Region::minx; break;
		case 'y': i = 1; m = &Region::miny; break;
		case 'z': i = 2; m = &Region::minz; break;
	}
	Region*const &half = (min[i] >= secondHalf->*m) ? secondHalf : firstHalf;
		return half->crop(min,max);
}

void Region::patch(Region r)
{
	*this = r;
}
