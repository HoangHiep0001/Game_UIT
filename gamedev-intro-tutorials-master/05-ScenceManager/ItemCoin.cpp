#include "ItemCoin.h"

CItemCoin::CItemCoin()
{
	vy = -0.15f;
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(ITEMCOIN_ANI_SET);
	this->SetAnimationSet(ani_set);
	time=GetTickCount64();
}

void CItemCoin::Render()
{
	if (isDestroy)
		return;
	int ani = ITEMCOIN_ANI_COIN;
	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox();
}

void CItemCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + COIN_BBOX_X_Y;
	b = y + COIN_BBOX_X_Y;
}

void CItemCoin::Update(DWORD dt, CScene* scene, vector<LPGAMEOBJECT>* colliable_objects)
{
	if (isDestroy)
	{
		return;
	}
	if (!CheckInCamera())
	{
		return;
	}
	CGameObject::Update(dt, scene, colliable_objects);

	if (GetTickCount64() - time >= 200 && time>0)
	{
		Destroy();
	}

	x += dx;
	y += dy;
}
