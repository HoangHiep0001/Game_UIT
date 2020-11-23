#include "ItemLeaves.h"
#include "PlayScence.h"

CLeaves::CLeaves()
{
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(LEAVES_ANI_SET);
	this->SetAnimationSet(ani_set);
	SetState(LEAVES_STATE_FALL);
}
void CLeaves::SetState(int state)
{
	CGameObject::SetState(state);
	if (state==LEAVES_STATE_FALL)
	{
		nx = -1;
		if (nx>0)
		{
			vx = LEAVES_SPEED_X;
		}
		else
		{
			vx =-LEAVES_SPEED_X;
		}
	//	vy = -LEAVES_SPEED_Y;
	}
}
void CLeaves::Render()
{
	if (isDestroy)
		return;
	int ani = -1;
	switch (state)
	{
	case LEAVES_STATE_FALL:
		if (nx>0)
		{
			ani = LEAVES_ANI_RIGHT;
		}
		else
		{
			 ani = LEAVES_ANI_LEFT;
		}
		break;
	}
	animation_set->at(ani)->Render(x, y);

	RenderBoundingBox();
}

void CLeaves::GetBoundingBox(float& l, float& t, float& r, float& b)
{

	if (isDestroy)
		return;
	l = x;
	t = y;
	r = x + LEAVES_BBOX_X;
	b = y + LEAVES_BBOX_Y;

}

void CLeaves::Update(DWORD dt, CScene* scene, vector<LPGAMEOBJECT>* colliable_objects)
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

	vy += LEAVES_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(colliable_objects, coEvents);
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

	}
	if (y >= start_y - LEAVES_Y)
	{
		//vy = -LEAVES_SPEED_Y;
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}