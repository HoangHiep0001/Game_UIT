#include "Map.h"
#include "Sprites.h"
#include "Utils.h"
#include "Game.h"

#define TILE_SIZE 16
Map::Map(int tileSetID, int rowMap, int columnMap, int rowTileSet, int columnTileSet, int totalTile)
{
	tileSet =CTextures::GetInstance()->Get(tileSetID);
	this->rowMap = rowMap;
	this->columnMap = columnMap;
	this->rowTileSet = rowTileSet;
	this->columnTileSet = columnTileSet;
	this->totalTile = totalTile;
	screenWidth = CGame::GetInstance()->GetScreenWidth();
}

Map::~Map()
{
}

void Map::SetCamera(int x,int y)
{
	this->camera_x = x;
	this->camera_y = y;
}

void Map::Render()
{
	float startingColumn = floor(camera_x / TILE_SIZE);
	float maxColumn = ceil( (screenWidth + camera_x)/ TILE_SIZE);
	//DebugOut(L" start = %f, max = %f\n", startingColumn, maxColumn);

	if (maxColumn >= columnMap) maxColumn = columnMap;
	for (int currentRow = 0; currentRow < rowMap; currentRow++)
		for (int currentColumn = startingColumn; currentColumn < maxColumn; currentColumn++)
			tiles.at(tileMap[currentRow][currentColumn] - 1)->Draw(currentColumn * TILE_SIZE, currentRow * TILE_SIZE);
}

void Map::SetTileMapData(std::vector<std::vector<int>> tileMapData)
{
	tileMap = tileMapData;
}
//
//void Map::SetCamera(Camera* cam)
//{
//	this->camera = cam;
//}


void Map::ExtractTileFromTileSet()
{
	for (int tileNum = 0; tileNum < totalTile; tileNum++)
	{
		int left =  tileNum	% columnTileSet * TILE_SIZE;
		int top = tileNum / columnTileSet * TILE_SIZE;
		int right = left + TILE_SIZE;
		int bottom = top + TILE_SIZE;
		LPSPRITE newTile = new CSprite(tileNum, left, top, right, bottom, tileSet);
		this->tiles.push_back(newTile);
	}
}

int Map::GetMapWidth()
{
	return columnMap * TILE_SIZE;
}

int Map::GetMapHeight()
{
	return rowMap * TILE_SIZE;
}
