#pragma once
#include "GameObject.h"
#define EFFECT_ANIMATION_SET_ID	14

#define EFFECT_NX 1
#define EFFECT_NY 1
#define EFFECT_TIME 200
class CEffect : public CGameObject
{
	DWORD time_effect;
	virtual void Render();
	virtual void Update(DWORD dt, CScene* scene, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
public:
	void SetTimeEffect(DWORD time) {time_effect = time;}
	CEffect(D3DXVECTOR2 position, int nx, int ny = 1);
};


