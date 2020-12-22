#include "FireBallCacTus.h"
#include"PlayScence.h"

void CFireBallCacTus::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (isDestroy)
		return;
	left = x;
	top = y;
	right = x + FIREBAL_CACTUS_BBOX_WIDTH;
	bottom = y + FIREBAL_CACTUS_BBOX_HEIGHT;
}

CFireBallCacTus::CFireBallCacTus(int dir)
{
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(FIRE_BALL_ANISET);
	this->SetAnimationSet(ani_set);

	nx = dir;
	if (nx > 0)
	{
		SetState(FIREBAL_CACTUS_STATE_DOWN_RIGHT);
	}
	else
	{
		SetState(FIREBAL_CACTUS_STATE_DOWN_LEFT);
	}

}

void CFireBallCacTus::SetState(int state)
{
	if (isDestroy)
		return;

	CGameObject::SetState(state);
	switch (state)
	{
	case FIREBAL_CACTUS_STATE_DOWN_RIGHT:
		break;
	case FIREBAL_CACTUS_STATE_DOWN_LEFT:
		break;
	case FIREBAL_CACTUS_STATE_UP_RIGHT:
		break;
	case FIREBAL_CACTUS_STATE_UP_LEFT:
		break;
	}
}

void CFireBallCacTus::Update(DWORD dt, CScene* scene, vector<LPGAMEOBJECT>* colliable_objects)
{
	if (!isDestroy)
	{
		CGameObject::Update(dt, scene, colliable_objects);

		CPlayScene* pc = dynamic_cast<CPlayScene*>(scene);
		float l, t, r, b;
		CMario* mario = pc->GetPlayer();
		mario->GetBoundingBox(l, t, r, b);
		float targetX, targetY;
		
		if (first_time)
		{
			targetX = mario->x + (r - l) / 2;
			targetY = mario->y + (b - t) / 2;

			vx = (targetX - x) / FIREBALL_FLY_TIME;
			vy = (targetY - y) / FIREBALL_FLY_TIME;

			first_time = false;

		}
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
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];
				{
					vy = 0;
					if (e->nx != 0)
						x += dx;
					if (e->ny != 0)
						y += dy;
				}
			}
		}
		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	}
}

void CFireBallCacTus::Render()
{
	if (!isDestroy)
	{
		int ani = -1;
		switch (state)
		{
		case FIREBAL_CACTUS_STATE_DOWN_LEFT:
		case FIREBAL_CACTUS_STATE_UP_LEFT:
			ani = FIREBAL_CACTUS_ANI_LEFT;
			break;
		case FIREBAL_CACTUS_STATE_DOWN_RIGHT:
		case FIREBAL_CACTUS_STATE_UP_RIGHT:
			ani = FIREBAL_CACTUS_ANI_RIGHT;
			break;
		}

		animation_set->at(ani)->Render(x, y, 255);

		//RenderBoundingBox();
	}
}
