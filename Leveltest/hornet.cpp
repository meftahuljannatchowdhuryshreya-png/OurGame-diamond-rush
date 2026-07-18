#include "map.h"
#include "types.h"
#include "player.h"
#include "raylib.h"
#include "hornet.h"
#include <vector>
#include <cmath>
using namespace std;
void UpdateHornet (Player &player,Hornet &hornet, std::vector<std::vector<int>> grid) {
    if(hornet.health<=0) return; //dead
    if(hornet.dashCooldown>0) hornet.dashCooldown--;
    //dash
    if(!hornet.isDashing && hornet.dashCooldown==0) { //start
        Vector2 dir={player.pos.x-hornet.position.x,player.pos.y-hornet.position.y};
        float distance=sqrt(dir.x*dir.x+dir.y*dir.y);
        if(distance>0) {
            dir.x/=distance;//to prevent quickly appearing
            dir.y/=distance;
        } 
        hornet.dashDirection=dir;
        hornet.isDashing=true;
        hornet.dashTime=30;
    }
    Vector2 next=hornet.position; 
     //dashing
    if(hornet.isDashing) {
        next.x+=hornet.dashDirection.x*hornet.dashSpeed;
        next.y+=hornet.dashDirection.y*hornet.dashSpeed;
        hornet.dashTime--;//decrease dash time
        if(hornet.dashTime<=0) { //stops dashing
            hornet.isDashing=false;
            hornet.dashCooldown=90;
        }
    }
    //normal
    else {
        Vector2 dir={player.pos.x-hornet.position.x,player.pos.y-hornet.position.y};
         float distance=sqrt(dir.x*dir.x+dir.y*dir.y);
         if(distance>0) {
            dir.x/=distance;//to prevent quickly appearing
            dir.y/=distance;
            next.x+=dir.x*hornet.normalSpeed;
            next.y+=dir.y*hornet.normalSpeed;
        } 
    }
    //wallcollision
    Vector2 center={next.x+hornet.width/2,next.y+hornet.height/2};
    if(!CheckWallIntersection(center,grid,hornet.width)) {
        hornet.position=next;
    }
    //damage player
       Rectangle hornetRect = {
    hornet.position.x,
    hornet.position.y,
    hornet.width,
    hornet.height
};

Rectangle playerRect = {
    player.pos.x - player.size/2,
    player.pos.y - player.size/2,
    player.size,
    player.size
};
if (CheckCollisionRecs(playerRect, hornetRect))
{
    if(hornet.isDashing) {
    player.health-=0.1f;
    }
    else player.health-=0.05f;
    if (player.health < 0)
        player.health = 0;
}
}
void DrawHornet(Hornet hornet) {
    if(hornet.health<=0) return;
     DrawRectangle(
        hornet.position.x,
        hornet.position.y,
        hornet.width,
        hornet.height,
        YELLOW
    );
     float barWidth=60;
    float barHeight=7;
    DrawRectangle(hornet.position.x-14,hornet.position.y-17,barWidth,barHeight,GRAY); //hornet health bar
    DrawRectangle(hornet.position.x - 14, hornet.position.y - 17,(hornet.health /300.0f) * barWidth,barHeight,RED );
}
void AttackHornet(Player &player, Hornet &hornet) {
    Vector2 playerCenter={player.pos.x,player.pos.y};
        Vector2 hornetCenter={hornet.position.x+hornet.width/2,hornet.position.y+hornet.height/2};
        float distance=sqrt(pow(playerCenter.x-hornetCenter.x,2)+pow(playerCenter.y-hornetCenter.y,2));
        if(distance<=player.attackRange && player.isAttacking && player.attackTick==player.attackDuration-1){
            hornet.health-=player.damage;
            if(hornet.health<0){
                hornet.health=0;
            }
        }
}