#ifndef UPGRADE_H
#define UPGRADE_H

#include "types.h"
#include "map.h"

void UpdateXP(Player &player);
void DrawXPBar(Player &player);
void SpawnHealthBoost(Player &player,HealthBoost &boost, int currentLevel,std::vector<std::vector<int>> &grid);
void UpdateHealthBoost(Player &player, HealthBoost &boost);
void DrawHealthBoost(HealthBoost boost);
#endif