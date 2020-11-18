#pragma once
#include "GameObject.h"

#define BRICK_BBOX_WIDTH  16
#define BRICK_BBOX_HEIGHT 16

class CBrick : public CGameObject
{

	int item_id;
	int item_count;
	bool Isbroken = false;
	virtual void Render();
	virtual void Update(DWORD dt, CScene* scene, vector<LPGAMEOBJECT>* coObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
public:
	bool  GetBroken(){return this->Isbroken = true;}
	void SetBroken(bool broken) { this->Isbroken = broken; }
	int GetItemID() { return this->item_id; }
	void SetItemID(int id) { this->item_id = id; }
	int GetItemCount() { return this->item_count; }
	void SetItemCount(int count) { this->item_count = count; }
};