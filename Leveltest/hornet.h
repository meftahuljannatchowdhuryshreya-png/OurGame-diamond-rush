#ifndef HORNET_H
#define HORNET_H
#include "types.h"
#include "map.h"
#include <vector>
void UpdateHornet (Player &player,Hornet &hornet, std::vector<std::vector<int>> grid);
void AttackHornet(Player &player,Hornet &hornet);
void DrawHornet (Hornet hornet);

#endif 