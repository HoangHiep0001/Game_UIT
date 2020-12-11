#pragma once
#include "GameObject.h"

#define MARK_BBOX_WIDTH  16
#define MARK_BBOX_HEIGHT 16


#define MARK_STATE_QUESTION	0
#define MARK_STATE_EMPTY 1
#define MARK_STATE_N_EMPTY 2

#define MARK_ANI_QUESTION 0
#define MARK_ANI_EMPTY 1


#define MARK_CAKE_VY 0.05f

#define MAX_RANGE_Y	2
class CQuestionMark : public CGameObject
{
	int item_id;
	int item_count;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, CScene* scene, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	float start_y;
	bool is_up = false;
	
public:
	CQuestionMark();
	virtual void SetState(int state);
	bool getIsUp() { return this->is_up; }
	void SetIsUp(bool x) { this->is_up = x; }
	void SetStartY(float y) { start_y = y; }
	int GetItemID() { return this->item_id; }
	void SetItemID(int id) { this->item_id = id; }
	int GetItemCount() { return this->item_count; }
	void SetItemCount(int count) { this->item_count = count; }
	
};

