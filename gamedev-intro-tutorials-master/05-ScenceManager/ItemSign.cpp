#include "ItemSign.h"

CItemSign::CItemSign()
{
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(ITEM_SIGN_ANI_SET);
	this->SetAnimationSet(ani_set);
	//time = GetTickCount64();
}

void CItemSign::Render()
{
	if (isDestroy)
		return;
	int ani = ITEM_SIGN_ANI;
	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox();
}

void CItemSign::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (isDestroy)
	{
		return;
	}
	if (state== ITEM_SIGN_ANI)
	{
		l = x;
		t = y;
		r = l + SIGN_BBOX_X_Y;
		b = t + SIGN_BBOX_X_Y;
	}
	else
	{
    l = x;
	t = y;
	r = l + SIGN_BBOX_X_Y;
	b = t + 7;
	}
	
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
	/*if (state== ITEM_SIGN_ANI_SIGN)
	{
		if (GetTickCount64() - time >= 2000 && time > 0)
		{
			SetState(ITEM_SIGN_ANI);
		}
	}*/
	x += dx;
	y += dy;
}

