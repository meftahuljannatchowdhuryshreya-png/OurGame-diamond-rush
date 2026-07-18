#include<bits/stdc++.h>
#include "map.h"
#include "tiledmap.h"
#include "types.h"
#include "player.h"
#include "boss.h"
#include "raylib.h"
using namespace std;

int main (){
    constexpr int screenWidth = 1024;
    constexpr int screenHeight = 648;
    float tile = 32.0f;
    InitWindow(screenWidth, screenHeight, "Game");
    SetTargetFPS(60);
    Texture2D tileset = LoadTexture("ChatGPT Image Jul 17, 2026, 10_46_00 PM.png");
int tilesetColumns = tileset.width / 32;
    
    Levelconfig();
    Player player;
    player.pos = {480.0f, 448.0f};
    player.size = 24.0f;
    player.speed = 4.0f;
    player.facing = "down";
    player.isJumping = false;
    player.jumpTick = 0.0f;
    player.zHeight = 0.0f;
    player.isCrawling = false;
    player.isAttacking = false;
    player.attackTick = 0;
    player.attackDuration = 2; //duration of attack in frames
    player.attackRange = 32.0f; //range of attack
    player.attackCooldown = 60; //cooldown time in frames
    player.health = 100.0f;

    FinalBoss boss;
    boss.pos = {200.0f, 200.0f};
    boss.speed = 2.0f;
    boss.health = 200.0f;
    boss.size = 32.0f;

    /*
    Image img = LoadImage("boss.png");
    ImageResize(&img,tile, tile);
    Texture2D bossTexture = LoadTextureFromImage(img);
    UnloadImage(img);
    */


    int cnt = 0;

    while (!WindowShouldClose()) {
        cnt = (cnt + 1) % 200;
        Vector2 bombPos; Player p;
        if (cnt==0){
            p = player;
            bombPos.x = GetRandomValue((int)boss.pos.x-50, (int)boss.pos.x+50);
            bombPos.y = GetRandomValue((int)boss.pos.y-50, (int)boss.pos.y+50);
        }
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTileMap(tileset); // Draw the fourth level in the maplist
        DrawCircle(player.pos.x, player.pos.y, player.size/2, YELLOW); // Draw the player as a yellow circle
        DrawRectangle(boss.pos.x, boss.pos.y, boss.size, boss.size, RED); // Draw the boss as a red square
        //DrawTexture(bossTexture, boss.pos.x, boss.pos.y, WHITE);
        UpdatePlayer(player, maplist[3].grid); // Update player position based on the fourth level's grid
        if (cnt < 60) {
            Laser(p, player, boss); // Call the Laser function to draw the laser attack
        }
        UpdateBoss(player, boss, maplist[3].grid); // Update boss position based on the fourth level's grid
        AttackBoss(player, boss); // Check if the player is attacking the boss
        if (cnt<150){
            DrawCircle(bombPos.x, bombPos.y, 5.0f, YELLOW); // Draw the bomb position as an orange circle
        }
        if (cnt==150){
            Bomb(bombPos, player); // Call the Bomb function to draw the bomb attack
        }
        DrawText(TextFormat("XP: %.1f", player.health), 20, 20, 30, GREEN);
        DrawText(TextFormat("Boss HP: %.1f", boss.health), 20, 60, 30, BLUE);

        EndDrawing();
    }
    UnloadTexture(tileset);
CloseWindow();

return 0;
}
