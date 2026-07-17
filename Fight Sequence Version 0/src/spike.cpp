#include "spike.h"
#include "raylib.h"
#include "player.h"
#include "map.h"
#include "types.h"

void UpdateSpike(Spike &spike,Player &player) {
    Rectangle spikeRect=
    {
        spike.position.x,
        spike.position.y,
        spike.width,
        5
    };
    Rectangle playerRect =
     {
        player.pos.x - player.size/2, 
        player.pos.y - player.size/2,
         player.size,
         player.size
};
if(CheckCollisionRecs(playerRect,spikeRect))
{
    player.health-=0.3f;
    if(player.health<0) {
        player.health=0;
    }
}
}
void DrawSpike(Spike spike)
{
    DrawRectangle(
        spike.position.x,
        spike.position.y,
        spike.width,
        spike.height,
        RED
    );
}