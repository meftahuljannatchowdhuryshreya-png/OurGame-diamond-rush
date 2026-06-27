#ifndef TYPES_H
#define TYPES_H

#include "raylib.h"
//#include "raymath.h"
#include <string>
#include <vector>

//definition
enum TileType {
    TILE_EMPTY=0,
    TILE_WALL=1,
    TILE_SPEOBJECT=2,
    TILE_CAGE=3
};
//dec
struct Room {
    std::string name;
    int x;
    int y;
    int w;
    int h;
    Color color;
};
struct LevelData {
    int id;
    std::string name;
    int width;
    int height;
    float startX;
    float startY;
    std::vector<std::vector<int>>grid;
    std::vector<Room>rooms;
    Vector2 startPos;
    Vector2 key1Pos;
    Vector2 key2Pos;
    bool key2FromBoss;
    bool key1Collected;
    bool key2Collected;
    bool chestUnlocked;
    Vector2 doorPos;
    Vector2 chestPos;

};

struct Player {
    Vector2 pos;
    float size;
    float speed;
    std::string facing; // "up", "down", "left", "right"
    
    bool isJumping;
    float jumpTick;
    float zHeight;

    bool isCrawling;

    bool isAttacking;
    int attackTick;
    int attackDuration;
    float attackRange;
    int attackCooldown;
    
    float health;
    float maxHealth;
    int lives;
    bool isInvulnerable;
    int invulnerableTick;
    
    int score;
    bool hasKey;
};

struct FinalBoss {
    Vector2 pos;
    float speed;
    float health;
    float size;
};
#endif

