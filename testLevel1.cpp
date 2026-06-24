#include<bits/stdc++.h>
#include "raylib.h"
using namespace std;
//#include "raymath.h"

//defination
enum TileType {
    TILE_EMPTY=0,
    TILE_WALL=1,
    TILE_SPEOBJECT=2,
    TILE_CAGE=3
};
//dec
struct Room {
    std::string name;
    int x;
    int y;
    int w;
    int h;
    Color color;
};
struct LevelData {
    int id;
    std::string name;
    int width;
    int height;
    float startX;
    float startY;
    std::vector<std::vector<int>>grid;
    std::vector<Room>rooms;
    Vector2 startPos;
    Vector2 key1Pos;
    Vector2 key2Pos;
    bool key2FromBoss;
    bool key1Collected;
    bool key2Collected;
    bool chestUnlocked;
    Vector2 doorPos;
    Vector2 chestPos;

};

vector<LevelData> maplist;
LevelData level1;

void Levelconfig() {
    maplist.clear();

    //Level 1
    //LevelData level1;
    level1.id=1;
    level1.name="Catacombs of the Fallen";
    level1.width=1024;
    level1.height=640;
    level1.startX=480.0f; //start from (15,14)
    level1.startY=448.0f;
    level1.startPos={480.0f,448.0f};
    level1.key1Pos={192.0f,64.0f}; //one key will be in The Bone Garden(6,2)
    level1.key2Pos={864.0f,480.0f}; //another key in Altar of First Desecration(27,15)
    level1.doorPos={928.0f,96.0f}; //door in Portal to Cursed Depths(29,3)
    level1.chestPos={576.0f,320.0f}; //chest in Portal to Cursed Depths(18,10)


    level1.rooms = {
        {"The Bone Garden of Fallen Warriors", 1, 2, 12, 5, {80, 200, 100, 75}},
        {"Portal to Cursed Depths", 15, 2, 10, 4, {200, 50, 50, 75}},
        {"Vault of Sealed Sorrows", 1, 8, 12, 6, {150, 40, 40, 80}},
        {"Hall of Echoing Silence", 10, 12, 13, 6, {100, 200, 80, 75}},
        {"Altar of First Desecration", 24, 7, 7, 11, {50, 100, 200, 75}},
    };
        
    //0=blank,1=block,2=Blood Altar/Torture Device,3=cursed items,4=human bones

    int grid1[20][32]={
    //   0 1 2 3 4 5 6 7 8 910111213141516171819202122232425262728293031
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},//0
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},//1
        {1,0,0,0,0,0,0,0,0,0,0,3,3,3,1,0,3,3,0,0,0,0,4,4,4,0,0,0,0,0,0,1},//2
        {1,0,0,0,4,4,4,4,0,0,0,0,0,3,1,0,3,3,0,0,0,0,4,0,4,0,0,0,0,0,0,1},//3
        {1,0,0,0,4,4,4,4,0,0,0,0,0,0,1,0,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,1},//4
        {1,0,0,0,4,4,4,4,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,1},//5
        {1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},//6
        {1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,1,0,0,0,3,0,0,0,1},//7
        {1,0,0,0,0,2,2,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,3,3,0,0,1},//8
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},//9
        {1,0,3,3,0,0,0,0,0,0,0,0,0,0,1,2,2,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},//10
        {1,0,3,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,0,0,0,0,0,0,0,1},//11
        {1,0,3,3,0,0,0,0,0,1,0,0,2,2,0,0,0,0,0,0,0,0,4,1,0,0,0,2,2,0,0,1},//12
        {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,4,1,0,0,0,2,2,0,0,1},//13
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,3,0,0,2,2,0,0,1},//14
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,3,0,0,0,0,0,0,1},//15
        {1,0,0,4,4,0,0,0,0,1,0,0,0,0,0,3,3,3,0,0,0,0,0,1,0,0,0,0,5,5,0,1},//16
        {1,0,0,4,0,0,0,0,0,1,0,0,0,0,0,3,3,3,0,0,0,0,0,1,0,0,0,0,0,0,0,1},//17
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},//18
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} //19
    };
    level1.grid.resize(20, std::vector<int>(32));
    for(int r=0;r<20;r++) {
        for(int c=0;c<32;c++) 
        level1.grid[r][c]=grid1[r][c];
    }
        maplist.push_back(level1);

}


int main() 
{
    
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 600;
    int tileSize = 25;
    
    InitWindow(screenWidth, screenHeight, "My first RAYLIB program!");
    SetTargetFPS(60);
    Levelconfig();
    // level1.grid is ready now
    
    while (!WindowShouldClose())
    {
        
        BeginDrawing();
            
            ClearBackground(BLACK);
            
            for (int i=0; i<20; i++){
                for (int j=0; j<32; j++){
                    switch (level1.grid[i][j]){
                    case 0:
                        DrawRectangle(j*tileSize, i*tileSize, tileSize, tileSize, BLACK);  break;
                    case 1:
                        DrawRectangle(j*tileSize, i*tileSize, tileSize, tileSize, GREEN); break;
                    case 2:
                        DrawRectangle(j*tileSize, i*tileSize, tileSize, tileSize, GRAY); break;
                    case 3:
                        DrawRectangle(j*tileSize, i*tileSize, tileSize, tileSize, RED); break;
                    case 4:
                        DrawRectangle(j*tileSize, i*tileSize, tileSize, tileSize, WHITE); break;
                    case 5:
                        DrawRectangle(j*tileSize, i*tileSize, tileSize, tileSize, BLUE); break;
                    }
                }
            }
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}
