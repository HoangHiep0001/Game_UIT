#include "ItemSign.h"
#include "Brick.h"

CItemSign::CItemSign(int state)
{
	state = state;
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(ITEM_SIGN_ANI_SET);
	this->SetAnimationSet(ani_set);
}

void CItemSign::Render()
{
	if (isDestroy)
		return; 
	int ani = -1;
	switch (state)
	{
	case ITEM_SIGN_STATE_P:
		 ani = ITEM_SIGN_ANI_P;
		break;
	case ITEM_SIGN_STATE_SIGN:
		 ani = ITEM_SIGN_ANI_SIGN;
		break;
	}
	animation_set->at(ani)->Render(x, y);
	//RenderBoundingBox();
}

void CItemSign::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (isDestroy)
	{
		return;
	}
	if (state== ITEM_SIGN_STATE_P)
	{
		l = x;
		t = y;
		r = l + SIGN_BBOX_X_Y;
		b = t + SIGN_BBOX_X_Y;
	}
	else if(state == ITEM_SIGN_STATE_SIGN)
	{
		l = x;
		t = y+ SIGN_BBOX_YA;
		r = l + SIGN_BBOX_X_Y;
		b = t + SIGN_BBOX_YB;
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
	if (state == ITEM_SIGN_STATE_SIGN)
	{
		if (GetTickCount64() - time >= SIGN_TIME && time > 0)
		{
			SetState(ITEM_SIGN_STATE_P);
			time = 0;
		}
	}
	x += dx;
	y += dy;
}

void CItemSign::SetState(int state)
{
	CGameObject::SetState(state);
	if (isDestroy)
	{
		return;
	}
	switch (state)
	{
	case ITEM_SIGN_STATE_SIGN:
		time = GetTickCount64();
		break;
	case ITEM_SIGN_STATE_P:
		break;
	}
}

