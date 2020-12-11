#pragma once
#include "GameObject.h"

#define BROKEN_BBOX_WIDTH  8
#define BROKEN_BBOX_HEIGHT 8

//STATE
#define BROKEN_STATE_BROKEN 0

// ani
#define BROKEN_ANI_BROKEN 0

#define BROKEN_ANIMATION_SET_ID	13
class CBroken : public CGameObject
{
	int location_broken_1;
	int location_broken_2;
	int location_broken_3;
	int location_broken_4;

	virtual void Render();
	virtual void Update(DWORD dt, CScene* scene, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
public:
	CBroken();
};

