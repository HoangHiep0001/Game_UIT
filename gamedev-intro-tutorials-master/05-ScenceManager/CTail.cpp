#include "CTail.h"
#include "Mario.h"
#include "PlayScence.h"

CTail::CTail(CScene* scene,int dir)
{
	nx = dir;
	this->tailHead = new CTailPoint(dir);
	this->tailLast = new CTailPoint(dir);

}

void CTail::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (isDestroy)
		return;
	float xh, yh, xl, yl;

	tailHead->GetPosition(xh, yh);
	tailLast->GetPosition(xl, yl);

	if (xh < xl)
	{
		left = xh;
		top = yh;
		right = xl;
		bottom = top + TAIL_BBOX_HEIGHT;
	}
	else
	{
		left = xl;
		top = yl;
		right = xh;
		bottom = top + TAIL_BBOX_HEIGHT;
	}
}

void CTail::Update(DWORD dt, CScene* scene, vector<LPGAMEOBJECT>* coObjects)
{
	if (isDestroy)
		return;


	CGameObject::Update(dt, scene, coObjects);

	float xh, yh, xl, yl;
	
	tailHead->GetPosition(xh, yh);
	tailLast->GetPosition(xl, yl);

	if (xh < xl)
	{
		x = xh;
		y = yh;
	}
	else
	{
		x = xl;
		y = yl;
	}

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

	}
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CTail::Render()
{
	if (isDestroy)
		return;
	RenderBoundingBox();
}
