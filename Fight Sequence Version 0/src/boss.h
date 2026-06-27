#ifndef BOSS_H
#define BOSS_H
#include "types.h"
#include "map.h"
#include <vector>
void UpdateBoss (Player &player, FinalBoss &boss, std::vector<std::vector<int>> grid);
void Laser (Player &p, Player &player, FinalBoss &boss);
void AttackBoss (Player &player, FinalBoss &boss);
void Bomb (Vector2 bombPos, Player &player);

#endif // BOSS_H