#include<bits/stdc++.h>
#include "map.h"
#include "types.h"
#include "player.h"
#include "boss.h"
#include "enemy.h"
#include "slime.h"
#include "spike.h"
#include "laser.h"
#include "raylib.h"
#include "audio.h"
using namespace std;

int main (){
    constexpr int screenWidth = 1024;
    constexpr int screenHeight = 640;
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

    Enemy goblin;
    goblin.position={235.0f,235.0f};
    goblin.width=16.0f;
    goblin.height=32.0f;
    goblin.speed=1.0f;
    goblin.health=50.0f;
    goblin.velocityY=0;
    goblin.onGround=false;
    goblin.moveRight=true;
    goblin.bullet.active=false;
    goblin.bullet.speed=8;
    goblin.bullet.active=false;
    goblin.bullet.speed=7;
    goblin.bullet.damage=0.5f;
    goblin.attackCooldown=0;

    Slime slime;
    slime.position={200.0f,560.0f};
    slime.width=64.0f;
    slime.height=16.0f;
    slime.health=20.0f;
    slime.moveRight=true;
    slime.speed=1.5f;

    Spike spike;
    spike.position = {900.0f, 571.0f};
    spike.width = 64;
    spike.height = 16;
    spike.health = 1;

    LaserTrap level1Lasers[4];
    LaserTrap level2Lasers[5];
    LaserTrap level3Lasers[5];
    LaserTrap level4Lasers[4];
    for(int i=0;i<4;i++){
    level1Lasers[i].active = true;
    level4Lasers[i].active = true;
    
    level1Lasers[i].onTime = 180;     // 3 sec (60 FPS) 
    level4Lasers[i].onTime = 180;  

    level1Lasers[i].offTime = 120;    // 2 sec
    level4Lasers[i].offTime = 120; 

    level1Lasers[i].timer = 0;
    level4Lasers[i].timer = 0;

    level1Lasers[i].damage = 0.7f;
    level4Lasers[i].damage = 0.99f;
//level 1 lasers
    level1Lasers[0].start={306,452};
    level1Lasers[0].end={306,504};
    level1Lasers[1].start={331,240};
    level1Lasers[1].end={408,240};
    level1Lasers[2].start={611,368};
    level1Lasers[2].end={665,368};
    level1Lasers[3].start={755,264};
    level1Lasers[3].end={755,311};
     //level 4 laser
    level4Lasers[0].start={528,388};
    level4Lasers[0].end={528,476};
    level4Lasers[1].start={656,108};
    level4Lasers[1].end={656,188};
    level4Lasers[2].start={656,300};
    level4Lasers[2].end={656,380};
    level4Lasers[3].start={656,452};
    level4Lasers[3].end={656,508};
    }

    for(int i=0;i<5;i++)
{
    level2Lasers[i].active=true;
    level3Lasers[i].active = true;

    level2Lasers[i].onTime = 180; 
    level3Lasers[i].onTime=180;

    level2Lasers[i].offTime = 120;
    level3Lasers[i].offTime=120;
    
    level2Lasers[i].timer = 0;
    level3Lasers[i].timer=0;

    level2Lasers[i].damage = 0.9f;
    level3Lasers[i].damage=0.3f;

    //level 2 laser
    level2Lasers[0].start={400,172};
    level2Lasers[0].end={400,220};
    level2Lasers[1].start={592,172};
    level2Lasers[1].end={592,252};
    level2Lasers[2].start={400,300};
    level2Lasers[2].end={400,380};
    level2Lasers[3].start={400,490};
    level2Lasers[3].end={400,540};
    level2Lasers[4].start={592,388};
    level2Lasers[4].end={592,472};
    //level 3 laser
    level3Lasers[0].start={326,208};
    level3Lasers[0].end={412,208};
    level3Lasers[1].start={432,106};
    level3Lasers[1].end={432,156};
    level3Lasers[2].start={708,238};
    level3Lasers[2].end={798,238};
    level3Lasers[3].start={900,432};
    level3Lasers[3].end={958,432};
    level3Lasers[4].start={134,400};
    level3Lasers[4].end={189,400};
    }
 

    Player playerCopy = player;
    FinalBoss bossCopy = boss;
    Enemy goblinCopy=goblin;
    Slime slimeCopy=slime;


    
    Image bossImage = LoadImage("boss.png");
    ImageResize(&bossImage, boss.size, boss.size);
    Texture2D bossTexture = LoadTextureFromImage(bossImage);
    UnloadImage(bossImage);

    int cnt = 0;
    Image bombImage = LoadImage("bomb.png");
    ImageResize(&bombImage, tile, tile);
    Texture2D bombtexture = LoadTextureFromImage(bombImage);
    UnloadImage(bombImage);

    Image noAttack = LoadImage("noattack.png");
    ImageResize(&noAttack, player.size, player.size);
    Texture2D noAttackTexture = LoadTextureFromImage(noAttack);
    UnloadImage(noAttack);

    Image leftAttack = LoadImage("leftattack.png");
    ImageResize(&leftAttack, player.size, player.size);
    Texture2D leftAttackTexture = LoadTextureFromImage(leftAttack);
    UnloadImage(leftAttack);

    Image rightAttack = LoadImage("rightattack.png");
    ImageResize(&rightAttack, player.size, player.size);
    Texture2D rightAttackTexture = LoadTextureFromImage(rightAttack);
    UnloadImage(rightAttack);

    bool gameOver = false;
    bool victory = false;
    int currentLevel=0;
    Vector2 bombPos; Player p;
    Vector2 bomb2Pos, bomb3Pos;

    while (!WindowShouldClose()) {
        cnt = (cnt + 1) % 200;
        
        if (cnt==0){
            p = player;
            bombPos.x = GetRandomValue((int)boss.pos.x-50, (int)boss.pos.x+50);
            bombPos.y = GetRandomValue((int)boss.pos.y-50, (int)boss.pos.y+50);
            bomb2Pos.x = GetRandomValue((int)boss.pos.x-100, (int)boss.pos.x+100);
            bomb2Pos.y = GetRandomValue((int)boss.pos.y-100, (int)boss.pos.y+100);
            bomb3Pos.x = GetRandomValue((int)boss.pos.x-200, (int)boss.pos.x+200);
            bomb3Pos.y = GetRandomValue((int)boss.pos.y-200, (int)boss.pos.y+200);
        }
        
        if (IsKeyPressed(KEY_R))
            {
                player = playerCopy;
                boss = bossCopy;
                goblin=goblinCopy;
                slime=slimeCopy;
                gameOver = false;
                victory = false;
                cnt = 0;
            }
        BeginDrawing();
        ClearBackground(BLACK);
        UpdateAudio();
        //CHANGE LEVEL
        if(IsKeyPressed(KEY_ONE))
        currentLevel=0;
         if(IsKeyPressed(KEY_TWO))
        currentLevel=1;
         if(IsKeyPressed(KEY_THREE))
        currentLevel=2;
         if(IsKeyPressed(KEY_FOUR))
        currentLevel=3;

        if (!gameOver && !victory){
            DrawLevel(maplist[currentLevel]);
            // Draw Player
            if (player.isAttacking || player.attackCooldown>0){
                if (player.pos.x<=boss.pos.x) DrawTexture (rightAttackTexture, player.pos.x-player.size/2, player.pos.y-player.size/2, WHITE);
                else DrawTexture (leftAttackTexture, player.pos.x-player.size/2, player.pos.y-player.size/2, WHITE);
            }
            else {
                DrawTexture (noAttackTexture, player.pos.x-player.size/2, player.pos.y-player.size/2, WHITE);
            }
            // Draw Boss
            if(currentLevel==3 ) {
            DrawTexture(bossTexture, boss.pos.x, boss.pos.y, WHITE);
            }
            UpdatePlayer(player, maplist[currentLevel].grid);
            
           
            // Laser Attack

            if (cnt < 60 && currentLevel==3) {
                Laser(p, player, boss); // Call the Laser function to draw the laser attack
            }
            if(currentLevel==3) {
            UpdateBoss(player, boss, maplist[currentLevel].grid);
            // Attacking the Boss
            AttackBoss(player, boss);
            }
            //enemy
             UpdateEnemy(goblin,maplist[currentLevel].grid,player);
             AttackEnemy(player, goblin);
             DrawEnemy(goblin);

             UpdateSlime(slime,maplist[currentLevel].grid,player);
             AttackSlime(player,slime);
             DrawSlime(slime);

             UpdateSpike(spike, player);
             DrawSpike(spike);
             //laser for levels
             if(currentLevel==0) {
             for(int i=0;i<4;i++) {
             UpdateLaserTrap(level1Lasers[i], player);
             DrawLaserTrap(level1Lasers[i]);
             }
            }else if(currentLevel==1) {
                 for(int i=0;i<5;i++) {
             UpdateLaserTrap(level2Lasers[i], player);
             DrawLaserTrap(level2Lasers[i]);
             } 
            } else if(currentLevel==2) {
                  for(int i=0;i<5;i++) {
             UpdateLaserTrap(level3Lasers[i], player);
             DrawLaserTrap(level3Lasers[i]);
             }
            } else if(currentLevel==3) {
                  for(int i=0;i<4;i++) {
             UpdateLaserTrap(level4Lasers[i], player);
             DrawLaserTrap(level4Lasers[i]);
             }
            }
            // Draw Bomb
            if (cnt<150 && currentLevel==3){
                if (!CheckWallIntersection({bombPos.x+tile/2, bombPos.y+tile/2}, maplist[currentLevel].grid, tile)){
                DrawTexture(bombtexture, bombPos.x, bombPos.y, WHITE); 
                }
                if (boss.health<=100 && !CheckWallIntersection({bomb2Pos.x+tile/2, bomb2Pos.y+tile/2}, maplist[currentLevel].grid, tile)){
                DrawTexture(bombtexture, bomb2Pos.x, bomb2Pos.y, WHITE); 
                }
                if (boss.health<=50 && !CheckWallIntersection({bomb3Pos.x+tile/2, bomb3Pos.y+tile/2}, maplist[currentLevel].grid, tile)){
                DrawTexture(bombtexture, bomb3Pos.x, bomb3Pos.y, WHITE); 
                } 
            }

            // Simulate Bomb Explosion
            if (cnt==150 && currentLevel==3){
                if (!CheckWallIntersection({bombPos.x+tile/2, bombPos.y+tile/2}, maplist[currentLevel].grid, tile)){
                    Bomb(bombPos, player);
                }
                if (boss.health<=100 && !CheckWallIntersection({bomb2Pos.x+tile/2, bomb2Pos.y+tile/2}, maplist[currentLevel].grid, tile)){
                    Bomb(bomb2Pos, player);
                }
                if (boss.health<=50 && !CheckWallIntersection({bomb3Pos.x+tile/2, bomb3Pos.y+tile/2}, maplist[currentLevel].grid, tile)){
                    Bomb(bomb3Pos, player);
                }
            }
        }
        // Health
        DrawText(TextFormat("XP: %.1f", player.health), 20, 20, 30, GREEN);
        if(currentLevel==3)
        DrawText(TextFormat("Boss HP: %.1f", boss.health), 20, 60, 30, BLUE);
        if (player.health<=0) gameOver = true;
        if(currentLevel==3) {
        if (boss.health<=0) victory = true;
        }
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

