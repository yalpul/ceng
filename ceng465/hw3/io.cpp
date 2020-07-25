#include <sstream>
#include "io.hpp"

static int order = 1;

std::pair<std::vector<atom>, std::vector<atom>>
read_atoms(std::ifstream& ifs)
{
  std::string line;
  std::string atom_str("ATOM");
  std::string ter("TER");
  std::vector<atom> chain1;
  std::vector<atom> chain2;
  while (std::getline(ifs, line))
    if (line.compare(0, atom_str.length(), atom_str) == 0)
      break;
  if (line.compare(13, 2, "CB") == 0 ||
      (line.compare(13, 2, "CA") == 0 && line.compare(17, 3, "GLY") == 0))
    chain1.push_back(mk_atom(line));

  while (std::getline(ifs, line))
    if (line.compare(0, ter.length(), ter) == 0)
      break;
    else if (line.compare(0, atom_str.length(), atom_str) == 0 &&
        (line.compare(13, 2, "CB") == 0 ||
        (line.compare(13, 2, "CA") == 0 &&
         line.compare(17, 3, "GLY") == 0)))
      chain1.push_back(mk_atom(line));

  order = 1;
  while (std::getline(ifs, line))
    if (line.compare(0, atom_str.length(), atom_str) == 0)
      break;
  if (line.compare(13, 2, "CB") == 0 ||
      (line.compare(13, 2, "CA") == 0 && line.compare(17, 3, "GLY") == 0))
    chain2.push_back(mk_atom(line));
  while (std::getline(ifs, line))
    if (line.compare(0, 3, "TER") == 0)
      break;
    else if (line.compare(0, atom_str.length(), atom_str) == 0 &&
        (line.compare(13, 2, "CB") == 0 ||
        (line.compare(13, 2, "CA") == 0 &&
         line.compare(17, 3, "GLY") == 0)))
      chain2.push_back(mk_atom(line));
  return std::pair<std::vector<atom>, std::vector<atom>>(chain1, chain2);
}

atom mk_atom(const std::string& line)
{
  const char *p = line.c_str()+17;
  std::stringstream ss(line.substr(31, 23));
  float x, y, z;
  ss >> x >> y >> z;
  return atom(p, order++, x, y, z);
}
