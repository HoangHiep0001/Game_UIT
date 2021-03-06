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

bool CKoopas::CheckPosition()
{
	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);
	float width = CGame::GetInstance()->GetScreenWidth();
	float height = CGame::GetInstance()->GetScreenHeight();
	if (startx > cx && startx < (cx + width) && starty > cy && starty < (cy + height))
	{
		return false;
	}
	return true;
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
	case KOOPAS_STATE_LIVE_FOOT_DOWN:
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
		if ((GetState() == KOOPAS_STATE_TORTOISESHELL_UP|| GetState() == KOOPAS_STATE_TORTOISESHELL_DOWN) && time > 0 && ispickup == false)
		{
			Destroy();
		}
		
		if (CheckPosition())
		{
			this->SetPosition(startx, starty);
			this->SetState(state_koopas);
			isDestroy = false;
		}
		return;
	}
	
	if (isDestroy)
	{
		return;
	}
	if (GetDirection() == 1)
	{
		if (state ==KOOPAS_STATE_WALKING)
		{
			if (this->x<=GetDistance_a())
			{
				nx =- nx;
				vx =- vx;
			}
			else if (this->x >= GetDistance_b())
			{
				nx =- nx;
				vx =- vx;
			}
		}
	}
	else if (GetDirection() == 2)
	{
		if (state == KOOPAS_STATE_FLYLING)
		{
			if (this->y <= GetDistance_a())
			{
				ny = -ny;
				vy = -vy;
			}
			else if (this->y >= GetDistance_b())
			{
				ny = -ny;
				vy = -vy;
			}
		}
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
					if (mario->GetApperance()==MARIO_FOX|| mario->GetApperance() == MARIO_FOX_FIRE)
					{
						x = mario->x + MARIO_BIG_BBOX_WIDTH + TIAL_BBOX_OFFSET;
						y = mario->y + KOOPAS_BIG_HOLD;
					}
					else
					{
						x = mario->x + MARIO_BIG_BBOX_WIDTH;
						y = mario->y + KOOPAS_BIG_HOLD;
					}
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
			if (state == KOOPAS_STATE_LIVING_UP)
			{
				nx = mario->nx;
				SetState(KOOPAS_STATE_TORTOISESHELL_UP);
				ispickup = false;
			}
			else if (state == KOOPAS_STATE_LIVING_DOWN)
			{
				nx = mario->nx;
				SetState(KOOPAS_STATE_TORTOISESHELL_DOWN);
				ispickup = false;
			}
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
	if (GetState() == KOOPAS_STATE_LIVING_DOWN && time > 0 && ispickup == false)
	{
		if ((GetTickCount64() - time) >= KOOPAS_TIME_LIVE)
		{

			state = KOOPAS_STATE_LIVE_FOOT_DOWN;
		}
	}
	if (GetState() == KOOPAS_STATE_LIVE_FOOT_DOWN && time > 0)
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
		if (GetDirection() != 2 )
		{
			vy += KOOPAS_GRAVITY * dt;
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
						vy = 0;
					}
					else vy = 0;
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
			else if(dynamic_cast<CGoomba*>(e->obj))
			{
				CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
				if (e->nx != 0|| e->ny != 0)
				{
					if (state == KOOPAS_STATE_TORTOISESHELL_UP|| state== KOOPAS_STATE_TORTOISESHELL_DOWN)
					{
						goomba->SetState(GOOMBA_STATE_WALKING_DOWN);
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
			else if (dynamic_cast<CMario*>(e->obj))
			{
				if (e->ny > 0)
				{
					if (state == KOOPAS_STATE_TORTOISESHELL_UP || state == KOOPAS_STATE_TORTOISESHELL_DOWN)
						vy = 0;
				}
			}
			else if (dynamic_cast<CBrick*>(e->obj))
			{
				CBrick* brick = dynamic_cast<CBrick*> (e->obj);
				if (e->ny < 0)
				{
					vy = 0;
				}
				if (e->nx != 0)
				{
					if (state == KOOPAS_STATE_TORTOISESHELL_UP || state == KOOPAS_STATE_TORTOISESHELL_DOWN)
					{
						if (brick->GetItemState() == 1)
						{
							if (brick->GetState() == BRICK_STATE_BRICK || brick->GetState() == BRICK_STATE_N_EMPTY)
							{
								SetState(BRICK_STATE_N_EMPTY);
								brick->SetItemCount(brick->GetItemCount() - 1);
								if (brick->GetItemCount() == 0)
								{
									brick->SetState(BRICK_STATE_EMPTY);
								}
								else if (brick->GetItemCount() > 0)
								{
									brick->SetState(BRICK_STATE_N_EMPTY);
								}
							}
						}
						else
						{
							//Effect(scene);
							brick->setIsBroken(true);
							brick->Destroy();
						}
					}
					
					nx = -nx;
					vx = -vx;
				}
			}
			else if (dynamic_cast<CKoopas*>(e->obj))
			{
				CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);
				if (state == KOOPAS_STATE_LIVING_UP || state == KOOPAS_STATE_LIVING_DOWN|| state == KOOPAS_STATE_TORTOISESHELL_UP || state == KOOPAS_STATE_TORTOISESHELL_DOWN)
				{
					koopas->SetState(KOOPAS_STATE_DIE_DOWN);
					if (GetTickCount64()-time> KOOPAS_TIME_DIE)
					{
						koopas->Destroy();
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
			else
			{
				x += dx;
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
				if (b > et && state != KOOPAS_STATE_FLYLING)
					vy = 0;
			}
		}
		else if (dynamic_cast<CBrick*>(e))
		{
			CBrick* brick = dynamic_cast<CBrick*> (e);

			float l, t, r, b, el, et, er, eb;
			this->GetBoundingBox(l, t, r, b);
			b = b;
			brick->GetBoundingBox(el, et, er, eb);
			if (CGameObject::AABB(l, t, r, b, el, et, er, eb))
			{
				if (e->ny < 0)
				{
					vy = 0;
				}
				if (e->nx != 0)
				{
					if (state == KOOPAS_STATE_TORTOISESHELL_UP || state == KOOPAS_STATE_TORTOISESHELL_DOWN)
					{
						if (brick->GetItemState() == 1)
						{
							if (brick->GetState() == BRICK_STATE_BRICK || brick->GetState() == BRICK_STATE_N_EMPTY)
							{
								SetState(BRICK_STATE_N_EMPTY);
								brick->SetItemCount(brick->GetItemCount() - 1);
								if (brick->GetItemCount() == 0)
								{
									brick->SetState(BRICK_STATE_EMPTY);
								}
								else if (brick->GetItemCount() > 0)
								{
									brick->SetState(BRICK_STATE_N_EMPTY);
								}
							}
						}
						else
						{
							//Effect(scene);
							brick->setIsBroken(true);
							brick->Destroy();
						}
					}
					nx = -nx;
					vx = -vx;
				}
			}
		}
		else if (dynamic_cast<CQuestionMark*>(e))
		{
			CQuestionMark* question = dynamic_cast<CQuestionMark*>(e);
			float l, t, r, b, el, et, er, eb;
			this->GetBoundingBox(l, t, r, b);
			b = b;
			question->GetBoundingBox(el, et, er, eb);
			if (CGameObject::AABB(l, t, r, b, el, et, er, eb))
			{
				if (e->nx != 0)
				{
					if (state == KOOPAS_STATE_TORTOISESHELL_UP || state == KOOPAS_STATE_TORTOISESHELL_DOWN)
					{
						if (question->GetState() == MARK_STATE_QUESTION || question->GetState() == MARK_STATE_N_EMPTY)
						{
							question->SetItemCount(question->GetItemCount() - 1);
							if (question->GetItemCount() == 0)
							{
								//Effect(scene);
								question->SetState(MARK_STATE_EMPTY);
							}
							else
							{
								//Effect(scene);
								question->SetState(MARK_STATE_N_EMPTY);
							}
						}
						nx = -nx;
						vx = -vx;
					}
					if (e->ny < 0)
					{
						vy = 0;
					}
				}
			}
		}
	}
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
		case KOOPAS_STATE_LIVE_FOOT_DOWN:
			ani = KOOPAS_ANI_RED_LIVE_FOOT_DOWN;
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
		case KOOPAS_STATE_LIVE_FOOT_DOWN:
			ani = KOOPAS_ANI_BULE_LIVE_FOOT_DOWN;
			break;
		}
	}

	animation_set->at(ani)->Render(x, y);

	//RenderBoundingBox();
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
		vx = 0;
		vy = 0;
		time = GetTickCount64();
		break;
	case KOOPAS_STATE_DIE_DOWN:
		vx = 0;
		vy = vy = -KOOPAS_DIE_VY;
		time = GetTickCount64();
		break;
	case KOOPAS_STATE_LIVING_DOWN:
		vx = 0;
		time = GetTickCount64();
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
		if (GetDirection() == 2)
		{
			vy = -0.04f;
			vx = 0;
		}
		else
		{
			vy = -KOOPAS_JUMP_SPEED_Y;
			vx = -KOOPAS_WALKING_SPEED;
		}
		
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
		if (nx > 0)
		{
			vx = KOOPAS_TORTOISESHELL;
		}
		else
		{
			vx = -KOOPAS_TORTOISESHELL;
		}
		time = GetTickCount64();
		break;
	case KOOPAS_STATE_LIVE_FOOT_UP:
	case KOOPAS_STATE_LIVE_FOOT_DOWN:
		break;
	}

}