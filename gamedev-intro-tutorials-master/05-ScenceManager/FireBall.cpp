#include "FireBall.h"
#include "Goomba.h"
#include "Ground.h"


CFireBall::CFireBall(int dir)
{
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(FIRE_BALL_ANISET);
	this->SetAnimationSet(ani_set);

	nx = dir;
	if (nx > 0)
	{
		SetState(FIREBALL_STATE_DOWN_RIGHT);
	}
	else
	{
		SetState(FIREBALL_STATE_DOWN_LEFT);
	}

}

void CFireBall::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + FIREBALL_BBOX_WIDTH;
	bottom = y + FIREBALL_BBOX_HEIGHT;
}

void CFireBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!isDestroy)
	{
		CGameObject::Update(dt, coObjects);

		//
		// TO-DO: make sure FIREBALL can interact with the world and to each of them too!
		// 

		if (!first_time)
		{
			if (y < MaxY)
			{
				vy = FIREBALL_Y;
			}
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

			// TODO: This is a very ugly designed function!!!!
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

			// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
			//if (rdx != 0 && rdx!=dx)
			//	x += nx*abs(rdx); 

			// block every object first!
			x += min_tx * dx + nx * 0.4f;
			y += min_ty * dy + ny * 0.4f;


			// Collision logic with other objects
			//
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];
				if (dynamic_cast<Ground*>(e->obj))
				{
					if (e->ny < 0)
					{
						vy = -FIREBALL_Y;
						MaxY = dynamic_cast<Ground*>(e->obj)->y - FIRE_BALL_MAX_Y;
						first_time = false;
					}
					if (e->nx != 0)
					{
						Destroy();
					}
				}
				else
				{
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

void CFireBall::Render()
{
	if (!isDestroy)
	{
		int ani = -1;
		switch (state)
		{
		case FIREBALL_STATE_DOWN_LEFT:
		case FIREBALL_STATE_UP_LEFT:
			ani = FIREBALL_ANI_LEFT;
			break;
		case FIREBALL_STATE_DOWN_RIGHT:
		case FIREBALL_STATE_UP_RIGHT:
			ani = FIREBALL_ANI_RIGHT;
			break;
		}

		animation_set->at(ani)->Render(x, y, 250);

		//RenderBoundingBox();
	}
}

void CFireBall::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case FIREBALL_STATE_DOWN_RIGHT:
		vx = FIREBALL_X;
		vy = FIREBALL_Y;
		break;
	case FIREBALL_STATE_DOWN_LEFT:
		vx = -FIREBALL_X;
		vy = FIREBALL_Y;
		break;
	case FIREBALL_STATE_UP_RIGHT:
		vx = FIREBALL_X;
		vy = -FIREBALL_Y;
		break;
	case FIREBALL_STATE_UP_LEFT:
		vx = -FIREBALL_X;
		vy = -FIREBALL_Y;
		break;
	}

}