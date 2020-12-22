#pragma once
#include "GameObject.h"
#include "Item.h"

#define MUSHROOMS_SPEED_X 0.035f
#define MUSHROOMS_GRAVITY	0.001f
// BBOX
#define MUSHROOMS_BBOX_X_Y 16

// ANI
#define MUSHROOMS_ANI_RED_WALK 0
#define MUSHROOMS_ANI_BULE_WALK 1
// APP
#define MUSHROOMS_RED 0
#define MUSHROOMS_BULE 1

#define MUSHROOMS_ANI_SET	8
#define MUSHROOMS_SCORE 1000
class CMushrooms : public Item
{
	int apperance;
	int score = MUSHROOMS_SCORE;
public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, CScene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	CMushrooms(int app);
	int GetScore() { return this->score; }
	int GetApperance() { return apperance; }
};