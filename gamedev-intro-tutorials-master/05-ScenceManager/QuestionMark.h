#pragma once
#include "GameObject.h"

#define MARK_BBOX_WIDTH  16
#define MARK_BBOX_HEIGHT 16


#define MARK_STATE_QUESTION	0
#define MARK_STATE_EMPTY 1

#define MARK_ANI_QUESTION 0
#define MARK_ANI_EMPTY 1


#define MARK_CAKE_VY 0.05f

#define MAX_RANGE_Y	2
class CQuestionMark : public CGameObject
{
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, CScene* scene, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	float start_y;
public:
	CQuestionMark();
	virtual void SetState(int state);
	void SetStartY(float y) { start_y = y; }
};

