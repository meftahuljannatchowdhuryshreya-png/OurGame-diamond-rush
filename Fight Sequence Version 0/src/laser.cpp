#include "laser.h"
#include "raylib.h"
#include "player.h"
#include "map.h"
#include "types.h"

void UpdateLaserTrap(LaserTrap &laser,Player &player) {
    laser.timer++;
    //laser timer
    if(laser.active) {
        if(laser.timer>=laser.onTime) {
            laser.active=false;
            laser.timer=0;
        }
     } else {
            if(laser.timer>=laser.offTime) {
                laser.active=true;
                laser.timer=0;
            }
        }
        //damaage
        if(!laser.active)
        return;
    Vector2 center=
    {
        player.pos.x,
        player.pos.y
    };
    if(CheckCollisionCircleLine(center,player.size/2,laser.start,laser.end)) {
        player.health-=0.1f;
        if(player.health<0) {
            player.health=0;
        }
    }
    }
    void DrawLaserTrap(LaserTrap laser){
        if(!laser.active) {
            return;
        }
        DrawLineEx(laser.start,laser.end,4,RED);
    }