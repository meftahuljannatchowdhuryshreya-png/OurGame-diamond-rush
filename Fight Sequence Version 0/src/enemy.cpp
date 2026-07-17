#include "types.h"
#include "enemy.h"
#include "map.h"
#include "raylib.h"
#include "player.h"
#include <cmath>
#include <vector>
using namespace std;

void UpdateEnemy(Enemy &e, vector<vector<int>> grid,Player &player) {
    //death
    if(e.health <= 0)
{
    e.bullet.active = false;
    return;
}

    if(e.attackCooldown>0) {
        e.attackCooldown--;
    }

    const float TILE_SIZE=32.0;
   
    int topRow=e.position.y/TILE_SIZE;
    int bottomRow=(e.position.y+e.height-1)/TILE_SIZE;

//move
    if(e.moveRight) {
      int nextRightCol=(e.position.x+e.speed+e.width-1)/TILE_SIZE;
       if(grid[topRow][nextRightCol]!=0 ||grid[bottomRow][nextRightCol]!=0){
            e.moveRight=false;
        }else {
            e.position.x+=e.speed;
        }
    }
    else {
         int nextLeftCol=(e.position.x-e.speed)/TILE_SIZE;
        if(grid[topRow][nextLeftCol]!=0 ||grid[bottomRow][nextLeftCol]!=0) {
            e.moveRight=true;
        }else {
             e.position.x-=e.speed;
        }
    }
//bullet
    if(!e.bullet.active && e.attackCooldown==0) {
        e.bullet.active=true;
        e.bullet.distanceTravelled=0;
        e.bullet.position.y=e.position.y+e.height/2;
//attack right
          if(e.moveRight) {
            e.bullet.position.x=e.position.x+e.width;
            e.bullet.direction=1;
          }else {
             e.bullet.position.x=e.position.x-e.width;
            e.bullet.direction=-1;
          }

        e.attackCooldown=30;
    }

      if(e.health>0 && e.bullet.active) {
        e.bullet.position.x+=2*e.bullet.speed*e.bullet.direction;
        e.bullet.distanceTravelled+=2*e.bullet.speed;
      }
      //will disspear after sometime
      if(e.bullet.distanceTravelled>=250) {
        e.bullet.active=false;
      }
      //damage player
     Rectangle goblinRect = {
    e.position.x,
    e.position.y,
    e.width,
    e.height
};

Rectangle playerRect = {
    player.pos.x - player.size/2,
    player.pos.y - player.size/2,
    player.size,
    player.size
};

 Rectangle bulletRect = {
    e.bullet.position.x,
    e.bullet.position.y,
    8,
    8
};
//player-goblin
if (CheckCollisionRecs(playerRect, goblinRect))
{
    player.health-=0.5f;

    if (player.health < 0)
        player.health = 0;
}
//player-bullet
if (e.bullet.active &&
    CheckCollisionRecs(bulletRect, playerRect))
{
    player.health -= 1.0f;

    if (player.health < 0)
        player.health = 0;

    e.bullet.active = false;
}
}

void DrawEnemy(Enemy e) {
     if(e.health<=0){
        return;
    }
    DrawRectangle(e.position.x,e.position.y,e.width,e.height,GREEN);
    float barWidth=30;
    float barHeight=4;
    DrawRectangle(e.position.x-7,e.position.y-10,barWidth,barHeight,GRAY);
      DrawRectangle(e.position.x - 7, e.position.y - 10,(e.health / 50.0f) * barWidth,barHeight,RED );
    if(e.bullet.active) {
        DrawCircleV(e.bullet.position,5,RED);
    }
}
    //attack goblin
    void AttackEnemy(Player &player,Enemy &goblin) {
        Vector2 playerCenter={player.pos.x,player.pos.y};
        Vector2 goblinCenter={goblin.position.x+goblin.width/2,goblin.position.y+goblin.height/2};
        float distance=sqrt(pow(playerCenter.x-goblinCenter.x,2)+pow(playerCenter.y-goblinCenter.y,2));
        if(distance<=player.attackRange && player.isAttacking && player.attackTick==player.attackDuration-1){
            goblin.health-=10.0f;
            if(goblin.health<0){
                goblin.health=0;
            }
        }
    }