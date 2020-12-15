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
class CBrick : public CGameObject
{
	vector<LPGAMEOBJECT> listBrick;

	int item_id;
	int item_count;
	int item_state;
	int score = BRICK_SCORE;
	bool Isbroken = false;
	bool is_broken = false;
	virtual void Render();
	virtual void Update(DWORD dt, CScene* scene, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
public:
	/*bool  GetBroken(){return this->Isbroken = true;}
	void SetBroken(bool broken) { this->Isbroken = broken; }*/
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