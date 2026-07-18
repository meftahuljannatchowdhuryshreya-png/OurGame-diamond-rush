#include "types.h"
#include "upgrade.h"
#include "raylib.h"
#include "player.h"
#include "map.h"
#include "vector"
using namespace std;
void UpdateXP(Player &player) {
    while(player.xp>=player.maxXp)
    {
        player.xp-=player.maxXp;
        player.level++;
        player.maxXp*=1.5;
        player.damage+=5;
    }
}
void SpawnHealthBoost(Player &player,HealthBoost &boost, int currentLevel,vector<vector<int>> &grid) {
    if(boost.active) return;
    if(player.health>70) return;
    if(GetRandomValue(0,300)!=0) return;
    int playerRow=player.pos.y/32;
    int playerCol=player.pos.x/32;
    while(true) {
        int row=GetRandomValue(playerRow - 7, playerRow + 7);
        int col=GetRandomValue(playerCol - 7, playerCol + 7);
        if(row < 0) row = 0;
        if(row >=(int)grid.size()) row =(int)grid.size() - 1;
        if(col < 0) col = 0;
         if(col>=(int)grid.size()) col =(int) grid.size() - 1;
        if(grid[row][col]==0) {
            boost.position.x=col*32;
            boost.position.y=row*32;
            boost.active=true;
            break;
        }
    }
}
void UpdateHealthBoost(Player &player,HealthBoost &boost){
     if(!boost.active) return;
Rectangle boostRect=
    {
        boost.position.x,
        boost.position.y,
        boost.size,
        boost.size
    };
    Rectangle playerRect =
     {
        player.pos.x - player.size/2, 
        player.pos.y - player.size/2,
         player.size,
         player.size
};
if(CheckCollisionRecs(playerRect,boostRect))
{
    player.health+=boost.boost;
    if(player.health>100) {
        player.health=100;
    }
    boost.active=false;
}
}
void DrawXPBar(Player &player) {
    float barWidth=250;
    float barHeight=20;
    DrawRectangle(20,60,barWidth,barHeight,GRAY);
     DrawRectangle(20,60,barWidth*(player.xp/player.maxXp),barHeight,BLUE);
      DrawRectangleLines(20, 60, barWidth, barHeight, WHITE);
      DrawText(
        TextFormat("Level %d",player.level),20,85,20,WHITE
      );
    }
      void DrawHealthBoost(HealthBoost boost){
        if(!boost.active) return;
        DrawRectangle(boost.position.x,boost.position.y,boost.size,boost.size,BLUE);
      }
