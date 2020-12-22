#include "Goomba.h"
#include "Ground.h"
#include "Brick.h"
#include "QuestionMark.h"
#include "Utils.h"
#include "Koopas.h"
#include "PlayScence.h"

CGoomba::CGoomba(int appe)
{
	apperance = appe;
	SetState(GOOMBA_STATE_WALKING);
	nx = -1;
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
		bottom = y + GOOMBA_BBOX_FLYING_Y;
		break;
	case GOOMBA_STATE_DIE:
		right= x+0;
		bottom = y+0;
		break;
	case GOOMBA_STATE_WALKING_DOWN:
	case GOOMBA_STATE_FLYLING_DOWN:
	case GOOMBA_STATE_WALKING_WING_DOWN:
		right = x + 0;
		bottom = y + 0;
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
	if (!CheckInCamera())
	{
		if (isDestroy)
		{
			this->SetState(state_goomba);
			isDestroy = false;
		}
		return;
	}

	if (isDestroy)
	{
		this->SetPosition(startx, starty);
		return;
	}

	if (time_die > 0)
	{
		DebugOut(L"[ERROR] Sprite ID %d cannot be found!\n", (GetTickCount64()-time_die));
	}
	if (state == GOOMBA_STATE_DIE||state==GOOMBA_STATE_FLYLING_DOWN|| state == GOOMBA_STATE_WALKING_DOWN||state==GOOMBA_STATE_WALKING_WING_DOWN)
	{
		if ((GetTickCount64() - time_die) >= GOOMBA_TIME_DIE&&time_die>0)
		{
			Destroy();
		}
	}
	
	CGameObject::Update(dt, scene,coObjects);

	if (state == GOOMBA_STATE_WALKING_WING)
	{
		if ((GetTickCount64() - time) >= GOOMBA_TIME_WALK && time > 0)
		{
			SetState(GOOMBA_STATE_FLYLING);
			time = 0;
		}
	}

	vy += GOOMBA_GRAVITY * dt;


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
				if (state==GOOMBA_STATE_FLYLING||state==GOOMBA_STATE_WALKING||state== GOOMBA_STATE_WALKING_WING)
				{
					if (dynamic_cast<Ground*>(e->obj)->GetGroundState() == 1)
					{
						if (e->ny > 0)
						{
							y += dy;
							vy = 0;
						}
						if (e->nx != 0)
						{
							this->nx = -this->nx;
							vx = -vx;

						}
						if (e->ny < 0)
						{
							vy = 0;
							Updateflyling();
						}
					}
					if (dynamic_cast<Ground*>(e->obj)->GetGroundState() == 0)
					{
						if (e->ny < 0)
						{
							vy = 0;
							Updateflyling();
						}
						if (e->nx != 0)
						{
							this->nx = -this->nx;
							vx = -vx;
						}
					}
				}

		
			}
			else if (dynamic_cast<CBrick*>(e->obj))
			{
				if (e->ny < 0)
				{
					vy = 0;
					Updateflyling();
				}
				if (e->nx != 0)
				{
					this->nx = -this->nx;
					vx = -vx;
				}
			
			}
			else if (dynamic_cast<CQuestionMark*>(e->obj))
			{
				if (e->ny < 0)
				{
					vy = 0;
					Updateflyling();
				}
				if (e->nx != 0)
				{
					this->nx = -this->nx;
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

	for (std::size_t i = 0; i < coObjects->size(); i++)
	{
		LPGAMEOBJECT e = coObjects->at(i);
		if (dynamic_cast<Ground*>(e))
		{
			Ground* f = dynamic_cast<Ground*> (e);

			float l, t, r, b, el, et, er, eb;
			this->GetBoundingBox(l, t, r, b);
			b = b;
			f->GetBoundingBox(el, et, er, eb);
			if (CGameObject::AABB(l, t, r, b, el, et, er, eb))
			{
				if (b > et && state!=GOOMBA_STATE_FLYLING)
					vy = 0;
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
		case GOOMBA_STATE_WALKING_DOWN:
			ani = GOOMBA_ANI_RED_WALKING_DOWN;
			break;
		case GOOMBA_STATE_FLYLING_DOWN:
			ani = GOOMBA_ANI_RED_FLYLING_DOWN;
			break;
		case GOOMBA_STATE_WALKING_WING_DOWN:
			ani = GOOMBA_ANI_RED_WALKING_WING_DOWN;
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
		case GOOMBA_STATE_WALKING_DOWN:
			ani = GOOMBA_ANI_THERE_WALKING_DOWN;
			break;
		case GOOMBA_STATE_FLYLING_DOWN:
			ani = GOOMBA_ANI_THERE_FLYLING_DOWN;
			break;
		case GOOMBA_STATE_WALKING_WING_DOWN:
			ani = GOOMBA_ANI_THERE_WALKING_WING_DOWN;
			break;
		}
	}
	
	animation_set->at(ani)->Render(x,y);

	RenderBoundingBox();
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
			if (nx>0)
			{
				vx= GOOMBA_WALKING_SPEED;
			}
			else
			{
				vx = -GOOMBA_WALKING_SPEED;
			}	
			break;
		case GOOMBA_STATE_FLYLING:
			if (nx>0)
			{
				vx = GOOMBA_WALKING_SPEED;
			}
			else
			{
				vx = -GOOMBA_WALKING_SPEED;
			}		
			vy = -GOOMBA_JUMP_FLY_SPEED_Y;
			break;
	    case GOOMBA_STATE_WALKING_WING:	
			if (nx>0)
			{
				vx = GOOMBA_WALKING_SPEED;
			}
			else
			{
				vx = -GOOMBA_WALKING_SPEED;
			}	
			vy = -GOOMBA_JUMP_SPEED_Y;
			time = GetTickCount64();
		    break;
		case GOOMBA_STATE_WALKING_DOWN:
		case GOOMBA_STATE_FLYLING_DOWN:
		case GOOMBA_STATE_WALKING_WING_DOWN:
			vx = 0;
			vy = -GOOMBA_JUMP_SPEED_Y;
			time_die = GetTickCount64();
			break;
	}
}

void CGoomba::Updateflyling()
{
	if (state == GOOMBA_STATE_FLYLING)
	{
			SetState(GOOMBA_STATE_WALKING_WING);
	}
}
