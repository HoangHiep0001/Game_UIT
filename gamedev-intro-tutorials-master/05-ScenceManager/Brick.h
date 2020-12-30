#pragma once
#include "GameObject.h"

#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16

//STATE
#define BRICK_STATE_BRICK 0
#define BRICK_STATE_EMPTY 1
#define BRICK_STATE_BROKEN 2

// ani
#define BRICK_ANI_BRICK 0
#define BRICK_ANI_EMPTY 1
#define BRICK_ANI_BROKEN 2
#define BRICK_ANIMATION_SET_ID	3
#define BRICK_SCORE 10


#define BRICK_NX 1
#define BRICK_NY 1
#define BRICK_X1 1
#define BRICK_X2 9
#define BRICK_Y1 2
#define BRICK_Y2 10

class CBrick : public CGameObject
{

	int item_id;
	int item_count;
	int item_state;
	DWORD time;
	int score = BRICK_SCORE;
	bool Isbroken = false;
	virtual void Render();
	virtual void Update(DWORD dt, CScene* scene, vector<LPGAMEOBJECT>* coObjects);
	
public:
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	/*bool  GetBroken(){return this->Isbroken = true;}
	void SetBroken(bool broken) { this->Isbroken = broken; }*/
	bool setIsBroken(bool x) {return this->Isbroken = x; }
	CBrick();
	int GetItemID() { return this->item_id; }
	void SetItemID(int id) { this->item_id = id; }
	int GetItemCount() { return this->item_count; }
	void SetItemCount(int count) { this->item_count = count; }
	int GetItemState() { return this->item_state; }
	void SetItemState(int nstate) { this->item_state = nstate; }
	virtual void SetState(int state);
	int GetScore() { return this->score; }
	void SetAnimationSet()
	{
		CAnimationSets* animation_sets = CAnimationSets::GetInstance();
		LPANIMATION_SET ani_set = animation_sets->Get(BRICK_ANIMATION_SET_ID);
		this->animation_set = ani_set;
	}
};