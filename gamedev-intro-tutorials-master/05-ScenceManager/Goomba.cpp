#include "Goomba.h"
#include "Ground.h"
#include "Brick.h"
#include "QuestionMark.h"
#include "Utils.h"

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
		right= x+0;
		bottom = y+0;
		break;

	}
	Bound.left = left;
	Bound.right = right;
	Bound.bottom = bottom;
	Bound.top = top;

	if (isDestroy)
	{
		right = 0;
		bottom = 0;
	}
}
void CGoomba::Update(DWORD dt, CScene* scene,vector<LPGAMEOBJECT> *coObjects)
{
	if (isDestroy)
	{
		return;
	}
	if (!CheckInCamera())
	{
		return;
	}
	if (time_die > 0)
	{
		DebugOut(L"[ERROR] Sprite ID %d cannot be found!\n", (GetTickCount64()-time_die));
	}
	if (state == GOOMBA_STATE_DIE)
	{
		if ((GetTickCount64() - time_die) >= GOOMBA_TIME_DIE)
		{
			Destroy();
		}
	}

	CGameObject::Update(dt, scene,coObjects);

	if (vy != 0)
	{
		vy += GOOMBA_GRAVITY * dt;
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
			else if (dynamic_cast<CBrick*>(e->obj))
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
			else if (dynamic_cast<CQuestionMark*>(e->obj))
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
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
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
			vx = -GOOMBA_WALKING_SPEED;
			break;
		case GOOMBA_STATE_FLYLING:
			vy = -GOOMBA_JUMP_FLY_SPEED_Y;
			vx = -GOOMBA_WALKING_SPEED;
			break;
	    case GOOMBA_STATE_WALKING_WING:			
			vx = -GOOMBA_WALKING_SPEED;			
		    break;
	}
}
