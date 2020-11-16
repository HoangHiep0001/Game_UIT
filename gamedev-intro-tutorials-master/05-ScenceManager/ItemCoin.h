
#pragma once
#include "GameObject.h"
#include "Item.h"

#define COIN_SPEED_X 0.05f
#define COIN_GRAVITY			0.001f
// BBOX
#define COIN_BBOX_X_Y 16

// ANI
#define ITEMCOIN_ANI_COIN 0

#define ITEMCOIN_ANI_SET	9

	class CItemCoin : public Item
	{
		DWORD time = 0;
	public:
		CItemCoin();
		virtual void Render();
		virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
		virtual void Update(DWORD dt, CScene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL);

	};

