#pragma once
#include "GameObject.h"
#include "Item.h"

#define FLOWER_FIRE_BBOX_X 16
#define FLOWER_FIRE_BBOX_Y 16

#define FLOWER_FIRE_ANI_SET	16

#define FLOWER_FIRE_ANI_FLOWER 0
#define FLOWER_FIRE_SCORE 1000
class CFlowerFire : public Item
{
	int item_id;
	int score = FLOWER_FIRE_SCORE;

public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, CScene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	int GetScore() { return this->score; }
	CFlowerFire();
};

