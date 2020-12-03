#pragma once
#include "GameObject.h"

#define COIN_BBOX_WIDTH  14
#define COIN_BBOX_HEIGHT 16

#define COIN_SCORE 100;

class CCoin : public CGameObject
{
	int score = COIN_SCORE;
	int coin_number = 1;
public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	int GetScore() { return this->score; }
	int GetCoin_number() { return this->coin_number; }
};