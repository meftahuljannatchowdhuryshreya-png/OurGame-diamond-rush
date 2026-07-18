#ifndef TILEDMAP_H
#define TILEDMAP_H

#include "raylib.h"

// Your Tiled map size
constexpr int TILE_MAP_WIDTH = 32;
constexpr int TILE_MAP_HEIGHT = 20;

constexpr int TILE_SIZE = 32;


// Load tileset image
void LoadTiledMap();


// Draw the map
void DrawTiledMap();


// Free memory
void UnloadTiledMap();

#endif
