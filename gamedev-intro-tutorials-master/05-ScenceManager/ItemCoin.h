#pragma once
#include "GameObject.h"
#include "Item.h"

#define COIN_FLY_Y			0.15f
// BBOX
#define COIN_BBOX_X_Y 16
//state
#define ITEM_COIN_STATE_COIN 0
#define ITEM_COIN_STATE_IDE 1
// ANI
#define ITEM_COIN_ANI_COIN 0
#define ITEM_COIN_ANI_IDE 1

#define ITEMCOIN_ANI_SET	9

	class CItemCoin : public Item
	{
		int state;
		DWORD time = 0;
		bool isBornByBrick = false;
	public:
		CItemCoin(int nsta);
		virtual void Render();
		virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
		virtual void Update(DWORD dt, CScene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL);
		int GetnState() { return state; }
		bool GetIsBornByBrick() { return this->isBornByBrick; }
		void SetIsBornByBrick(bool x) { isBornByBrick = x; }

	};

