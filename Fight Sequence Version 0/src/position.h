#ifndef POSITION_H
#define POSITION_H

#include "enemy.h"
#include "slime.h"
#include "spike.h"
#include "laser.h"

void LoadLevelPositions(int currentLevel,Enemy goblin[], int &goblinCount,Slime slime[],int &slimeCount,Spike spike[],int &spikeCount,LaserTrap level1Lasers[],LaserTrap level2Lasers[],LaserTrap level3Lasers[],LaserTrap level4Lasers[]);
#endif