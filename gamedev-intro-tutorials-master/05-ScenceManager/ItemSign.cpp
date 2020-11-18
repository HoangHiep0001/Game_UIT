#include "ItemSign.h"

CItemSign::CItemSign()
{
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(ITEM_SIGN_ANI_SET);
	this->SetAnimationSet(ani_set);
	time = GetTickCount64();
}

void CItemSign::Render()
{
	if (isDestroy)
		return;
	int ani = ITEM_SIGN_ANI_SIGN;
	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox();
}

void CItemSign::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + SIGN_BBOX_X_Y;
	b = y + SIGN_BBOX_X_Y;
}

void CItemSign::Update(DWORD dt, CScene* scene, vector<LPGAMEOBJECT>* colliable_objects)
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

	if (GetTickCount64() - time >= 200 && time > 0)
	{
		Destroy();
	}

	x += dx;
	y += dy;
}

