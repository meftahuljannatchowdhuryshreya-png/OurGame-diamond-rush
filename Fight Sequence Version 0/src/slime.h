#ifndef SLIME_H
#define SLIME_H

#include "types.h"

void UpdateSlime(Slime &slime,std::vector<std::vector<int>> grid,Player &player);
void DrawSlime(Slime slime);
void AttackSlime(Player &player, Slime &slime);

#endif