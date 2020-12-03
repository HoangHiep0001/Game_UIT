#pragma once
#include "GameObject.h"

#define MUSHROOMS_ID_BULE 0
#define MUSHROOMS_ID_RED 1
#define COIN_ID_WALK 2
#define COIN_ID_IDE	3
#define LEAVES_ID 4
#define SIGN_ID 5

#define COIN_SCORE 100
class Item : public CGameObject
{
protected:
	int ID;
	int score=0;
	int number = 0;
public:
	virtual void Render() {};
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) {};
	virtual void Update(DWORD dt, CScene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL) {};
	Item* SpawnItem(int id, CScene* scene);
};