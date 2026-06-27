#include "types.h"
#include "player.h"
#include "map.h"
#include <cmath>
#include <vector>

bool CheckWallIntersection(Vector2 pos, std::vector<std::vector<int>> grid, float size) {
    float halfS = size / 2.0f;
  
    Vector2 corners[4] = {
        { pos.x - halfS, pos.y - halfS }, //top-left
        { pos.x + halfS, pos.y - halfS }, //top-right
        { pos.x - halfS, pos.y + halfS }, //bottom-left
        { pos.x + halfS, pos.y + halfS }  //bottom-right
    };

    int tileW = 32;
    int tileH = 32;

    for (int i = 0; i < 4; i++) {
        int cellX = (int)(corners[i].x / tileW);
        int cellY = (int)(corners[i].y / tileH);

      
        if (cellX < 0 || cellX >= 32 || cellY < 0 || cellY >= 20) {
                  return true; }
        
        if (grid[cellY][cellX] == 1 || grid[cellY][cellX] == 2 || grid[cellY][cellX] == 3 || grid[cellY][cellX] == 4) {
                  return true; }
    }
    return false;
}

void UpdatePlayer(Player &p, std::vector<std::vector<int>> grid) {
   
   
    float adjustedSpeed = p.speed;

    Vector2 movement = { 0.0f, 0.0f };
 
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
        movement.y -= 1.0f;
    }
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
        movement.y += 1.0f;
    }
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        movement.x -= 1.0f;
    }
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        movement.x += 1.0f;
    }

    //Diagonal movement speed
    if (movement.x != 0.0f && movement.y != 0.0f) {
        movement.x *= 0.7071f;
        movement.y *= 0.7071f;
    }

    //Sliding movement
    Vector2 nextX = { p.pos.x + movement.x * adjustedSpeed, p.pos.y };
    if (!CheckWallIntersection(nextX, grid, p.size)) {
        p.pos.x = nextX.x;
    }
    
    Vector2 nextY = { p.pos.x, p.pos.y + movement.y * adjustedSpeed };
    if (!CheckWallIntersection(nextY, grid, p.size)) {
        p.pos.y = nextY.y;
    }

    if (p.attackCooldown > 0) p.attackCooldown--;

    if ((IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_X) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) && p.attackCooldown <= 0) {
        p.isAttacking = true;
        p.attackTick = p.attackDuration;
        p.attackCooldown = 60;
    }

    if (p.isAttacking) {
        p.attackTick--;
        if (p.attackTick <= 0) {
            p.isAttacking = false;
        }
    }
}
