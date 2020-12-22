#pragma once
#include "GameObject.h"

#define TAIL_POINT_BBOX_WIDTH 0
#define TAIL_POINT_BBOX_HEIGHT 0

#define TAIL_HEAD 1
#define	TAIL_LAST 2

#define TAIL_ROTATE_VX 0.16f
#define CIRCLE_DIAMETER 28
#define TIME_ROTATE_TAIL 200

class CTailPoint : public CGameObject
{
	int count = 0;
	float start_x;
public:
	CTailPoint( int dir);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, CScene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	void SetStartX(float x) { start_x = x; }
	void SetState(int state);
};

