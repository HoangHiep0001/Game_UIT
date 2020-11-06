#include "Goomba.h"
#include "Ground.h"

CGoomba::CGoomba(int appe)
{
	apperance = appe;
	SetState(GOOMBA_STATE_WALKING);
}

void CGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	switch (state)
	{
	case GOOMBA_STATE_WALKING:
		right = x + GOOMBA_BBOX_X_Y;
		bottom = y + GOOMBA_BBOX_X_Y;
		break;
	case GOOMBA_STATE_FLYLING:
		right = x + GOOMBA_BBOX_WING;
		bottom = y + GOOMBA_BBOX_FLYING_Y;
		break;
	case GOOMBA_STATE_WALKING_WING:
		right = x + GOOMBA_BBOX_WING;
		bottom = y + GOOMBA_BBOX_WING;
		break;
	case GOOMBA_STATE_DIE:
			right= 0;
			bottom = 0;
			break;

	}
}
void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (isDestroy)
	{
		return;
	}
	CGameObject::Update(dt, coObjects);

	vy += GOOMBA_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();


	if (state == GOOMBA_STATE_DIE)
	{
		if (GetTickCount64() - time_die >= 200 )
		{
			Destroy();
		}
	}

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
			if (dynamic_cast<Ground*>(e->obj))
			{
				if (e->ny < 0)
				{
					vy = 0;
				}
				if (e->nx != 0)
				{
					nx = -nx;
					vx = -vx;
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



}

void CGoomba::Render()
{
	if (isDestroy)
		return;
	int ani = -1;
	if (apperance== GOOMBA_RED )
	{
		switch (state)
		{
		case GOOMBA_STATE_WALKING:
			ani = GOOMBA_ANI_RED_WALKING;
			break;
		case GOOMBA_STATE_FLYLING:
			ani = GOOMBA_ANI_RED_FLYLING;
			break;
		case GOOMBA_STATE_WALKING_WING:
			ani = GOOMBA_ANI_RED_WALKING_WING;
			break;
		case GOOMBA_STATE_DIE:
			ani = GOOMBA_ANI_RED_DIE;
			break;
		}
	}
	else if (apperance== GOOMBA_THERE)
	{
		switch (state)
		{
		case GOOMBA_STATE_WALKING:
			ani = GOOMBA_ANI_THERE_WALKING;
			break;
		case GOOMBA_STATE_FLYLING:
			ani = GOOMBA_ANI_THERE_FLYLING;
			break;
		case GOOMBA_STATE_WALKING_WING:
			ani = GOOMBA_ANI_THERE_WALKING_WING;
			break;
		case GOOMBA_STATE_DIE:
			ani = GOOMBA_ANI_THERE_DIE;
			break;
		}
	}
	
	animation_set->at(ani)->Render(x,y);

	//RenderBoundingBox();
}

void CGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case GOOMBA_STATE_DIE:
			vx = 0;
			vy = 0;
			time_die = GetTickCount64();
			break;
		case GOOMBA_STATE_WALKING: 
			if (vx > 0)
			{
				vx = GOOMBA_WALKING_SPEED;
			}
			else
			{
				vx = -GOOMBA_WALKING_SPEED;
			}
			break;
		case GOOMBA_STATE_FLYLING:
			vy = -GOOMBA_JUMP_FLY_SPEED_Y;
			if (vx>0)
			{
				vx = GOOMBA_WALKING_SPEED;
			}
			else
			{
				vx = -GOOMBA_WALKING_SPEED;
			}
			break;
		case GOOMBA_STATE_WALKING_WING:
			if (vx > 0)
			{
				vx = GOOMBA_WALKING_SPEED;
			}
			else
			{
				vx = -GOOMBA_WALKING_SPEED;
			}
			break;
	}
}
