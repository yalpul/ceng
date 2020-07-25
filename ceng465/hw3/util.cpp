#include "util.hpp"

int unvisited_exists(const std::vector<bool>& visited)
{
  for (size_t i = 0; i < visited.size(); i++)
    if (visited[i] == false)
      return i;
  return -1;
}

bool interacting(const interaction& a, const interaction& b)
{
  return a.first.interacting(b.first)
      || a.first.interacting(b.second)
      || a.second.interacting(b.first)
      || a.second.interacting(b.second);
}

std::vector<std::set<interaction>>
find_hotspots(const std::vector<interaction>& interactions)
{
  int idx;
  std::vector<bool> visited(interactions.size(), false);
  std::vector<std::set<interaction>> hotspots;
  while ((idx = unvisited_exists(visited)) != -1) {
    visited[idx] = true;
    const interaction& pivot = interactions[idx];
    hotspots.push_back(find_set(pivot, interactions, visited));
  }
  return hotspots;
}

bool operator<(const interaction& a, const interaction& b)
{
  int comp = a.first.compare(b.first);
  if (comp < 0)
    return true;
  else if (comp > 0)
    return false;
  else
    comp = a.second.compare(b.second);
  if (comp < 0)
    return true;
  else
    return false;
}

std::set<interaction> find_set
(const interaction& pivot,
 const std::vector<interaction>& interactions,
 std::vector<bool>& visited)
{
  std::set<interaction> group = {pivot}, current = {pivot};
  while (current.size() > 0) {
    std::set<interaction> next;
    for (const auto& p : current)
      for (size_t i = 0; i < interactions.size(); i++)
        if (visited[i] == false && interacting(p, interactions[i])) {
            group.insert(interactions[i]);
            next.insert(interactions[i]);
            visited[i] = true;
          }
    current = std::move(next);
  }
  return group;
}

std::vector<interaction> find_interactions
(const std::pair<std::vector<atom>, std::vector<atom>>& atoms)
{
  std::vector<interaction> interactions;
  for (const atom& a : atoms.first)
    for (const atom& b : atoms.second)
      if (a.interacting(b))
        interactions.push_back(interaction(a, b));

  return interactions;
}
