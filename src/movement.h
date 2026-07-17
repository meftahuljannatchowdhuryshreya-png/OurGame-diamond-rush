#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "types.hpp"
#include "audio.hpp"
#include <vector>


bool CheckWallIntersection(
    Vector2 pCandidate,
    const std::vector<std::vector<int>>& grid,
    float size
);


void UpdatePlayer(
    Player &p,
    const std::vector<std::vector<int>>& grid
);

#endif //MOVEMENT_H
