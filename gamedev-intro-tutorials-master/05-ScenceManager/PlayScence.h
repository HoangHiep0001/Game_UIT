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


#define GAME_TIME 1000
class Hud;

class CPlayScene: public CScene
{
protected: 
	RECT camera;
	RECT mapCamera;
	CMario *player;					// A play scene has to have player, right? 
	
	vector<LPGAMEOBJECT> objects;

	Map* tileMap;

	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_TILEMAP_DATA(string line);

	Hud* hud;
	DWORD time_start;
	int coin_number=0;
	bool oldmap = false;
	unordered_map<int, RECT> mapCameras;
	unordered_map<int, RECT> Cameras;
public: 
	CPlayScene(int id, LPCWSTR filePath, int word, int time, int intro);
	
	RECT GetCamera() { return this->camera; }
	
	void SetMapCamera(RECT map) { this->mapCamera = map; }
	void SetCamera(RECT cam) { this -> camera = cam; }
	unordered_map<int, RECT> GetListMapCamera() {
		return this->mapCameras;
	}
	unordered_map<int, RECT> GetListCamera() {
		return this->Cameras;
	}

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	void SpawnObject(LPGAMEOBJECT object) { objects.push_back(object); }

	CMario * GetPlayer() { return player; } 
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

