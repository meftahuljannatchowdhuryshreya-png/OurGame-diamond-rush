#include<bits/stdc++.h>
#include "map.h"
#include "types.h"
#include "player.h"
#include "boss.h"
#include "raylib.h"
#include "audio.h"
using namespace std;

int main (){
    constexpr int screenWidth = 1024;
    constexpr int screenHeight = 648;
    float tile = 32.0f;
    InitWindow(screenWidth, screenHeight, "Game");
    InitAudio();
    SetTargetFPS(60);
    Levelconfig();
    Player player;
    player.pos = {480.0f, 448.0f};
    player.size = 24.0f;
    player.speed = 4.0f;
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

    Player playerCopy = player;
    FinalBoss bossCopy = boss;


    
    Image bossImage = LoadImage("boss.png");
    ImageResize(&bossImage,tile, tile);
    Texture2D bossTexture = LoadTextureFromImage(bossImage);
    UnloadImage(bossImage);

    int cnt = 0;
    Image bombImage = LoadImage("bomb.png");
    ImageResize(&bombImage, tile, tile);
    Texture2D bombtexture = LoadTextureFromImage(bombImage);
    UnloadImage(bombImage);

    Image noAttack = LoadImage("noattack.png");
    ImageResize(&noAttack, tile, tile);
    Texture2D noAttackTexture = LoadTextureFromImage(noAttack);
    UnloadImage(noAttack);

    Image leftAttack = LoadImage("leftattack.png");
    ImageResize(&leftAttack, tile, tile);
    Texture2D leftAttackTexture = LoadTextureFromImage(leftAttack);
    UnloadImage(leftAttack);

    Image rightAttack = LoadImage("rightattack.png");
    ImageResize(&rightAttack, tile, tile);
    Texture2D rightAttackTexture = LoadTextureFromImage(rightAttack);
    UnloadImage(rightAttack);

    bool gameOver = false;
    bool victory = false;

    Vector2 bombPos; Player p;

    while (!WindowShouldClose()) {
        cnt = (cnt + 1) % 200;
        
        if (cnt==0){
            p = player;
            bombPos.x = GetRandomValue((int)boss.pos.x-50, (int)boss.pos.x+50);
            bombPos.y = GetRandomValue((int)boss.pos.y-50, (int)boss.pos.y+50);
        }
        
        if (IsKeyPressed(KEY_R))
            {
                player = playerCopy;
                boss = bossCopy;
                gameOver = false;
                victory = false;
                cnt = 0;
            }
        BeginDrawing();
        ClearBackground(BLACK);
        UpdateAudio();
        if (!gameOver && !victory){
            DrawLevel(maplist[3], tile);
            // Draw Player
            if (player.isAttacking || player.attackCooldown>0){
                if (player.pos.x<=boss.pos.x) DrawTexture (rightAttackTexture, player.pos.x-player.size/2, player.pos.y-player.size/2, WHITE);
                else DrawTexture (leftAttackTexture, player.pos.x-player.size/2, player.pos.y-player.size/2, WHITE);
            }
            else {
                DrawTexture (noAttackTexture, player.pos.x-player.size/2, player.pos.y-player.size/2, WHITE);
            }
            // Draw Boss
            DrawTexture(bossTexture, boss.pos.x, boss.pos.y, WHITE);
            UpdatePlayer(player, maplist[3].grid);
            // Laser Attack
            if (cnt < 60) {
                Laser(p, player, boss); // Call the Laser function to draw the laser attack
            }
            UpdateBoss(player, boss, maplist[3].grid);
            // Attacking the Boss
            AttackBoss(player, boss);

            // Draw Bomb
            if (cnt<150){
                if (!CheckWallIntersection({bombPos.x+tile/2, bombPos.y+tile/2}, maplist[3].grid, tile)){
                DrawTexture(bombtexture, bombPos.x, bombPos.y, WHITE); 
                }// Draw the bomb position as an orange circle
            }

            // Simulate Bomb Explosion
            if (cnt==150){
                if (!CheckWallIntersection({bombPos.x+tile/2, bombPos.y+tile/2}, maplist[3].grid, 2*tile)){
                    Bomb(bombPos, player);
                } // Call the Bomb function to draw the bomb attack
            }
        }
        // Health
        DrawText(TextFormat("XP: %.1f", player.health), 20, 20, 30, GREEN);
        DrawText(TextFormat("Boss HP: %.1f", boss.health), 20, 60, 30, BLUE);
        if (player.health<=0) gameOver = true;
        else if (boss.health<=0) victory = true;
        if (gameOver)
        {
            DrawText("GAME OVER", 240, 150, 50, RED);
            DrawText("Press R to Restart", 210, 220, 30, WHITE);
        }
        else if (victory){
            DrawText("VICTORY", 240, 150, 50, GREEN);
        }
        EndDrawing();
}
    UnloadTexture(bossTexture);
    UnloadTexture(bombtexture);
    UnloadTexture(noAttackTexture);
    UnloadTexture(leftAttackTexture);
    UnloadTexture(rightAttackTexture);
    CloseWindow();
    CloseAudio();
}
