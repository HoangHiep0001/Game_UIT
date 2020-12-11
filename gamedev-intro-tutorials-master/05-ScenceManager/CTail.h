#pragma once
#include "GameObject.h"

#define TAIL_BBOX_WIDTH 8
#define TAIL_BBOX_HEIGHT 3
class CTail : public CGameObject
{

public:
	CTail( CScene* scene, int dir);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, CScene* scene, vector<LPGAMEOBJECT>* coObjects);
	void Render();

};
