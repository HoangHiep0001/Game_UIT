#pragma once
#include "GameObject.h"
#define EFFECT_CHANGE_MARIO_ANIMATION_SET_ID	15
#define EFFECT_CHANGE_MARIO_TIME 900
class CEffectChangeMario : public CGameObject
{
	DWORD time_effect;
	virtual void Render();
	virtual void Update(DWORD dt, CScene* scene, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
public:
	void SetTimeEffect(DWORD time) { time_effect = time; }
	CEffectChangeMario(D3DXVECTOR2 position);
};
