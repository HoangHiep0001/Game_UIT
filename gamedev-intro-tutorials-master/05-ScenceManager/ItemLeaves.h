#pragma once
#pragma once
#include "GameObject.h"
#include "Item.h"

#define LEAVES_SPEED_X 0.05f
#define LEAVES_SPEED_Y 0.35f
#define LEAVES_GRAVITY	0.0001f
// BBOX
#define LEAVES_BBOX_X 16
#define LEAVES_BBOX_Y 14
//STATE
#define LEAVES_STATE_FALL 100
// ANI
#define LEAVES_ANI_LEFT 0
#define LEAVES_ANI_RIGHT 1

#define LEAVES_ANI_SET	10

#define LEAVES_Y 5
class CLeaves : public Item
{
	int item_id;
	float start_y;
public:
	void SetStartY(float y) { start_y = y; }
	virtual void SetState(int state);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, CScene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	CLeaves();
	
}; 

