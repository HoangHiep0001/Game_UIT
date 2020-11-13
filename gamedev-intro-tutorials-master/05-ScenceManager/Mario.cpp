#include <algorithm>
#include <assert.h>
#include "Utils.h"
#include "Mario.h"
#include "Game.h"
#include "Goomba.h"
#include "Portal.h"
#include "Ground.h"
#include "FireBall.h"
#include "Brick.h"
#include "QuestionMark.h"
#include "Coin.h"
#include "Koopas.h"
#include "PlayScence.h"



CMario::CMario(float x, float y) : CGameObject()
{
	apperance = MARIO_NORMAL;
	level = MARIO_LEVEL_SMALL;
	untouchable = 0;
	SetState(MARIO_STATE_IDLE);
	a = 0;
	a_stop = 0;
	time_stop = 0;
	time_fly = 0;
	start_x = x; 
	start_y = y; 
	this->x = x; 
	this->y = y; 
}

void CMario::UpLevel()
{
	if (level == MARIO_LEVEL_SMALL)
		y -= UPLEVEL_OFFSET;
	level = MARIO_LEVEL_BIG;
	
}

void CMario::Update(DWORD dt, CScene* scene, vector<LPGAMEOBJECT>* coObjects)
{

	// Calculate dx, dy 
	CGameObject::Update(dt, scene);

	if (a == 0 && a_stop != 0)
	{
		vx -= a_stop * dt;
		if (nx > 0)
		{
			if (vx < 0)
			{
				a_stop = 0;
				vx = 0;
			}
		}
		else
		{
			if (vx > 0)
			{
				a_stop = 0;
				vx = 0;
			}
		}
	}

	if (abs(vx) > MARIO_WALKING_SPEED_MAX)
		vx = vx;
	else
		vx += a * dt;

	// Simple fall down
	if (state != MARIO_STATE_FLYLING)
	{
		vy += MARIO_GRAVITY * dt;
	}
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state != MARIO_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	//kiem tra tan cong xong chua
	if (state == MARIO_STATE_ATTACK)
	{
		isAttack = CheckLastFrameAttack();
	}

	if (state == MARIO_STATE_FIRE_BALL)
	{
		isFireBall = CheckLastFrameAttack();
	}


	if (state == MARIO_STATE_FLYLING)
	{
		if (GetTickCount64() - time_fly > TIME_FLYLING_MARIO)
			SetState(MARIO_STATE_LANDING);
	}

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}
	if (state == MARIO_STATE_JUMP)
	{
		if (vy > 0)
			state = MARIO_STATE_IDLE;
	}
	// No collision occured, proceed normally
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

			if (dynamic_cast<CGoomba*>(e->obj)) // if e->obj is Goomba 
			{
				CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
				if (e->ny < 0)
				{
					if (goomba->GetState() == GOOMBA_STATE_WALKING)
					{
						if (goomba->GetApperance() == GOOMBA_RED)
						{
							goomba->SetState(GOOMBA_STATE_DIE);

						}
						if (goomba->GetApperance() == GOOMBA_THERE)
						{
							goomba->SetState(GOOMBA_STATE_DIE);

						}
						vy = -MARIO_JUMP_DEFLECT_SPEED;
					}
					if ((goomba->GetState() == GOOMBA_STATE_WALKING_WING) || (goomba->GetState() == GOOMBA_STATE_FLYLING))
					{
						if (goomba->GetApperance() == GOOMBA_RED)
						{
							goomba->SetState(GOOMBA_STATE_WALKING);
							goomba->y += GOOMBA_BBOX_Y;
						}
						else if (goomba->GetApperance() == GOOMBA_THERE)
						{
							goomba->SetState(GOOMBA_STATE_WALKING);
							goomba->y += GOOMBA_BBOX_Y;
						}
						vy = -MARIO_JUMP_DEFLECT_SPEED;
					}
				}
				if (e->nx != 0)
				{
					if (untouchable == 0)
					{
						if (state == MARIO_STATE_ATTACK)
						{
							if (goomba->GetApperance() == GOOMBA_RED)
							{
								goomba->SetState(GOOMBA_STATE_DIE);

							}
							if (goomba->GetApperance() == GOOMBA_THERE)
							{
								goomba->SetState(GOOMBA_STATE_DIE);
							}
						}
						else if (goomba->GetState() != GOOMBA_STATE_DIE)
						{
							if (level > MARIO_LEVEL_SMALL)
							{
								if (apperance == MARIO_NORMAL)
								{
									level = MARIO_LEVEL_SMALL;
									StartUntouchable();
								}
								else if (apperance == MARIO_FOX)
								{
									apperance = MARIO_NORMAL;
									level = MARIO_LEVEL_BIG;
									StartUntouchable();
								}
								else if (apperance == MARIO_FIRE)
								{
									apperance = MARIO_NORMAL;
									level = MARIO_LEVEL_SMALL;
									StartUntouchable();
								}
							}
							else
								SetState(MARIO_STATE_DIE);

						}
					}
				}
			}
			else if (dynamic_cast<CKoopas*>(e->obj))
			{
				CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);
				if (e->ny < 0)
				{
					if (koopas->GetState() == KOOPAS_STATE_WALKING)
					{
						if (koopas->GetApperance() == KOOPAS_RED)
						{
							koopas->SetState(KOOPAS_STATE_LIVING_UP);
						}
						if (koopas->GetApperance() == KOOPAS_BULE)
						{
							koopas->SetState(KOOPAS_STATE_LIVING_UP);
						}
						vy = -MARIO_JUMP_DEFLECT_SPEED;
					}
					if (koopas->GetState() == KOOPAS_STATE_FLYLING)
					{
						if (koopas->GetApperance() == KOOPAS_RED)
						{
							koopas->SetState(KOOPAS_STATE_WALKING);
						}
						if (koopas->GetApperance() == KOOPAS_BULE)
						{
							koopas->SetState(KOOPAS_STATE_WALKING);
						}
						vy = -MARIO_JUMP_DEFLECT_SPEED;
					}
				}
				if (e->nx != 0)
				{
					if (untouchable == 0)
					{
						if (state == MARIO_STATE_ATTACK)
						{
							if (koopas->GetApperance() == KOOPAS_RED)
							{
								koopas->SetState(KOOPAS_STATE_DIE_UP);

							}
							if (koopas->GetApperance() == KOOPAS_BULE)
							{
								koopas->SetState(KOOPAS_STATE_DIE_UP);
							}
						}
						else if (state == MARIO_STATE_WALKING_LEFT || state == MARIO_STATE_WALKING_RIGHT)
						{
							if (koopas->state == (KOOPAS_STATE_LIVING_UP))
							{
								SetState(MARIO_STATE_STONE_KOOPAS);
								koopas->nx = -nx;
								koopas->SetState(KOOPAS_STATE_TORTOISESHELL_UP);
							}
						}
						else if (state == MARIO_STATE_HOLD)
						{
							if (koopas->state == (KOOPAS_STATE_LIVING_UP))
							{
								koopas->SetIsPick(true);
							}
						}
						else if ((koopas->GetState() != KOOPAS_STATE_DIE_UP) && (koopas->GetState() != KOOPAS_STATE_LIVING_UP))
						{
							if (level > MARIO_LEVEL_SMALL)
							{
								if (apperance == MARIO_NORMAL)
								{
									level = MARIO_LEVEL_SMALL;
									StartUntouchable();
								}
								else if (apperance == MARIO_FOX)
								{
									apperance = MARIO_NORMAL;
									level = MARIO_LEVEL_BIG;
									StartUntouchable();
								}
								else if (apperance == MARIO_FIRE)
								{
									apperance = MARIO_NORMAL;
									level = MARIO_LEVEL_SMALL;
									StartUntouchable();
								}
							}
							else
								SetState(MARIO_STATE_DIE);
						}
					}
				}
			}
			else if (dynamic_cast<CPortal*>(e->obj))
			{
				CPortal* p = dynamic_cast<CPortal*>(e->obj);
				CGame::GetInstance()->SwitchScene(p->GetSceneId());
			}
			else if (dynamic_cast<Ground*>(e->obj))
			{
				if (e->ny < 0)
				{
					if (state == MARIO_STATE_LANDING)
						SetState(MARIO_STATE_IDLE);
					vy = 0;
					time_jump = 0;
				}
				if (dynamic_cast<Ground*>(e->obj)->GetGroundState() == 1)
				{
					if (e->ny > 0)
						y += dy;
				}
				else vy = 0;
				if (e->nx != 0)
				{
					if (dynamic_cast<Ground*>(e->obj)->GetGroundState() == 0)
					{
						vx = 0;
						a = 0;
					}
					else
					{
						x += dx;
					}
				}

				if (e->ny < 0 && state == MARIO_STATE_FIRE_BALL_DOUBLE)
				{
					state = MARIO_STATE_IDLE;
					isSpawnShot = false;
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
					vx = 0;
					a = 0;
				}

			}
			else if (dynamic_cast<CQuestionMark*>(e->obj))
			{
				CQuestionMark* question = dynamic_cast<CQuestionMark*>(e->obj);

				if (e->ny < 0)
				{
					vy = 0;
				}
				if (e->ny > 0)
				{
					if (question->GetState() == MARK_STATE_QUESTION)
					{
						question->SetState(MARK_STATE_EMPTY);
						vy = 0;
					}
					else
					{
						vy = 0;
					}
				}

				if (e->nx != 0)
				{
					vx = 0;
					a = 0;
				}
			}
			else if (dynamic_cast<CCoin*>(e->obj))
			{
				if (e->ny != 0 || e->nx != 0)
				{
					CCoin* coin = dynamic_cast<CCoin*>(e->obj);
					coin->Destroy();
					x += dx;
					y += dy;
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


	for (std::size_t i = 0; i < coObjects->size(); i++)
	{
		LPGAMEOBJECT e = coObjects->at(i);

	}
	if (level == MARIO_LEVEL_BIG)
	{
		if (apperance == MARIO_FIRE)
		{
			if (state == MARIO_STATE_FIRE_BALL)
			{
				if (CheckFrameFireBall() && isSpawnFireBall == false)
				{
					CFireBall* fireball = new CFireBall(this->nx);
					if (nx > 0)
					{
						fireball->SetPosition(x + FIRE_BALL, y + FIRE_BALL);
						CPlayScene* pc = dynamic_cast<CPlayScene*>(scene);
						pc->SpawnObject(fireball);
					}
					else
					{
						fireball->SetPosition(x, y + FIRE_BALL);
						CPlayScene* pc = dynamic_cast<CPlayScene*>(scene);
						pc->SpawnObject(fireball);
					}
					isSpawnFireBall = true;
				}
			}
			
			if (state == MARIO_STATE_FIRE_BALL_DOUBLE)
			{
				if (isSpawnShot == false)
				{
					if (CheckFrameFireBall() && isSpawnFireBallDouble == false)
					{
						CFireBall* fireball = new CFireBall(this->nx);
						if (nx > 0)
						{
							fireball->SetPosition(x + FIRE_BALL, y + FIRE_BALL);
							CPlayScene* pc = dynamic_cast<CPlayScene*>(scene);
							pc->SpawnObject(fireball);
						}
						else
						{
							fireball->SetPosition(x, y + FIRE_BALL);
							CPlayScene* pc = dynamic_cast<CPlayScene*>(scene);
							pc->SpawnObject(fireball);
						}
						isSpawnFireBallDouble = true;
					}
					isSpawnShot = true;
				}
				if (time_doubleshot > 0 && GetTickCount64() - time_doubleshot > TIME_FIRE_BALL)
				{
					if (CheckFrameFireBallDouble() && isSpawnFireBallDouble == false)
					{
						CFireBall* fireball = new CFireBall(this->nx);
						if (nx > 0)
						{
							fireball->SetPosition(x + FIRE_BALL, y + FIRE_BALL);
							CPlayScene* pc = dynamic_cast<CPlayScene*>(scene);
							pc->SpawnObject(fireball);
						}
						else
						{
							fireball->SetPosition(x, y + FIRE_BALL);
							CPlayScene* pc = dynamic_cast<CPlayScene*>(scene);
							pc->SpawnObject(fireball);
						}
						time_doubleshot = 0;

						isSpawnFireBallDouble = true;
					}
				}
			}
		}
	}
}



void CMario::ChangeApperance(int apperance_change)
{
	this->apperance = apperance_change;
}

void CMario::SetState(int state)
{
	CGameObject::SetState(state);
	a = 0;	
	isSit = false;
	switch (state)
	{
	case MARIO_STATE_WALKING_RIGHT:
		vx = MARIO_WALKING_SPEED;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT: 
		vx = -MARIO_WALKING_SPEED;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		// TODO: need to check if Mario is *current* on a platform before allowing to jump again
		if (level == MARIO_LEVEL_SMALL)
		{
			vy = -MARIO_SMALL_JUMP_SPEED_Y;
		}
		else
			vy = -MARIO_BIG_JUMP_SPEED_Y;
		if (time_jump == 0)
		{
			time_jump = GetTickCount64();
		}
		break; 
	case MARIO_STATE_JUMP_MAX:
		// TODO: need to check if Mario is *current* on a platform before allowing to jump again
		
			vy = -MARIO_JUMP_SPEED_Y_MAX;
		break;
	case MARIO_STATE_IDLE: 
		if (a_stop == 0)
		{
			vx = 0;
		}
		isSpawnFireBall = false;
		break;
	case MARIO_STATE_DIE:
		vy = -MARIO_DIE_DEFLECT_SPEED;
		break;
	case MARIO_STATE_WALKING_RIGHT_FAST:
		nx = 1;
		a= MARIO_ACCELERATION;
		a_stop = MARIO_ACCELERATION_STOP;
		break;
	case MARIO_STATE_WALKING_LEFT_FAST:
		nx = -1;
		a = -MARIO_ACCELERATION;
		a_stop = -MARIO_ACCELERATION_STOP;
		break;
	case MARIO_STATE_SIT:
		vx = 0;
		this->isSit = true;
		break;
	case MARIO_STATE_STOP:
		time_stop = GetTickCount64();
		vx = 0;
		break;
	case MARIO_STATE_FLYLING:
		a_stop = 0;
		if (nx > 0)
		{
 			vx = MARIO_FLYING_SPEED_X;
		}
		else vx = -MARIO_FLYING_SPEED_X;
		vy = -MARIO_FLYLING_SPEED_Y;
		time_fly = GetTickCount64();
		break;
	case MARIO_STATE_LANDING:
		a_stop = 0;
		if (nx > 0)
		{
			vx = MARIO_LANDING_SPEED_X;
		}
		else vx = -MARIO_FLYING_SPEED_X;
		vy = MARIO_LANGDING_SPEED_Y;
		break;
	case MARIO_STATE_FIRE_BALL:
		isFireBall = true;
		break;
	case MARIO_STATE_ATTACK:
		isAttack = true;
		break;
	case MARIO_STATE_FIRE_BALL_DOUBLE:
		isFireBall = true;
		isSpawnFireBallDouble = true;
		vy = -MARIO_BIG_JUMP_SPEED_Y;
		time_doubleshot = GetTickCount64();
		break;
	case MARIO_STATE_STONE_KOOPAS:
		break;
	case MARIO_STATE_HOLD:
		pickingup = true;
		break;
	}
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y; 

	switch (level)
	{
	case MARIO_LEVEL_SMALL:
		right = x + MARIO_SMALL_BBOX_WIDTH;
		bottom = y + MARIO_SMALL_BBOX_HEIGHT;
		break;
	case MARIO_LEVEL_BIG:
		if (apperance == MARIO_NORMAL || apperance == MARIO_FIRE)
		{
			if (state == MARIO_STATE_SIT)
				top = y + SIT_BBOX_OFFSET;
			right = x + MARIO_BIG_BBOX_WIDTH;
			bottom = y + MARIO_BIG_BBOX_HEIGHT;
		}
		else
		{
			if (state == MARIO_STATE_SIT)
				top = y + SIT_BBOX_OFFSET;
			right = x + MARIO_FOX_BBOX_WIDTH;
			bottom = y + MARIO_FOX_BBOX_HEIGHT - MARIO_FOX_BBOX_OFFSET;
		}
		break;
	}
}

/*
	Reset Mario status to the beginning state of a scene
*/
void CMario::Reset()
{
	SetState(MARIO_STATE_IDLE);
	SetLevel(MARIO_LEVEL_BIG);
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
}
bool CMario::CheckFrameFireBall()
{
	if (state == MARIO_STATE_FIRE_BALL)
	{
		if (nx > 0)
		{
			int ani = MARIO_ANI_BIG_FIRE_BALL_RIGHT;
			if (animation_set->at(ani)->GetCurrentFrame() == 1)
			{
				return true;
			}
		}
		else
		{
			int ani = MARIO_ANI_BIG_FIRE_BALL_LEFT;
			if (animation_set->at(ani)->GetCurrentFrame() == 1)
			{
				return true;
			}
		}
	}
	else if(state == MARIO_STATE_FIRE_BALL_DOUBLE)
	{
		if (nx > 0)
		{
			int ani = MARIO_ANI_BIG_FIRE_BALL_DOUBLE_RIGHT;
			if (animation_set->at(ani)->GetCurrentFrame() == 1)
			{
				return true;
			}
		}
		else
		{
			int ani = MARIO_ANI_BIG_FIRE_BALL_DOUBLE_LEFT;
			if (animation_set->at(ani)->GetCurrentFrame() == 1)
			{
				return true;
			}
		}
	}
	else return false;
}

bool CMario::CheckFrameFireBallDouble()
{
	if (nx > 0)
	{
		int ani = MARIO_ANI_BIG_FIRE_BALL_DOUBLE_RIGHT;
		if (animation_set->at(ani)->GetCurrentFrame() == 1)
		{
			return true;
		}
	}
	else
	{
		int ani = MARIO_ANI_BIG_FIRE_BALL_DOUBLE_LEFT;
		if (animation_set->at(ani)->GetCurrentFrame() == 1)
		{
			return true;
		}
	}
	return false;
}

bool CMario::CheckLastFrameAttack()
{
	switch (apperance)
	{
	case MARIO_FOX:
	{
		if (state == MARIO_STATE_ATTACK)
		{
			if (nx > 0)
			{
				int ani = MARIO_ANI_BIG_FOX_ATTACK_IDLE_RIGHT;
				if (animation_set->at(ani)->GetCurrentFrame() >= animation_set->at(ani)->GetlastFrame())
				{
					animation_set->at(ani)->ResetFrame();
					return false;
				}
			}
			else
			{
				int ani = MARIO_ANI_BIG_FOX_ATTACK_IDLE_LEFT;
				if (animation_set->at(ani)->GetCurrentFrame() >= animation_set->at(ani)->GetlastFrame())
				{
					animation_set->at(ani)->ResetFrame();
					return false;
				}
			}
		}
	}
	case MARIO_FOX_FIRE:
	{
		if (state == MARIO_STATE_ATTACK)
		{
			if (nx > 0)
			{
				int ani = MARIO_ANI_BIG_FOX_FIRE_ATTACK_IDLE_RIGHT;
				if (animation_set->at(ani)->GetCurrentFrame() >= animation_set->at(ani)->GetlastFrame())
				{
					animation_set->at(ani)->ResetFrame();
					return false;
				}
			}
			else
			{
				int ani = MARIO_ANI_BIG_FOX_FIRE_ATTACK_IDLE_LEFT;
				if (animation_set->at(ani)->GetCurrentFrame() >= animation_set->at(ani)->GetlastFrame())
				{
					animation_set->at(ani)->ResetFrame();
					return false;
				}
			}
		}
		break;
	}
	case MARIO_FIRE:
	{
		if (state == MARIO_STATE_FIRE_BALL)
		{
			if (nx > 0)
			{
				int ani = MARIO_ANI_BIG_FIRE_BALL_RIGHT;
				if (animation_set->at(ani)->GetCurrentFrame() >= animation_set->at(ani)->GetlastFrame())
				{
					animation_set->at(ani)->ResetFrame();
					return false;
				}
			}
			else
			{
				int ani = MARIO_ANI_BIG_FIRE_BALL_LEFT;
				if (animation_set->at(ani)->GetCurrentFrame() >= animation_set->at(ani)->GetlastFrame())
				{
					animation_set->at(ani)->ResetFrame();
					return false;
				}
			}
		}
		if (state == MARIO_STATE_FIRE_BALL_DOUBLE)
		{
			if (nx > 0)
			{
				int ani = MARIO_ANI_BIG_FIRE_BALL_DOUBLE_RIGHT;
				if (animation_set->at(ani)->GetCurrentFrame() >= animation_set->at(ani)->GetlastFrame())
				{
					animation_set->at(ani)->ResetFrame();
					return false;
				}
			}
			else
			{
				int ani = MARIO_ANI_BIG_FIRE_BALL_DOUBLE_LEFT;
				if (animation_set->at(ani)->GetCurrentFrame() >= animation_set->at(ani)->GetlastFrame())
				{
					animation_set->at(ani)->ResetFrame();
					return false;
				}
			}
		}
	}
	default:
		break;
	}
	return true;
}


void CMario::Render()
{
	int ani = -1;
	if (state == MARIO_STATE_DIE)
	{
		ani = MARIO_ANI_DIE;
	}
	else
	{
		if (apperance == MARIO_NORMAL)
		{
			if (level == MARIO_LEVEL_BIG)
			{
				switch (state)
				{
				case MARIO_STATE_IDLE:
					if (nx > 0) ani = MARIO_ANI_BIG_IDLE_RIGHT;
					else ani = MARIO_ANI_BIG_IDLE_LEFT;
					break;
				case MARIO_STATE_WALKING_RIGHT:
					ani = MARIO_ANI_BIG_WALKING_RIGHT;
					break;
				case MARIO_STATE_WALKING_RIGHT_FAST:
					ani = MARIO_ANI_BIG_WALKING_FAST_RIGHT;
					break;
				case MARIO_STATE_WALKING_LEFT:
					ani = MARIO_ANI_BIG_WALKING_LEFT;
					break;
				case MARIO_STATE_WALKING_LEFT_FAST:
					ani = MARIO_ANI_BIG_WALKING_FAST_LEFT;
					break;
				case MARIO_STATE_JUMP:
				case MARIO_STATE_JUMP_MAX:
					if (nx > 0)
						ani = MARIO_ANI_BIG_JUMP_IDLE_RIGHT;
					else
						ani = MARIO_ANI_BIG_JUMP_IDLE_LEFT;
					break;
				case MARIO_STATE_SIT:
					if (nx > 0) ani = MARIO_ANI_BIG_SIT_RIGHT;
					else ani = MARIO_ANI_BIG_SIT_LEFT;
					break;
				default:
					if (nx > 0) ani = MARIO_ANI_BIG_IDLE_RIGHT;
					else ani = MARIO_ANI_BIG_IDLE_LEFT;
					break;
				case MARIO_STATE_STOP:
					if (nx < 0)
						ani = MARIO_ANI_BIG_STOP_IDLE_RIGHT;
					else
						ani = MARIO_ANI_BIG_STOP_IDLE_LEFT;
					break;
				case MARIO_STATE_FLY:
					if (nx > 0)
						ani = MARIO_ANI_BIG_FLY_IDLE_RIGHT;
					else
						ani = MARIO_ANI_BIG_FLY_IDLE_LEFT;
					break;
				case MARIO_STATE_HOLD:
					if (nx > 0)
						ani = MARIO_ANI_BIG_HOLD_RIGHT;
					else
						ani = MARIO_ANI_BIG_HOLD_LEFT;
					break;
				case MARIO_STATE_STONE_KOOPAS:
					if (nx > 0)
						ani = MARIO_ANI_BIG_STONE_KOOPAS_RIGHT;
					else
						ani = MARIO_ANI_BIG_STONE_KOOPAS_LEFT;
					break;
				}

			}
			else if (level == MARIO_LEVEL_SMALL)
			{
				switch (state)
				{
				case MARIO_STATE_IDLE:
					if (nx > 0) ani = MARIO_ANI_SMALL_IDLE_RIGHT;
					else ani = MARIO_ANI_SMALL_IDLE_LEFT;
					break;
				case MARIO_STATE_WALKING_RIGHT:
					ani = MARIO_ANI_SMALL_WALKING_RIGHT;
					break;
				case MARIO_STATE_WALKING_RIGHT_FAST:
					ani = MARIO_ANI_SMALL_WALKING_FAST_RIGHT;
					break;
				case MARIO_STATE_WALKING_LEFT:
					ani = MARIO_ANI_SMALL_WALKING_LEFT;
					break;
				case MARIO_STATE_WALKING_LEFT_FAST:
					ani = MARIO_ANI_SMALL_WALKING_FAST_LEFT;
					break;
				case MARIO_STATE_JUMP:
				case MARIO_STATE_JUMP_MAX:
					if (nx > 0)
						ani = MARIO_ANI_SMALL_JUMP_IDLE_RIGHT;
					else
						ani = MARIO_ANI_SMALL_JUMP_IDLE_LEFT;
					break;

				default:
					if (nx > 0) ani = MARIO_ANI_SMALL_IDLE_RIGHT;
					else ani = MARIO_ANI_SMALL_IDLE_LEFT;
					break;
				case MARIO_STATE_STOP:
					if (nx < 0)
						ani = MARIO_ANI_SMALL_STOP_IDLE_RIGHT;
					else
						ani = MARIO_ANI_SMALL_STOP_IDLE_LEFT;
					break;
				case MARIO_STATE_FLY:
					if (nx > 0)
						ani = MARIO_ANI_SMALL_FLY_IDLE_RIGHT;
					else
						ani = MARIO_ANI_SMALL_FLY_IDLE_LEFT;
					break;
				case MARIO_STATE_HOLD:
					if (nx > 0)
						ani = MARIO_ANI_SMALL_HOLD_RIGHT;
					else
						ani = MARIO_ANI_SMALL_HOLD_LEFT;
					break;
				case MARIO_STATE_STONE_KOOPAS:
					if (nx > 0)
						ani = MARIO_ANI_SMALL_STONE_KOOPAS_RIGHT;
					else
						ani = MARIO_ANI_SMALL_STONE_KOOPAS_LEFT;
					break;
				}
			}
		}
		else if (apperance == MARIO_FOX)
		{
			if (level == MARIO_LEVEL_BIG)
			{
				switch (state)
				{
				case MARIO_STATE_IDLE:
					if (nx > 0) ani = MARIO_ANI_BIG_FOX_IDLE_RIGHT;
					else ani = MARIO_ANI_BIG_FOX_IDLE_LEFT;
					break;
				case MARIO_STATE_WALKING_RIGHT:
					ani = MARIO_ANI_BIG_FOX_WALKING_RIGHT;
					break;
				case MARIO_STATE_WALKING_RIGHT_FAST:
					ani = MARIO_ANI_BIG_FOX_WALKING_FAST_RIGHT;
					break;
				case MARIO_STATE_WALKING_LEFT:
					ani = MARIO_ANI_BIG_FOX_WALKING_LEFT;
					break;
				case MARIO_STATE_WALKING_LEFT_FAST:
					ani = MARIO_ANI_BIG_FOX_WALKING_FAST_LEFT;
					break;
				case MARIO_STATE_JUMP:
				case MARIO_STATE_JUMP_MAX:
					if (nx > 0)
						ani = MARIO_ANI_BIG_FOX_JUMP_IDLE_RIGHT;
					else
						ani = MARIO_ANI_BIG_FOX_JUMP_IDLE_LEFT;
					break;
				case MARIO_STATE_SIT:
					if (nx > 0)
					{
						ani = MARIO_ANI_BIG_FOX_SIT_RIGHT;
					}
					else
					{
						ani = MARIO_ANI_BIG_FOX_SIT_LEFT;
					}
					break;
				default:
					if (nx > 0) ani = MARIO_ANI_BIG_FOX_IDLE_RIGHT;
					else ani = MARIO_ANI_BIG_FOX_IDLE_LEFT;
					break;
				case MARIO_STATE_STOP:
					if (nx < 0)
						ani = MARIO_ANI_BIG_FOX_STOP_IDLE_RIGHT;
					else
						ani = MARIO_ANI_BIG_FOX_STOP_IDLE_LEFT;
					break;
				case MARIO_STATE_FLY:
					if (nx > 0)
						ani = MARIO_ANI_BIG_FOX_FLY_IDLE_RIGHT;
					else
						ani = MARIO_ANI_BIG_FOX_FLY_IDLE_LEFT;
					break;
				case MARIO_STATE_ATTACK:
					if (nx > 0)
					{
						ani = MARIO_ANI_BIG_FOX_ATTACK_IDLE_RIGHT;
					}
					else
					{
						ani = MARIO_ANI_BIG_FOX_ATTACK_IDLE_LEFT;
					}
					break;
				case MARIO_STATE_FLYLING:
					if (nx > 0)
						ani = MARIO_ANI_BIG_FOX_FLYLING_IDLE_RIGHT;
					else
						ani = MARIO_ANI_BIG_FOX_FLYLING_IDLE_LEFT;
					break;
				case MARIO_STATE_LANDING:
					if (nx > 0)
						ani = MARIO_ANI_BIG_FOX_FLYLING_IDLE_RIGHT;
					else
						ani = MARIO_ANI_BIG_FOX_FLYLING_IDLE_LEFT;
					break;
				case MARIO_STATE_HOLD:
					if (nx > 0)
						ani = MARIO_ANI_BIG_FOX_HOLD_RIGHT;
					else
						ani = MARIO_ANI_BIG_FOX_HOLD_LEFT;
					break;
				case MARIO_STATE_STONE_KOOPAS:
					if (nx > 0)
						ani = MARIO_ANI_BIG_FOX_STONE_KOOPAS_RIGHT;
					else
						ani = MARIO_ANI_BIG_FOX_STONE_KOOPAS_LEFT;
					break;
				}
			}

		}
		else if (apperance == MARIO_FIRE)
		{
			if (level == MARIO_LEVEL_BIG)
			{
				switch (state)
				{
				case MARIO_STATE_IDLE:
					if (nx > 0) ani = MARIO_ANI_BIG_FIRE_IDLE_RIGHT;
					else ani = MARIO_ANI_BIG_FIRE_IDLE_LEFT;
					break;
				case MARIO_STATE_WALKING_RIGHT:
					ani = MARIO_ANI_BIG_FIRE_WALKING_RIGHT;
					break;
				case MARIO_STATE_WALKING_RIGHT_FAST:
					ani = MARIO_ANI_BIG_FIRE_WALKING_FAST_RIGHT;
					break;
				case MARIO_STATE_WALKING_LEFT:
					ani = MARIO_ANI_BIG_FIRE_WALKING_LEFT;
					break;
				case MARIO_STATE_WALKING_LEFT_FAST:
					ani = MARIO_ANI_BIG_FIRE_WALKING_FAST_LEFT;
					break;
				case MARIO_STATE_JUMP:
				case MARIO_STATE_JUMP_MAX:
					if (nx > 0)
						ani = MARIO_ANI_BIG_FIRE_JUMP_IDLE_RIGHT;
					else
						ani = MARIO_ANI_BIG_FIRE_JUMP_IDLE_LEFT;
					break;
				case MARIO_STATE_SIT:
					if (nx > 0)
					{
						ani = MARIO_ANI_BIG_FIRE_SIT_RIGHT;
					}
					else
					{
						ani = MARIO_ANI_BIG_FIRE_SIT_LEFT;
					}
					break;
				default:
					if (nx > 0) ani = MARIO_ANI_BIG_FIRE_IDLE_RIGHT;
					else ani = MARIO_ANI_BIG_FIRE_IDLE_LEFT;
					break;
				case MARIO_STATE_STOP:
					if (nx < 0)
						ani = MARIO_ANI_BIG_FIRE_STOP_IDLE_RIGHT;
					else
						ani = MARIO_ANI_BIG_FIRE_STOP_IDLE_LEFT;
					break;
				case MARIO_STATE_FLY:
					if (nx > 0)
						ani = MARIO_ANI_BIG_FIRE_FLY_IDLE_RIGHT;
					else
						ani = MARIO_ANI_BIG_FIRE_FLY_IDLE_LEFT;
					break;
				case MARIO_STATE_HOLD:
					if (nx > 0)
						ani = MARIO_ANI_BIG_FIRE_HOLD_RIGHT;
					else
						ani = MARIO_ANI_BIG_FIRE_HOLD_LEFT;
					break;
				case MARIO_STATE_FIRE_BALL:
					if (nx > 0)
						ani = MARIO_ANI_BIG_FIRE_BALL_RIGHT;
					else
						ani = MARIO_ANI_BIG_FIRE_BALL_LEFT;
					break;
				case MARIO_STATE_FIRE_BALL_DOUBLE:
					if (nx > 0)
						ani = MARIO_ANI_BIG_FIRE_BALL_DOUBLE_RIGHT;
					else
						ani = MARIO_ANI_BIG_FIRE_BALL_DOUBLE_LEFT;
					break;
				case MARIO_STATE_STONE_KOOPAS:
					if (nx > 0)
						ani = MARIO_ANI_BIG_FIRE_STONE_KOOPAS_RIGHT;
					else
						ani = MARIO_ANI_BIG_FIRE_STONE_KOOPAS_LEFT;
					break;
				}
			}
		}
		else if (apperance == MARIO_FOX_FIRE)
		{
			if (level == MARIO_LEVEL_BIG)
			{
				switch (state)
				{
				case MARIO_STATE_IDLE:
					if (nx > 0) ani = MARIO_ANI_BIG_FOX_FIRE_IDLE_RIGHT;
					else ani = MARIO_ANI_BIG_FOX_FIRE_IDLE_LEFT;
					break;
				case MARIO_STATE_WALKING_RIGHT:
					ani = MARIO_ANI_BIG_FOX_FIRE_WALKING_RIGHT;
					break;
				case MARIO_STATE_WALKING_RIGHT_FAST:
					ani = MARIO_ANI_BIG_FOX_FIRE_WALKING_FAST_RIGHT;
					break;
				case MARIO_STATE_WALKING_LEFT:
					ani = MARIO_ANI_BIG_FOX_FIRE_WALKING_LEFT;
					break;
				case MARIO_STATE_WALKING_LEFT_FAST:
					ani = MARIO_ANI_BIG_FOX_FIRE_WALKING_FAST_LEFT;
					break;
				case MARIO_STATE_JUMP:
				case MARIO_STATE_JUMP_MAX:
					if (nx > 0)
						ani = MARIO_ANI_BIG_FOX_FIRE_JUMP_IDLE_RIGHT;
					else
						ani = MARIO_ANI_BIG_FOX_FIRE_JUMP_IDLE_LEFT;
					break;
				case MARIO_STATE_SIT:
					if (nx > 0)
					{
						ani = MARIO_ANI_BIG_FOX_FIRE_SIT_RIGHT;
					}
					else
					{
						ani = MARIO_ANI_BIG_FOX_FIRE_SIT_LEFT;
					}
					break;
				default:
					if (nx > 0) ani = MARIO_ANI_BIG_FOX_FIRE_IDLE_RIGHT;
					else ani = MARIO_ANI_BIG_FOX_FIRE_IDLE_LEFT;
					break;
				case MARIO_STATE_STOP:
					if (nx < 0)
						ani = MARIO_ANI_BIG_FOX_FIRE_STOP_IDLE_RIGHT;
					else
						ani = MARIO_ANI_BIG_FOX_FIRE_STOP_IDLE_LEFT;
					break;
				case MARIO_STATE_FLY:
					if (nx > 0)
						ani = MARIO_ANI_BIG_FOX_FIRE_FLY_IDLE_RIGHT;
					else
						ani = MARIO_ANI_BIG_FOX_FIRE_FLY_IDLE_LEFT;
					break;
				case MARIO_STATE_ATTACK:
					if (nx > 0)
					{
						ani = MARIO_ANI_BIG_FOX_FIRE_ATTACK_IDLE_RIGHT;
					}
					else
					{
						ani = MARIO_ANI_BIG_FOX_FIRE_ATTACK_IDLE_LEFT;
					}
					break;
				case MARIO_STATE_FLYLING:
					if (nx > 0)
						ani = MARIO_ANI_BIG_FOX_FIRE_FLYLING_IDLE_RIGHT;
					else
						ani = MARIO_ANI_BIG_FOX_FIRE_FLYLING_IDLE_LEFT;
					break;
				case MARIO_STATE_LANDING:
					if (nx > 0)
						ani = MARIO_ANI_BIG_FOX_FIRE_FLYLING_IDLE_RIGHT;
					else
						ani = MARIO_ANI_BIG_FOX_FIRE_FLYLING_IDLE_LEFT;
					break;
				case MARIO_STATE_HOLD:
					if (nx > 0)
						ani = MARIO_ANI_BIG_FOX_FIRE_HOLD_RIGHT;
					else
						ani = MARIO_ANI_BIG_FOX_FIRE_HOLD_LEFT;
					break;
				case MARIO_STATE_STONE_KOOPAS:
					if (nx > 0)
						ani = MARIO_ANI_BIG_FOX_FIRE_STONE_KOOPAS_RIGHT;
					else
						ani = MARIO_ANI_BIG_FOX_FIRE_STONE_KOOPAS_LEFT;
					break;
				}
			}
		}
	}
	int alpha = 255;
	if (untouchable) alpha = 220;

	animation_set->at(ani)->Render(x, y, alpha);

	RenderBoundingBox();
}