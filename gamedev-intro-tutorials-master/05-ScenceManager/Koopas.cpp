#include "Koopas.h"
#include "Ground.h"
#include "Brick.h"
#include "QuestionMark.h"
#include "Mario.h"
#include "PlayScence.h"

CKoopas::CKoopas(int appe)
{
	apperance = appe;
	//SetState(KOOPAS_STATE_WALKING);
}

void CKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	switch (state)
	{
	case KOOPAS_STATE_WALKING:
		right = x + KOOPAS_BBOX_WIDTH;
		bottom = y + KOOPAS_BBOX_HEIGHT;
		break;
	case KOOPAS_STATE_FLYLING:
		right = x + KOOPAS_BBOX_WIDTH;
		bottom = y + KOOPAS_BBOX_HEIGHT;
		break;
	case KOOPAS_STATE_DIE_UP:
		right = x;
		bottom = y;
		break;
	case KOOPAS_STATE_LIVING_UP:
		right = x + KOOPAS_BBOX_LIVING;
		bottom = y + KOOPAS_BBOX_LIVING;
		break;
	case KOOPAS_STATE_TORTOISESHELL_UP:
		right = x + KOOPAS_BBOX_LIVING;
		bottom = y + KOOPAS_BBOX_LIVING;
		break;
	case KOOPAS_STATE_DIE_DOWN:
		right = x;
		bottom = y;
		break;
	case KOOPAS_STATE_LIVING_DOWN:
		right = x + KOOPAS_BBOX_LIVING;
		bottom = y + KOOPAS_BBOX_LIVING;
		break;
	case KOOPAS_STATE_TORTOISESHELL_DOWN:
		right = x + KOOPAS_BBOX_LIVING;
		bottom = y + KOOPAS_BBOX_LIVING;
		break;
	case KOOPAS_STATE_LIVE_FOOT_UP:
		right = x + KOOPAS_BBOX_LIVING;
		bottom = y + KOOPAS_BBOX_LIVING;
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

void CKoopas::Update(DWORD dt, CScene* scene, vector<LPGAMEOBJECT>* coObjects)
{
	if (!CheckInCamera())
	{
		return;
	}
	if (isDestroy)
	{
		return;
	}

	if (ispickup)
	{
		CPlayScene* pc = dynamic_cast<CPlayScene*>(scene);
		CMario* mario = pc->GetPlayer();
		if (mario->GetPick())
		{
			if (mario->GetLevel() == MARIO_LEVEL_BIG)
			{
				if (mario->nx > 0)
				{
					x = mario->x + MARIO_BIG_BBOX_WIDTH;
					y = mario->y + KOOPAS_BIG_HOLD;
				}
				else
				{
					x = mario->x - KOOPAS_BBOX_LIVING;
					y = mario->y + KOOPAS_BIG_HOLD;
				}
			}
			if (mario->GetLevel() == MARIO_LEVEL_SMALL)
			{
				if (mario->nx > 0)
				{
					x = mario->x + MARIO_SMALL_BBOX_WIDTH;
					y = mario->y - KOOPAS_SMALL_HOLD;
				}
				else
				{
					x = mario->x - KOOPAS_BBOX_LIVING;
					y = mario->y - KOOPAS_SMALL_HOLD;
				}
			}
		}
		else
		{
			nx = mario->nx;
			SetState(KOOPAS_STATE_TORTOISESHELL_UP);
			ispickup = false;
		}
	}
	if (GetState() == KOOPAS_STATE_TORTOISESHELL_UP && time > 0 && ispickup == false)
	{
		if ((GetTickCount64() - time) >= KOOPAS_TIME_LIVING)
		{
			Destroy();
		}
	}
	if (GetState() == KOOPAS_STATE_LIVING_UP && time>0 && ispickup == false)
	{
		if ((GetTickCount64() - time) >= KOOPAS_TIME_LIVE)
		{
			
			state = KOOPAS_STATE_LIVE_FOOT_UP;
		}
	}
	if (GetState() == KOOPAS_STATE_LIVE_FOOT_UP && time>0)
	{
		if ((GetTickCount64() - time) >= KOOPAS_TIME_LIVE_FOOT)
		{
			y -= KOOPAS_Y;
			SetState(KOOPAS_STATE_WALKING);
			time = 0;
		}
	}
	CGameObject::Update(dt, scene, coObjects);
	if (!ispickup)
	{
		vy += KOOPAS_GRAVITY * dt;
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
				if (dynamic_cast<Ground*>(e->obj)->GetGroundState() == 1)
				{
					if (e->ny > 0)
					{
						y += dy;
					}
					if (e->nx != 0)
					{
						nx = -nx;
						vx = -vx;
					}
				}
				if (dynamic_cast<Ground*>(e->obj)->GetGroundState() == 0)
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
 				if (state== KOOPAS_STATE_FLYLING)
				{
					vy = -KOOPAS_JUMP_SPEED_Y;
				}
			}
			else if (dynamic_cast<CBrick*>(e->obj))
			{
				CBrick* brick = dynamic_cast<CBrick*>(e->obj);
				if (e->ny < 0)
				{
					vy = 0;
				}
				if (e->nx != 0)
				{
					if (state==KOOPAS_STATE_TORTOISESHELL_UP)
					{
						brick->Destroy();
					}
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
			else if(dynamic_cast<CGoomba*>(e->obj))
			{
				CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
				if (e->nx != 0)
				{
					if (state == KOOPAS_STATE_LIVING_UP)
					{
						goomba->SetState(GOOMBA_STATE_DIE);
					}
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

void CKoopas::Render()
{
	if (isDestroy)
	{
		return;
	}
	int ani = -1;
	if (apperance == KOOPAS_RED)
	{
		switch (state)
		{
		case KOOPAS_STATE_WALKING:
			if (vx > 0)
			{
				ani = KOOPAS_ANI_RED_WALKING_RIGHT;
			}
			else
			{
				ani = KOOPAS_ANI_RED_WALKING_LEFT;
			}

			break;
		case KOOPAS_STATE_FLYLING:
			if (vx > 0)
			{
				ani = KOOPAS_ANI_RED_FLYLING_RIGHT;
			}
			else
			{
				ani = KOOPAS_ANI_RED_FLYLING_LEFT;
			}
			break;
		case KOOPAS_STATE_DIE_UP:
		case KOOPAS_STATE_LIVING_UP:
			ani = KOOPAS_ANI_RED_DIE_UP;
			break;
		case KOOPAS_STATE_TORTOISESHELL_UP:
			ani = KOOPAS_ANI_RED_TORTOISESHELL_UP;
			break;
		case KOOPAS_STATE_DIE_DOWN:
		case KOOPAS_STATE_LIVING_DOWN:
			ani = KOOPAS_ANI_RED_DIE_DOWN;
			break;
		case KOOPAS_STATE_TORTOISESHELL_DOWN:
			ani = KOOPAS_ANI_RED_TORTOISESHELL_DOWN;
			break;
		case KOOPAS_STATE_LIVE_FOOT_UP:
			ani = KOOPAS_ANI_RED_LIVE_FOOT_UP;
			break;
		}
	}
	else if (apperance == KOOPAS_BULE)
	{
		switch (state)
		{
		case KOOPAS_STATE_WALKING:
			if (vx > 0)
			{
				ani = KOOPAS_ANI_BULE_WALKING_RIGHT;
			}
			else
			{
				ani = KOOPAS_ANI_BULE_WALKING_LEFT;
			}

			break;
		case KOOPAS_STATE_FLYLING:
			if (vx > 0)
			{
				ani = KOOPAS_ANI_BULE_FLYLING_RIGHT;
			}
			else
			{
				ani = KOOPAS_ANI_BULE_FLYLING_LEFT;
			}
			break;

		case KOOPAS_STATE_DIE_UP:
		case KOOPAS_STATE_LIVING_UP:
			ani = KOOPAS_ANI_BULE_DIE_UP;
			break;
		case KOOPAS_STATE_TORTOISESHELL_UP:
			ani = KOOPAS_ANI_BULE_TORTOISESHELL_UP;
			break;
		case KOOPAS_STATE_DIE_DOWN:
		case KOOPAS_STATE_LIVING_DOWN:
			ani = KOOPAS_ANI_BULE_DIE_DOWN;
			break;
		case KOOPAS_STATE_TORTOISESHELL_DOWN:
			ani = KOOPAS_ANI_BULE_TORTOISESHELL_DOWN;
			break;
		case KOOPAS_STATE_LIVE_FOOT_UP:
			ani = KOOPAS_ANI_BULE_LIVE_FOOT_UP;
			break;
		}
	}

	animation_set->at(ani)->Render(x, y);

	RenderBoundingBox();
}

void CKoopas::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPAS_STATE_DIE_UP:
		vx = 0;
		vy = 0;
		break;
	case KOOPAS_STATE_LIVING_UP:
		y += KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_LIVING;
		vx = 0;
		vy = 0;
		time = GetTickCount64();
		break;
	case KOOPAS_STATE_DIE_DOWN:
		vx = 0;
		vy = 0;
		break;
	case KOOPAS_STATE_LIVING_DOWN:
		y += KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_LIVING;
		vx = 0;
		vy = 0;
		break;
	case KOOPAS_STATE_WALKING:
		nx = -1;
		if (nx > 0)
		{
			vx = KOOPAS_WALKING_SPEED;
		}
		else
		{
			vx = -KOOPAS_WALKING_SPEED;
		}
		break;
	case KOOPAS_STATE_FLYLING:
		nx = -1;
		vy = -KOOPAS_JUMP_SPEED_Y;
		vx = -KOOPAS_WALKING_SPEED;
		break;
	case KOOPAS_STATE_TORTOISESHELL_UP:
		if (nx>0)
		{
			vx = KOOPAS_TORTOISESHELL;
		}
		else
		{
			vx = -KOOPAS_TORTOISESHELL;
		}
		time = GetTickCount64();
		break;
	case KOOPAS_STATE_TORTOISESHELL_DOWN:
		vx = KOOPAS_TORTOISESHELL;
		break;
	case KOOPAS_STATE_LIVE_FOOT_UP:
		break;
	}

}