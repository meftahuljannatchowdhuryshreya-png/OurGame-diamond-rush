#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"
#include "map.h"
#include <vector>

bool CheckWallIntersection(Vector2 pCandidate, std::vector<std::vector<int>> grid, float size);
void UpdatePlayer(Player &p, std::vector<std::vector<int>> grid);


#endif // PLAYER_H