#include "CEffectItem.h"

CEffectItem::CEffectItem(int state)
{
	this->state = state;
	SetState(EFFECTITEM_ANI_SET);
}

void CEffectItem::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case EFFECTITEM_ANI_SET:
		vx = 0;
		vy = 0;
		time = GetTickCount64();
		break;
	}
}

void CEffectItem::Render()
{
	if (isDestroy)
		return;
	int ani = EFFECTITEM_ANI_SET;
	animation_set->at(ani)->Render(x, y);

	RenderBoundingBox();
}

void CEffectItem::GetBoundingBox(float& l, float& t, float& r, float& b)
{

	if (isDestroy)
		return;
	l = x;
	t = y;
	r = x + EFFECTITEM_BBOX;
	b = y + EFFECTITEM_BBOX;

}

void CEffectItem::Update(DWORD dt, CScene* scene, vector<LPGAMEOBJECT>* coObjects)
{
	if (isDestroy)
	{
		return;
	}
	if (!CheckInCamera())
	{
		return;
	}
	CGameObject::Update(dt, scene, coObjects);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

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
	}


}