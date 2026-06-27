#ifndef TYPES_H
#define TYPES_H

#include "raylib.h"
#include <string>
#include <vector>

struct LevelData {
    std::vector<std::vector<int>>grid;
};

struct Player {
    Vector2 pos;
    float size;
    float speed;
    bool isAttacking;
    int attackTick;
    int attackDuration;
    float attackRange;
    int attackCooldown;
    
    float health;
};

struct FinalBoss {
    Vector2 pos;
    float speed;
    float health;
    float size;
};
#endif
