#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scence.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
#include "Koopas.h"
#include "Map.h"
#include "QuestionMark.h"
#include "COIN.h"
#include "Hud.h"
#include "Item.h"
#include "Grid.h"


#define GAME_TIME 1000
#define SPECIAL_MAP_STATIC 0
#define SPECIAL_MAP_MOVING 1
#define INTRO_MAP_START 0
#define INTRO_MAP_MAP 1

#define TILE_SIZE	16
#define INTRO_NX 5
class Hud;

class CPlayScene: public CScene
{
protected: 
	RECT camera;
	RECT mapCamera;
	CMario *player;					// A play scene has to have player, right? 
	vector<LPGAMEOBJECT> objects;
	int isSpecialMap;
	Map* tileMap;

	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_TILEMAP_DATA(string line);
	void _ParseSection_GRID(string line);

	Grid* grid;
	Hud* hud;
	DWORD time_start;
	int coin_number=0;
	bool oldmap = false;
	unordered_map<int, RECT> mapCameras;
	unordered_map<int, RECT> Cameras;
	unordered_map<int, int> isSpecialCamera;

	int x_specialcamera = 0;
public: 
	CPlayScene(int id, LPCWSTR filePath, int word, int time, int intro);
	
	Hud* getHub() { return this->hud; }

	RECT GetCamera() { return this->camera; }
	
	void GetListObjectFromGrid();

	void UpdateGrid();

	void SetMapCamera(RECT map) { this->mapCamera = map; }
	void SetCamera(RECT cam) { this -> camera = cam; }
	unordered_map<int, RECT> GetListMapCamera() {
		return this->mapCameras;
	}
	void SetSpecialCamera(int i) { this->isSpecialMap = i; }
	unordered_map<int, int> GetSpecialCamera() { return this->isSpecialCamera; }
	unordered_map<int, RECT> GetListCamera() {
		return this->Cameras;
	}

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	void SpawnObject(LPGAMEOBJECT object) { objects.push_back(object); }

	CMario * GetPlayer() { return player; } 
	int GetID() { return id; }
    int GetWord() { return word; }
	int GetTime() { return time; }
	int GetIntro() { return intro; }
	void GetCountDown();
	//friend class CPlayScenceKeyHandler;
};

class CPlayScenceKeyHandler : public CScenceKeyHandler
{
public: 
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	CPlayScenceKeyHandler(CScene *s) :CScenceKeyHandler(s) {};
};

