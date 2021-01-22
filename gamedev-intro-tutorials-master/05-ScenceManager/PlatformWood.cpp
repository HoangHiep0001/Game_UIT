#include "PlatformWood.h"
CPlatformWood::CPlatformWood()
{
	SetState(PLATFORM_WOOD_STATE_PLATFORM_WOOD);
}
void CPlatformWood::Render()
{
	if (isDestroy)
	{
		return;
	}
	animation_set->at(0)->Render(x, y);
	RenderBoundingBox();
}

void CPlatformWood::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (isDestroy)
	{
		return;
	}
	l = x;
	t = y;
	r = x + PLATFORM_WOOD_BBOX_WIDTH;
	b = y + PLATFORM_WOOD_BBOX_HEIGHT;
}

void CPlatformWood::Update(DWORD dt, CScene* scene, vector<LPGAMEOBJECT>* coObjects)
{
	if (!CheckInCamera())
	{
		return;
	}

	if (isDestroy)
	{
		return;
	}
	CGameObject::Update(dt, scene, coObjects);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();



	CalcPotentialCollisions(coObjects, coEvents);
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


		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (e->nx != 0)
				x += dx;
			if (e->ny != 0)
				y += dy;
		}
	}
}

void CPlatformWood::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case PLATFORM_WOOD_STATE_PLATFORM_WOOD:
		vx = -PLATFORM_WOOD_VX;
		vy = 0;
		break;
	}
}
