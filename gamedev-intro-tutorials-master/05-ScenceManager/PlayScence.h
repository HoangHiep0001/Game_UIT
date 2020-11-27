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
	
public: 
	CPlayScene(int id, LPCWSTR filePath);

	RECT GetCamera() { return this->camera; }

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	void SpawnObject(LPGAMEOBJECT object) { objects.push_back(object); }
	CMario * GetPlayer() { return player; } 

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

