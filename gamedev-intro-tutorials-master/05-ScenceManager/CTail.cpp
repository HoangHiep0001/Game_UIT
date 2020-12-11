#include "CTail.h"
#include "Mario.h"
#include "PlayScence.h"

CTail::CTail(CScene* scene,int dir)
{
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	nx = dir;
}

void CTail::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + TAIL_BBOX_WIDTH;
	bottom = y + TAIL_BBOX_HEIGHT;
}

void CTail::Update(DWORD dt, CScene* scene, vector<LPGAMEOBJECT>* coObjects)
{
	CPlayScene* pc = dynamic_cast<CPlayScene*>(scene);
	CMario* mario = pc->GetPlayer();
	if (mario->GetIsTail())
	{
		if (mario->GetLevel() == MARIO_LEVEL_BIG)
		{
			if (mario->GetApperance() == MARIO_FOX || mario->GetApperance() == MARIO_FOX_FIRE)
			{
				if (mario->nx > 0)
				{
					x = mario->x - 8;
					y = mario->y + 19;
				}
				else
				{
					x = mario->x + MARIO_BIG_BBOX_WIDTH;
					y = mario->y + 19;
				}

			}
		}
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
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CTail::Render()
{
	animation_set->at(0)->Render(x, y, 255);
	RenderBoundingBox();
}
