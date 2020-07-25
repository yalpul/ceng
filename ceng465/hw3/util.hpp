#ifndef _UTIL_HPP_
#define _UTIL_HPP_

#include <vector>
#include <set>
#include "atom.hpp"

using interaction = std::pair<atom,atom>;

std::vector<interaction> find_interactions
(const std::pair<std::vector<atom>, std::vector<atom>>& atoms);

int unvisited_exists(const std::vector<bool>& visited);
bool interacting(const interaction& a, const interaction& b);

std::vector<std::set<interaction>>
find_hotspots(const std::vector<interaction>& interactions);

bool operator<(const interaction& a, const interaction& b);

std::set<interaction> find_set
(const interaction& pivot,
 const std::vector<interaction>& interactions,
 std::vector<bool>& visited);

#endif
