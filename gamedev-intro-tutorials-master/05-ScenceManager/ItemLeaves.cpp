#include "ItemLeaves.h"
#include "PlayScence.h"
#include "Ground.h"

CLeaves::CLeaves()
{
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(LEAVES_ANI_SET);
	this->SetAnimationSet(ani_set);
	SetState(LEAVES_STATE_FALL);
}
void CLeaves::SetState(int state)
{
	this->state = state;
	if (state==LEAVES_STATE_FALL)
	{
		nx = -1;
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

	vy = LEAVES_GRAVITY;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(colliable_objects, coEvents);
	if (coEvents.size() == 0)
	{
		x = 18 * sin(y * 0.25f) + ox;;
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

		x = 18 * sin(y * 0.25f) + ox;;
		y += dy;

	}
	for (UINT i = 0; i < coEventsResult.size(); i++)
	{
		LPCOLLISIONEVENT e = coEventsResult[i];
		if (dynamic_cast<Ground*>(e->obj))
		{
				x += dx;
				y += dy;
		}
		else if (dynamic_cast<CBrick*>(e->obj))
		{
				x += dx;
				y += dy;
		}
		else if (dynamic_cast<CQuestionMark*>(e->obj))
		{
				x += dx;
				y += dy;
		}
		else
		{
			if (e->nx != 0)
				x += dx;
			if (e->ny != 0)
				y += dy;
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

}