#pragma once
#include "GameObject.h"
#include "Item.h"

#define SIGN_SPEED_X 0.05f
#define SIGN_GRAVITY 0.001f
// BBOX
#define SIGN_BBOX_X_Y 16

// ANI
#define ITEM_SIGN_ANI 0
#define ITEM_SIGN_ANI_SIGN 1

#define ITEM_SIGN_ANI_SET	11

class CItemSign : public Item
{
	DWORD time = 0;
public:
	CItemSign();
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, CScene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL);

};



