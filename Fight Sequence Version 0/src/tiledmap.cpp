#include "tiledmap.h"
#include "raylib.h"


Texture2D tileset;


// Your exported Tiled map
int tiledMap[TILE_MAP_HEIGHT][TILE_MAP_WIDTH] =
{
    {1829,1829,1830,1829,1829,1830,1829,1830,1829,1829,1830,1830,1829,1829,1829,1829,1829,1829,1829,2247,2248,2249,1829,1829,1829,1830,1829,1829,1829,1829,1830,1830},

    {1855,1855,1855,1855,1855,1856,1855,1855,1855,1855,1856,2404,2254,2255,1855,2045,2046,2047,1855,2295,2296,2297,1855,1856,1855,1855,1855,1855,1856,1855,1855,1856},

    // paste the remaining rows here
};



void LoadTiledMap()
{
    tileset = LoadTexture("assets/tileset.png");
}



void DrawTiledMap()
{

    int columns = tileset.width / TILE_SIZE;


    for(int y = 0; y < TILE_MAP_HEIGHT; y++)
    {
        for(int x = 0; x < TILE_MAP_WIDTH; x++)
        {

            int gid = tiledMap[y][x];


            if(gid == 0)
                continue;


            // convert global ID to local tile number
            int id = gid - 1;


            Rectangle source =
            {
                (float)((id % columns) * TILE_SIZE),
                (float)((id / columns) * TILE_SIZE),
                TILE_SIZE,
                TILE_SIZE
            };


            Rectangle destination =
            {
                (float)(x*TILE_SIZE),
                (float)(y*TILE_SIZE),
                TILE_SIZE,
                TILE_SIZE
            };


            DrawTexturePro(
                tileset,
                source,
                destination,
                {0,0},
                0,
                WHITE
            );
        }
    }
}



void UnloadTiledMap()
{
    UnloadTexture(tileset);
}
