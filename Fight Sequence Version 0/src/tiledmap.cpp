#include "tiledmap.h"

#include "../include/json.hpp"

#include <fstream>
#include <vector>


using json = nlohmann::json;


Texture2D tileset;


std::vector<int> tiles;


int mapWidth;
int mapHeight;

int tileSize = 32;

int columns;



void LoadTiledMap(const char* filename)
{

    std::ifstream file(filename);


    json data;

    file >> data;



    mapWidth = data["width"];

    mapHeight = data["height"];



    tileset = LoadTexture(
        "assets/tilesets/ChatGPT Image Jul 17, 2026, 10_46_00 PM.png"
    );



    columns = tileset.width / tileSize;



    auto layer = data["layers"][0];


    for(auto t : layer["data"])
    {
        tiles.push_back(t);
    }

}



void DrawTiledMap()
{

    for(int y=0;y<mapHeight;y++)
    {

        for(int x=0;x<mapWidth;x++)
        {


            int gid =
            tiles[y*mapWidth+x];


            if(gid==0)
                continue;



            int id = gid - 1;



            Rectangle source =
            {
                (float)((id%columns)*tileSize),
                (float)((id/columns)*tileSize),
                tileSize,
                tileSize
            };


            Rectangle dest =
            {
                x*tileSize,
                y*tileSize,
                tileSize,
                tileSize
            };


            DrawTexturePro(
                tileset,
                source,
                dest,
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
