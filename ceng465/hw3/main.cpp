#include <iostream>
#include <vector>
#include <fstream>
#include <set>

#include "atom.hpp"
#include "io.hpp"
#include "util.hpp"


int main(int argc, char **argv)
{
  if (argc != 2) {
    std::cerr << "File name needed as argument" << std::endl;
    return 1;
  }
  std::ifstream ifs(argv[1]);
  if (!ifs.good()) {
    std::cerr << "Error opening file" << std::endl;
    return 1;
  }

  std::pair<std::vector<atom>, std::vector<atom>> atoms = read_atoms(ifs);
  std::vector<interaction> interactions =
    find_interactions(atoms);

  int grp = 1;
  std::vector<std::set<interaction>> hotspots = find_hotspots(interactions);
  for (const auto& set : hotspots) {
    std::cout << "There are " << set.size()
      << " interacting pairs." << std::endl;
    for (const auto& i : set)
      std::cout << "Group " << grp << ": "
        << i.first << '-' << i.second << std::endl;
    grp++;
  }
  std::cout << "Number of groups = " << hotspots.size() << std::endl;
}
