#ifndef _IO_HPP_
#define _IO_HPP_

#include <vector>
#include <string>
#include <fstream>

#include "atom.hpp"

atom mk_atom(const std::string& line);

std::pair<std::vector<atom>, std::vector<atom>>
read_atoms(std::ifstream& ifs);

#endif
