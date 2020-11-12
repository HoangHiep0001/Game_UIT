#pragma once
#include <d3d9.h>
#include"Textures.h"
#include "Sprites.h"
class Map
{
	float camera_x;
 	float camera_y;
	int rowMap, columnMap;		
	int rowTileSet, columnTileSet;	

	int totalTile;	
	
	LPDIRECT3DTEXTURE9 tileSet;
	vector<LPSPRITE> tiles;
	std::vector<std::vector<int>> tileMap;
	int screenWidth;
public:
	Map(int tileSetID,int rowMap,int columnMap, int rowTileSet,int  columnTileSet, int totalTile);
	~Map();
	void Render();
	void SetTileMapData(std::vector<std::vector<int>> tileMapData);
	void SetCamera(int x, int y);
	void ExtractTileFromTileSet();
	int GetMapWidth();
	int GetMapHeight();
};

