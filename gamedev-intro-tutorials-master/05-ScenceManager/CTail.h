#pragma once
#include "GameObject.h"

#define TAIL_BBOX_WIDTH 20
#define TAIL_BBOX_HEIGHT 4


class CTail : public CGameObject
{
	int score = 0;
public:
	CTail( CScene* scene, int dir);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, CScene* scene, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	int GetScore() { return this->score; }
};
