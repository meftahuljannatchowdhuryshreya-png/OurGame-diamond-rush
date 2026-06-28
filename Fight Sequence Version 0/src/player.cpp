#include "types.h"
#include "player.h"
#include "map.h"
#include <cmath>
#include <vector>
using namespace std;

bool CheckWallIntersection(Vector2 pos, vector<vector<int>> grid, float size) {
  
    Vector2 corners[4] = {
        { pos.x - size/2, pos.y - size/2 }, //top-left
        { pos.x + size/2, pos.y - size/2}, //top-right
        { pos.x - size/2, pos.y + size/2}, //bottom-left
        { pos.x + size/2, pos.y + size/2}  //bottom-right
    };

    for (int i = 0; i < 4; i++) {

        int cellX = (int)(corners[i].x / tile);
        int cellY = (int)(corners[i].y / tile);
      
        if (cellX < 0 || cellX >= 32 || cellY < 0 || cellY >= 20) {
            return true;
        }
        
        if (!grid[cellY][cellX] == 0){
            return true;
        }
    }
    return false;
}

void UpdatePlayer(Player &p, vector<vector<int>> grid) {
   
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
    Vector2 next = { p.pos.x + movement.x * adjustedSpeed, p.pos.y + movement.y * adjustedSpeed };
    if (!CheckWallIntersection(next, grid, p.size)) {
        p.pos = next;
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
