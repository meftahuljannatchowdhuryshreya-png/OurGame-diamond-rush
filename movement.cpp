#include "types.h"
#include "movement.h"
//#include "audio.hpp"
#include "map.h"
#include <cmath>
#include <vector>

bool CheckWallIntersection(Vector2 pCandidate, std::vector<std::vector<int>> grid, float size) {
    float halfS = size / 2.0f;
  
    Vector2 corners[4] = {
        { pCandidate.x - halfS, pCandidate.y - halfS }, //top-left
        { pCandidate.x + halfS, pCandidate.y - halfS }, //top-right
        { pCandidate.x - halfS, pCandidate.y + halfS }, //bottom-left
        { pCandidate.x + halfS, pCandidate.y + halfS }  //bottom-right
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
    if (p.isCrawling) adjustedSpeed *= 2.0f; //will fix these 2 after deciding p.speed
    if (p.isJumping) adjustedSpeed *= 4.11f;

    Vector2 movement = { 0.0f, 0.0f };
 
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
        movement.y -= 1.0f;
        p.facing = "up";
    }
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
        movement.y += 1.0f;
        p.facing = "down";
    }
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        movement.x -= 1.0f;
        p.facing = "left";
    }
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        movement.x += 1.0f;
        p.facing = "right";
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

  
    // if ((IsKeyPressed(KEY_J) || IsKeyPressed(KEY_Z)) && !p.isJumping && !p.isCrawling) {
    //     p.isJumping = true;
    //     p.jumpTick = 0;
    //     PlayGameSFX(sfxJump);
    // }

    // if (p.isJumping) {
    //     p.jumpTick += 1.0f;
    //     // Parabolic arc for height trajectory
    //     float duration = 30.0f; // ticks
    //     if (p.jumpTick >= duration) {
    //         p.isJumping = false;
    //         p.zHeight = 0;
    //     } else {
    //         p.zHeight = sinf((p.jumpTick / duration) * 3.14159f) * 45.0f; // Max jump height 45px
    //     }
    // }

  
    // if ((IsKeyDown(KEY_K) || IsKeyDown(KEY_C)) && !p.isJumping) {
    //     if (!p.isCrawling) {
    //         p.isCrawling = true;
    //         PlayGameSFX(sfxCrawl);
    //     }
    // } else {
    //     p.isCrawling = false;
    // }
