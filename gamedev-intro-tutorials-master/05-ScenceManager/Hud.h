#pragma once
#include "Game.h"
#include "PlayScence.h"
class CGame;
class CPlayScene;
// STATE
#define HUB_SPIRE_HUB 1100
#define HUB_SPIRE_ARROW 1101
#define HUB_SPIRE_P 1102
#define HUB_SPIRE_SUPER_BLACK 1103

#define SCREEN_HEIGHT 280 

class Hud
{
	CGame* Game;
	CPlayScene* PlayScene;
	float x, y;
	int maxv=0;
public:
	Hud(CPlayScene* Scene);
	void Render();
	void Update();

};

