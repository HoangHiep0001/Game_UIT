#include "CBroken.h"
#include "PlayScence.h"
CBroken::CBroken()
{
	SetState(BROKEN_STATE_BROKEN);
}

void CBroken::Render()
{
	CSprites::GetInstance()->Get(BROKEN_ANI_BROKEN)->Draw(x, y, 255);
	CSprites::GetInstance()->Get(BROKEN_ANI_BROKEN)->Draw(x+8, y, 255);
	CSprites::GetInstance()->Get(BROKEN_ANI_BROKEN)->Draw(x, y+8, 255);
	CSprites::GetInstance()->Get(BROKEN_ANI_BROKEN)->Draw(x + 8, y+8, 255);
	RenderBoundingBox();
}

void CBroken::Update(DWORD dt, CScene* scene, vector<LPGAMEOBJECT>* coObjects)
{
	if (!CheckInCamera())
	{
		return;
	}
	CGameObject::Update(dt, scene, coObjects);
	x += dx;
	y += dy;
	switch (state)
	{
	case 1:
		state = BROKEN_ANI_BROKEN;
		break;
	case 2:
		state = BROKEN_ANI_BROKEN;
		break;
	case 3:
		state = BROKEN_ANI_BROKEN;
		break;
	case 4:
		state = BROKEN_ANI_BROKEN;
		break;
	}
	 
}


void CBroken::GetBoundingBox(float& l, float& t, float& r, float& b)
{

	if (isDestroy)
		return;
	l = x;
	t = y;
	r = x + BROKEN_BBOX_WIDTH;
	b = y + BROKEN_BBOX_HEIGHT;
}


