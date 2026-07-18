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
     float xp;
    float maxXp;
    int level;
    float damage;

};

struct FinalBoss {
    Vector2 pos;
    float speed;
    float health;
    float size;
    bool xpGiven;
};
struct Bullet
{
    Vector2 position;
    float speed;
    bool active;
    float damage;
    float distanceTravelled;
    float direction;
};
struct Enemy
{
    Vector2 position;
    float width;
    float height;
    float speed;
    int health;
    bool moveRight;
    float velocityY;
    bool onGround;
    Bullet bullet;
    int attackCooldown;
    bool xpGiven;
};
struct Slime
{
    Vector2 position;
    float width;
    float height;
    float health;
    bool moveRight;
    float speed;
    bool xpGiven;
};
struct Spike
{
    Vector2 position;
    float width;
    float height;
    float health;
};
struct LaserTrap
{
    Vector2 start;
    Vector2 end;
    bool active;
    int onTime;
    int offTime;
    int timer;
    float damage;
};
struct HealthBoost
{
    Vector2 position;
    float size;
    float boost;
    bool active;
};
struct Hornet
{
    Vector2 position;
    float width;
    float height;
    float normalSpeed;
    float dashSpeed;
    bool isDashing;
    int dashCooldown;
    int dashTime;
    Vector2 dashDirection;
    int health;
    bool xpGiven;
};

#ifndef TYPES_H
#define TYPES_H

// Menu screens
enum class MenuScreen
{
    MAIN_MENU,
    OPTIONS,
    SETTINGS,
    SCOREBOARD,
    PAUSE_MENU
};

enum class MenuAction
{
    NONE,

    NEW_GAME,
    CONTINUE_GAME,

    SHOW_CONTROLS,
    SHOW_TUTORIAL,
    SHOW_CREDITS,

    RESUME_GAME,
    RESTART_GAME,
    EXIT_TO_MAIN_MENU,

    QUIT_GAME
};


#endif
