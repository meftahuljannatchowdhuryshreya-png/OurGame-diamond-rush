#ifndef MAP_H
#define MAP_H

#include <vector>
#include "types.h"

extern std::vector<LevelData>maplist;
void Levelconfig();
void DrawLevel(LevelData level, float tile);

#endif