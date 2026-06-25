#include<bits/stdc++.h>
#include "raylib.h"
using namespace std;
struct LevelData {
    std::vector<std::vector<int>>grid;
};
LevelData level3;

void Levelconfig() {

 
int grid3[20][32]={
//   0 1 2 3 4 5 6 7 8 910111213141516171819202122232425262728293031
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},//0
    {1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},//1
    {1,0,0,0,0,0,2,2,0,0,0,0,0,1,0,0,0,0,0,5,5,0,0,0,0,0,0,0,0,0,0,1},//2
    {1,0,3,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,2,3,5,0,0,0,2,0,1},//3
    {1,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,2,3,0,0,0,2,0,1},//4
    {1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,3,0,0,0,0,0,2,3,5,0,0,0,2,0,1},//5
    {1,1,1,1,1,1,1,1,1,1,0,0,0,1,0,0,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,1},//6
    {1,0,0,0,1,5,5,5,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1},//7
    {1,0,0,0,1,0,5,5,0,0,0,0,0,1,3,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},//8
    {1,0,5,0,1,0,0,0,0,0,0,0,0,0,0,0,0,3,3,0,0,1,0,4,4,4,4,0,0,0,0,1},//9
    {1,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,0,1,0,4,4,4,4,0,0,0,0,1},//10
    {1,0,0,0,0,0,0,0,0,2,2,0,0,1,0,0,0,0,0,0,0,1,0,4,4,4,4,0,0,0,0,1},//11
    {1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1},//12
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,1,1,1,1,1,1,1,1,1,0,0,1,1},//13
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,1,0,0,0,0,0,0,0,0,0,0,0,1},//14
    {1,0,0,3,0,0,0,0,0,2,2,0,0,0,0,0,0,0,1,1,0,0,3,3,3,0,0,0,0,0,0,1},//15
    {1,0,0,3,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,1,0,0,3,3,3,0,0,0,0,0,0,1},//16
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1},//17
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},//18
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}//19
};
    level3.grid.resize(20, std::vector<int>(32));
    for(int r=0;r<20;r++) {
        for(int c=0;c<32;c++) 
        level3.grid[r][c]=grid3[r][c];
    }
}


int main() 
{
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 600;
    int tileSize = 25;
    
    InitWindow(screenWidth, screenHeight, "My first RAYLIB program!");
    SetTargetFPS(60);
    Levelconfig();
    // level3.grid is ready now
    
    while (!WindowShouldClose())
    {
        BeginDrawing();
            
            ClearBackground(BLACK);
            
            for (int i=0; i<20; i++){
                for (int j=0; j<32; j++){
                    switch (level3.grid[i][j]){
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
