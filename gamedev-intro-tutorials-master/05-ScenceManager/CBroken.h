#pragma once
#include "GameObject.h"
#define BROKEN_GRAVITY 0.0035f

#define BROKEN_VX 0.07f
#define BROKEN_VY 0.17f

#define BROKEN_ANIMATION_SET_ID	13
class CBroken : public CGameObject
{
	virtual void Render();
	virtual void Update(DWORD dt, CScene* scene, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
public:
	CBroken(D3DXVECTOR2 position, int nx, int ny = 1);
};

