#pragma once
#include "GameObject.h"

#define PLATFORM_WOOD_BBOX_WIDTH  48
#define PLATFORM_WOOD_BBOX_HEIGHT 16

#define PLATFORM_WOOD_VX 0.04
#define PLATFORM_WOOD_VY 0.04

#define PLATFORM_WOOD_STATE_PLATFORM_WOOD 0
#define PLATFORM_WOOD_ANI_PLATFORM_WOOD 0

class CPlatformWood : public CGameObject
{
	
public:
	CPlatformWood();
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, CScene* scene, vector<LPGAMEOBJECT>* coObjects);
	virtual void SetState(int state);
};

