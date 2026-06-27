#include "map.h"
#include "types.h"
#include "player.h"
#include "raylib.h"
#include "boss.h"
#include <vector>
#include <cmath>

void UpdateBoss (Player &player, FinalBoss &boss, std::vector<std::vector<int>> grid){
    Vector2 next = boss.pos;
    if (boss.pos.x < player.pos.x) {
        next.x += boss.speed;
    } else if (boss.pos.x > player.pos.x) {
        next.x -= boss.speed;
    }
    if (boss.pos.y < player.pos.y) {
        next.y += boss.speed;
    } else if (boss.pos.y > player.pos.y) {
        next.y -= boss.speed;
    }
    next.x += boss.size/2;
    next.y += boss.size/2;
    if (!CheckWallIntersection(next, grid, boss.size)) {
        boss.pos.x = next.x - boss.size/2;
        boss.pos.y = next.y - boss.size/2;
    }
    else {
        next = boss.pos;
            if (boss.pos.x < player.pos.x) {
            next.x += boss.speed;
        } else if (boss.pos.x > player.pos.x) {
            next.x -= boss.speed;
        }
        next.x += boss.size/2;
        next.y += boss.size/2;
        if (!CheckWallIntersection(next, grid, boss.size)) {
            boss.pos.x = next.x - boss.size/2;
        }
        else {
            next = boss.pos;
            if (boss.pos.y < player.pos.y) {
                next.y += boss.speed;
            } else if (boss.pos.y > player.pos.y) {
                next.y -= boss.speed;
            }
            next.x += boss.size/2;
            next.y += boss.size/2;
            if (!CheckWallIntersection(next, grid, boss.size)) {
                boss.pos.y = next.y - boss.size/2;
            }
        }

    }
}

void Laser (Player &p, Player &player, FinalBoss &boss){
    Vector2 dir = {p.pos.x + player.size/2 - boss.pos.x - boss.size/2, p.pos.y + player.size/2 - boss.pos.y - boss.size/2};
    float length = sqrt(dir.x * dir.x + dir.y * dir.y);
    if (length > 0.001f) {
        dir.x /= length;
        dir.y /= length;
    }
    Vector2 p1 = {boss.pos.x + boss.size/2 - dir.x * 1000, boss.pos.y + boss.size/2 - dir.y * 1000};
    Vector2 p2 = {boss.pos.x + boss.size/2 + dir.x * 1000, boss.pos.y + boss.size/2 + dir.y * 1000};
    DrawLineV(p1, p2, RED);

    Vector2 perp = {-dir.y, dir.x};
    Vector2 q1 = {boss.pos.x + boss.size/2 - perp.x * 1000, boss.pos.y + boss.size/2 - perp.y * 1000};
    Vector2 q2 = {boss.pos.x + boss.size/2 + perp.x * 1000, boss.pos.y + boss.size/2 + perp.y * 1000};
    DrawLineV(q1, q2, RED);

    const float c = 0.70710678f;
    Vector2 dir45 = {dir.x * c - dir.y * c, dir.x * c + dir.y * c};
    Vector2 r1 = {boss.pos.x + boss.size/2 - dir45.x * 1000, boss.pos.y + boss.size/2 - dir45.y * 1000};
    Vector2 r2 = {boss.pos.x + boss.size/2 + dir45.x * 1000, boss.pos.y + boss.size/2 + dir45.y * 1000};
    DrawLineV(r1, r2, RED);

    Vector2 dirNeg45 = {dir.x * c + dir.y * c, -dir.x * c + dir.y * c};
    Vector2 s1 = {boss.pos.x + boss.size/2 - dirNeg45.x * 1000, boss.pos.y + boss.size/2 - dirNeg45.y * 1000};
    Vector2 s2 = {boss.pos.x + boss.size/2 + dirNeg45.x * 1000, boss.pos.y + boss.size/2 + dirNeg45.y * 1000};
    DrawLineV(s1, s2, RED);

    Vector2 center = {player.pos.x + player.size/2, player.pos.y + player.size/2};

    if (CheckCollisionCircleLine(center, player.size/2, p1, p2) ||
        CheckCollisionCircleLine(center, player.size/2, q1, q2) ||
        CheckCollisionCircleLine(center, player.size/2, r1, r2) ||
        CheckCollisionCircleLine(center, player.size/2, s1, s2))
    {
        player.health -= 0.1f;

        if (player.health < 0)
            player.health = 0;
    }
}

void Bomb (Vector2 bombPos, Player &player) {
    float bombRadius = 90.0f;
    bombPos = {bombPos.x+ 16, bombPos.y+ 16};

    DrawCircleV(
        bombPos,
        bombRadius,
        Fade(ORANGE, 255)
    );
    DrawCircleV(
        bombPos,
        bombRadius * 0.65f,
        Fade(YELLOW, 255)
    );

    Vector2 playerCenter = {player.pos.x + player.size/2, player.pos.y + player.size/2};
    float distance = sqrt(pow(playerCenter.x - bombPos.x, 2) + pow(playerCenter.y - bombPos.y, 2));

    if (distance <= bombRadius+player.size/2) {
        player.health -= 10.0f; // Reduce the player's health by 1
        if (player.health < 0)
            player.health = 0;
    }
}

void AttackBoss (Player &player, FinalBoss &boss){
    Vector2 playerCenter = {player.pos.x + player.size/2, player.pos.y + player.size/2};
    Vector2 bossCenter = {boss.pos.x + boss.size/2, boss.pos.y + boss.size/2};

    float distance = sqrt(pow(playerCenter.x - bossCenter.x, 2) + pow(playerCenter.y - bossCenter.y, 2));

    if (distance <= player.attackRange && player.isAttacking) {
        boss.health -= 10.0f; // Reduce the boss's health by 10
        if (boss.health < 0)
            boss.health = 0;
    }
}