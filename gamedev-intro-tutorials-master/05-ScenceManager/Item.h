#pragma once
#include "GameObject.h"

#define MUSHROOMS_ID_RED	1
#define COIN_ID	2

class Item : public CGameObject
{
	int ID;
public:
	virtual void Render() {};
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	virtual void Update(DWORD dt, CScene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL) {};
	Item* SpawnItem(int id);
};