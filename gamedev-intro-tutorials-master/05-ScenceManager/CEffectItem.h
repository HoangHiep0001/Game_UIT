#pragma once
#include "GameObject.h"
/// BBOX
#define EFFECTITEM_BBOX 16

//state
#define EFFECTITEM_ANI_SET	0

#define EFFECTITEM_ANI 5110


#define EFFECTITEM_TIME 200
class CEffectItem : public CGameObject
{
	DWORD time=0;
	int state;
public:
	CEffectItem(int state);
	virtual void Render();
	virtual void Update(DWORD dt, CScene* scene, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state);
};

