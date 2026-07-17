#ifndef ENEMY_H
#define ENEMY_H

#include "types.h"
#include "map.h"
#include <vector>

void UpdateEnemy(Enemy &e,std::vector<std::vector<int>>grid,Player &player);
void AttackEnemy (Player &player, Enemy &goblin);
void DrawEnemy(Enemy e);

#endif
