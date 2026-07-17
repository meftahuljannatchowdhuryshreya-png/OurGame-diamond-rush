#include "slime.h"
#include "raylib.h"
#include "player.h"
#include "map.h"
#include "types.h"
#include <cmath>
#include <vector>
using namespace std;

void UpdateSlime(Slime &slime,vector<vector<int>> grid,Player &player) {
    if(slime.health <= 0)
    return;
    const float TILE_SIZE=32.0;
   
    int topRow=slime.position.y/TILE_SIZE;
    int bottomRow=(slime.position.y+slime.height-1)/TILE_SIZE;
    int nextGroundRow = (slime.position.y + slime.height) / TILE_SIZE;
//move
    if(slime.moveRight) {
      int nextRightCol=(slime.position.x+slime.speed+slime.width-1)/TILE_SIZE;
       int nextGroundCol = (slime.position.x + slime.speed + slime.width) / TILE_SIZE;
        if(grid[topRow][nextRightCol]!=0 || grid[bottomRow][nextRightCol]!=0 ||  grid[nextGroundRow][nextGroundCol] == 0)  {
            slime.moveRight=false;
        }else {
            slime.position.x+=slime.speed;
        }
    }
    else {
         int nextLeftCol=(slime.position.x-slime.speed)/TILE_SIZE;
         int nextGroundCol = (slime.position.x - slime.speed) / TILE_SIZE;
        if(grid[topRow][nextLeftCol]!=0 || grid[bottomRow][nextLeftCol]!=0 ||  grid[nextGroundRow][nextGroundCol] == 0 ) {
            slime.moveRight=true;
        }else {
             slime.position.x-=slime.speed;
        }
    }
    Rectangle slimeRect=
    {
        slime.position.x,
        slime.position.y,
        slime.width,
        slime.height
    };
    Rectangle playerRect =
     {
        player.pos.x - player.size/2, 
        player.pos.y - player.size/2,
         player.size,
         player.size
};
if(CheckCollisionRecs(playerRect,slimeRect))
{
    player.health-=0.1f;
    if(player.health<0) {
        player.health=0;
    }
}
}
void DrawSlime(Slime slime) {
         if(slime.health<=0){
        return;
    }
 DrawRectangle(slime.position.x,slime.position.y,slime.width,slime.height,GREEN);
}
void AttackSlime(Player &player,Slime &slime) {
    if(slime.health <= 0)
    return;
        Vector2 playerCenter={player.pos.x,player.pos.y};
        Vector2 slimeCenter={slime.position.x+slime.width/2,slime.position.y+slime.height/2};
        float distance=sqrt(pow(playerCenter.x-slimeCenter.x,2)+pow(playerCenter.y-slimeCenter.y,2));
        if(distance<=player.attackRange && player.isAttacking && player.attackTick==player.attackDuration-1){
            slime.health-=10.0f;
            if(slime.health<0){
                slime.health=0;
            }
        }
    }
