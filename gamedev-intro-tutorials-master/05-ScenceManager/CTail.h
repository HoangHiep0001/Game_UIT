#pragma once
#include "GameObject.h"
#include "CTailPoint.h"

#define TAIL_BBOX_WIDTH 24
#define TAIL_BBOX_HEIGHT 5

#define TAIL_POINT_LEFT 24
#define TAIL_POINT_RIGHT 12
#define TAIL_POINT_WIDTH 6
#define TAIL_POINT_HEIGHT 19

class CTail : public CGameObject
{
	int score = 0;
	CTailPoint* tailHead; 
	CTailPoint* tailLast;
	bool is_broken = false;
public:
	CTail( CScene* scene, int dir);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, CScene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	int GetScore() { return this->score; }
	CTailPoint* GettailHead() { return this->tailHead; }
	CTailPoint* GettailLast() { return this->tailLast; }
};
