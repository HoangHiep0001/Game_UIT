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
#include "Mushrooms.h"
#include "ItemLeaves.h"
#include "ItemSign.h"
#include "ItemCoin.h"
#include "Trigger_ChangeCamera.h"
#include "FireBallCacTus.h"
#include "CCheckStop.h"
#include "Trigger.h"
#include "CPortalintro.h"
#include "CTailPoint.h"


CMario::CMario(int intro, float x, float y) : CGameObject()
{
	this->intro = intro;
	if (intro == 0)
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
		this->life = 1;
		this->score = 0;
		this->coin_number = 0;
	}
	else
	{
		apperance = MARIO_NORMAL;
		level = MARIO_LEVEL_SMALL;
		untouchable = 0;
		SetState(MARIO_STATE_START);
		a = 0;
		a_stop = 0;
		time_stop = 0;
		time_fly = 0;
		start_x = x;
		start_y = y;
		this->x = x;
		this->y = y;
		this->life = 1;
		this->score = 0;
		this->coin_number = 0;
	}
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
	if (GetIntro()==0)
	{
		if (state != MARIO_STATE_FLYLING && state != MARIO_STATE_UP&& state!= MARIO_STATE_DOWN)
		{
			vy += MARIO_GRAVITY * dt;
		}
	}
	
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (GetTickCount64() - isP_time > 2000)
	{
		isP_time = 0;
		isP = false;
	}

	// turn off collision when die 
	if (state != MARIO_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	//kiem tra tan cong xong chua
	if (state == MARIO_STATE_ATTACK)
	{
		isAttack = CheckLastFrameAttack();
		if (!isAttack)
		{
			tail->GettailLast()->Destroy();
			tail->GettailHead()->Destroy();
			tail->Destroy();
			isSpawnTail = false;
		}
	}
	if (isAttack == true && state != MARIO_STATE_ATTACK)
	{
		isAttack = false;
		tail->GettailLast()->Destroy();
		tail->GettailHead()->Destroy();
		tail->Destroy();
		isSpawnTail = false;
	}

	if (state == MARIO_STATE_FIRE_BALL)
	{
		isFireBall = CheckFrameFireBall();
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
			if (this == NULL)
				return;

			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CGoomba*>(e->obj)) // if e->obj is Goomba 
			{
				if (untouchable == 0)
				{
					CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
					if (e->ny < 0)
					{
						if (goomba->state == GOOMBA_STATE_WALKING)
						{
							if (goomba->GetApperance() == GOOMBA_RED)
							{
								this->score += xcore*goomba->GetScore();
								//xcore *= 2;
								goomba->SetState(GOOMBA_STATE_DIE);

							}
							if (goomba->GetApperance() == GOOMBA_THERE)
							{
								this->score += goomba->GetScore();
								goomba->SetState(GOOMBA_STATE_DIE);

							}
							vy = -MARIO_JUMP_DEFLECT_SPEED;
						}
						else if ((goomba->state == GOOMBA_STATE_WALKING_WING) || (goomba->state == GOOMBA_STATE_FLYLING))
						{
							this->score += goomba->GetScore();
							goomba->SetState(GOOMBA_STATE_WALKING);
							goomba->y += GOOMBA_BBOX_Y;
							vy = -MARIO_JUMP_DEFLECT_SPEED;
						}
					}
					if (e->nx != 0)
					{
						if (goomba->GetState() != GOOMBA_STATE_DIE)
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
							{
								this->score += goomba->GetScore();
								SetState(MARIO_STATE_DIE);
							}
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
			else if (dynamic_cast<CKoopas*>(e->obj))
			{
				if (untouchable == 0)
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
						if (koopas->GetState() == KOOPAS_STATE_TORTOISESHELL_UP)
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
					}
					else if (ny > 0)
					{
						if ((koopas->GetState() != KOOPAS_STATE_DIE_UP) || (koopas->GetState() != KOOPAS_STATE_DIE_DOWN) /*&& (koopas->GetState() != KOOPAS_STATE_LIVING_UP) && (koopas->GetState() != KOOPAS_STATE_LIVING_DOWN)*/)
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
					if (e->nx != 0)
					{
						if (state == MARIO_STATE_WALKING_LEFT || state == MARIO_STATE_WALKING_RIGHT)
						{
							if (koopas->state == (KOOPAS_STATE_LIVING_UP))
							{
								SetState(MARIO_STATE_STONE_KOOPAS);
								koopas->nx = -nx;
								koopas->SetState(KOOPAS_STATE_TORTOISESHELL_UP);
							}
							else if (koopas->state == (KOOPAS_STATE_LIVING_DOWN))
							{
								SetState(MARIO_STATE_STONE_KOOPAS);
								koopas->nx = -nx;
								koopas->SetState(KOOPAS_STATE_TORTOISESHELL_DOWN);
							}
							else if (koopas->GetState() == KOOPAS_STATE_TORTOISESHELL_UP || koopas->GetState() ==KOOPAS_STATE_TORTOISESHELL_DOWN|| koopas->GetState()==KOOPAS_STATE_WALKING  ||koopas->GetState() == KOOPAS_STATE_FLYLING )
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
						else if (state == MARIO_STATE_HOLD)
						{
							if (koopas->state == (KOOPAS_STATE_LIVING_UP) || koopas->state == (KOOPAS_STATE_LIVING_DOWN))
							{
								koopas->SetIsPick(true);
							}
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
			else if (dynamic_cast<CPortal*>(e->obj))
			{
				CPortal* p = dynamic_cast<CPortal*>(e->obj);
				CGame::GetInstance()->GetProperties()->SetMarioPosition(p->GetMarioX(), p->GetMarioY());
				CGame::GetInstance()->SwitchScene(p->GetSceneId());
				return;
			}
			else if (dynamic_cast<CPortalintro*>(e->obj))
			{
				CPortalintro* p = dynamic_cast<CPortalintro*>(e->obj);
				this->portal = p;
				this->isInPortal = true;
				x += dx;
				y += dy;
			}
			else if (dynamic_cast<Trigger_ChangeCamera*>(e->obj))
			{
				Trigger_ChangeCamera* trigger = dynamic_cast<Trigger_ChangeCamera*>(e->obj);
				CPlayScene* pc = dynamic_cast<CPlayScene*>(scene);
				pc->SetMapCamera(pc->GetListMapCamera().at(trigger->getCameraMapID()));
				this->SetPosition(trigger->getMarioX(), trigger->getMarioY());
				pc->SetCamera(pc->GetListCamera().at(trigger->getCameraMapID()));
				SetisDownPipe(false);
				SetisUpPipe(false);
				SetState(MARIO_STATE_IDLE);
			}
			else if (dynamic_cast<Ground*>(e->obj))
			{
				if (e->ny < 0)
				{
					if (state == MARIO_STATE_FIRE_BALL_DOUBLE)
					{
						state = MARIO_STATE_IDLE;
						isSpawnShot = false;
					}
					else if (state == MARIO_STATE_LANDING)
					{	
						SetState(MARIO_STATE_IDLE);
					}
					else if (state == MARIO_STATE_DOWN && dynamic_cast<Ground*>(e->obj)->GetGroundState() == 0)
					{
						x += dx;
						y += dy;
					}
					vy = 0;
					time_jump = 0;
					is_colii_top = false; 
				}
				else if (e->ny > 0)
				{
					if (dynamic_cast<Ground*>(e->obj)->GetGroundState() == 1)
					{
						y += dy;
					}
					if (state == MARIO_STATE_UP && dynamic_cast<Ground*>(e->obj)->GetGroundState() == 0)
					{
						x += dx;
						y += dy;
					}
				}
				else 
				{
					vy = 0;
				}
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
				
			}
			else if (dynamic_cast<CBrick*>(e->obj))
			{
			CBrick* brick = dynamic_cast<CBrick*>(e->obj);
				if (e->ny < 0)
				{
					vy = 0;
					time_jump = 0;
					is_colii_top = false;
				}
				else if (e->ny > 0)
				{ 
					if (brick->GetItemState()!=0)
					{
						if (brick->GetState()==BRICK_STATE_BRICK)
						{
							if (brick->GetItemCount() >= 0)
							{
								brick->SetState(BRICK_STATE_EMPTY);
							}
						}	
					}
					else
					{
						if (level > MARIO_LEVEL_SMALL)
						{
							if (state == MARIO_STATE_JUMP)
							{
								brick->Destroy();
								this->score = brick->GetScore();
							}
						}
					}
						
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
					this->vy = 0;
					time_jump = 0;
					is_colii_top = false;
				}
				if (e->ny > 0)
				{	
 					this->vy = 0;
					is_colii_top = true;
					question->SetIsUp(true);
					if (question->GetState() == MARK_STATE_QUESTION || question->GetState() == MARK_STATE_N_EMPTY)
					{
						question->SetItemCount(question->GetItemCount() - 1);
						if (question->GetItemCount() == 0)
						{
							question->SetState(MARK_STATE_EMPTY);
						}
						else
						{
							question->SetState(MARK_STATE_N_EMPTY);
						}
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
			CPlayScene* pc = dynamic_cast<CPlayScene*>(scene);
			CCoin* coin = dynamic_cast<CCoin*>(e->obj);
				if (e->ny != 0 || e->nx != 0)
				{
					coin->Destroy();
					x += dx;
					y += dy;
					this->score += coin->GetScore();
					this->coin_number += coin->GetCoin_number();
				}
			}
			else if (dynamic_cast<CItemCoin*>(e->obj))
			{
			CPlayScene* pc = dynamic_cast<CPlayScene*>(scene);
			CItemCoin* coin = dynamic_cast<CItemCoin*>(e->obj);
			if (e->ny != 0 || e->nx != 0)
			{
				coin->Destroy();
				x += dx;
				y += dy;
				this->score += coin->GetScore();
				this->coin_number += coin->GetCoin_number();
			}
			}
			else if (dynamic_cast<CMushrooms*>(e->obj))
			{
				CMushrooms* mushrooms = dynamic_cast<CMushrooms*>(e->obj);
				
				if (level == MARIO_LEVEL_SMALL&&mushrooms->GetApperance()!=MUSHROOMS_BULE)
				{	
					this->y-= MARIO_BIG_BBOX;
					level = MARIO_LEVEL_BIG;
					mushrooms->Destroy();
					this->score += mushrooms->GetScore();
				}
				else
				{
					this->life++;
					mushrooms->Destroy();
				}	
				if (e->nx != 0)
					x += dx;
				if (e->ny < 0)
 					y += dy;
            }
			else if(dynamic_cast<CLeaves*>(e->obj))
			{
				CLeaves* leaves = dynamic_cast<CLeaves*>(e->obj);
				if (level==MARIO_LEVEL_BIG)
				{
					this->y -= MARIO_FOX_BBOX;
					ChangeApperance(MARIO_FOX);
					leaves->Destroy();
					this->score += leaves->GetScore();
					if (e->nx != 0)
						x += dx;
					if (e->ny < 0)
						y += dy;
				}
			}
			else if (dynamic_cast<CItemSign*>(e->obj))
			{
				CItemSign* sign = dynamic_cast<CItemSign*>(e->obj);
				if (e->ny<0)
				{
					if (sign->state==ITEM_SIGN_STATE_P)
					{
						sign->SetState(ITEM_SIGN_STATE_SIGN);
						
					}
					vy = 0;
					time_jump = 0;
					isP = true;
					isP_time = GetTickCount64();
				}
				if (e->nx != 0)
				{
					vx = 0;
					a = 0;
				}
			}
			else if (dynamic_cast<CFireBallCacTus*>(e->obj))
			{
				if (untouchable == 0)
				{
					CFireBallCacTus* FireBall = dynamic_cast<CFireBallCacTus*>(e->obj);

					if (apperance == MARIO_NORMAL && level == MARIO_LEVEL_BIG)
					{
						level = MARIO_LEVEL_SMALL;
						StartUntouchable();
						FireBall->Destroy();
					}
					else if (apperance == MARIO_FOX && level == MARIO_LEVEL_BIG)
					{
						apperance = MARIO_NORMAL;
						level = MARIO_LEVEL_BIG;
						StartUntouchable();
						FireBall->Destroy();
					}
					else if (apperance == MARIO_FIRE && level == MARIO_LEVEL_BIG)
					{
						apperance = MARIO_NORMAL;
						level = MARIO_LEVEL_SMALL;
						StartUntouchable();
						FireBall->Destroy();
					}
					else if (level == MARIO_LEVEL_SMALL)
					{
						SetState(MARIO_STATE_DIE);
						FireBall->Destroy();
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
			else if (dynamic_cast<CCheckStop*>(e->obj))
			{
				CCheckStop* checkstop = dynamic_cast<CCheckStop*>(e->obj);
				if (checkstop->GetDirection() == CHECKSTOP_DIRECTION_RIGHT)
				{
					if (state==MARIO_STATE_WALKING_RIGHT && !checkstop->GetISEnable())
					{
						SetState(MARIO_STATE_START);
						checkstop->SetIsEnable(true);
					}
					else
					{
						checkstop->SetIsEnable(false);
						x += dx;
						y += dy;
					}
				}
				else if (checkstop->GetDirection() == CHECKSTOP_DIRECTION_LEFT)
				{
					if (state == MARIO_STATE_WALKING_LEFT && !checkstop->GetISEnable())
					{
						SetState(MARIO_STATE_START);
						checkstop->SetIsEnable(true);
					}
					else
					{
						checkstop->SetIsEnable(false);
						x += dx;
						y += dy;
					}
				}
				else if (checkstop->GetDirection() == CHECKSTOP_DIRECTION_UP)
				{
					if (state == MARIO_STATE_START_UP && !checkstop->GetISEnable())
					{
						SetState(MARIO_STATE_START);
						checkstop->SetIsEnable(true);
					}
					else
					{
						checkstop->SetIsEnable(false);
						x += dx;
						y += dy;
					}
				}
				else if (checkstop->GetDirection() == CHECKSTOP_DIRECTION_DOWN)
				{
					if (state == MARIO_STATE_START_DOWN && !checkstop->GetISEnable())
					{
						SetState(MARIO_STATE_START);
						checkstop->SetIsEnable(true);
					}
					else
					{
						checkstop->SetIsEnable(false);
						x += dx;
						y += dy;
					}
				}
				else
				{
					x += dx;
					y += dy;
				}
			}
			else if (dynamic_cast<Trigger*>(e->obj))
			{
				Trigger* trigger = dynamic_cast<Trigger*>(e->obj);
				if (trigger->GetTriggerState() == TRIGGER_DIRECTION_UP &&!isUpPipe)
				{
					this->isUpPipe = true;
					x += dx;
					y -= dy;
				}
				else if (trigger->GetTriggerState() == TRIGGER_DIRECTION_DOWN  )
				{
					this->isDownPipe = true;
					x += dx;
					y += dy;
				}
			}
		}
	}


	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	bool flagOnGround = false;
	//for (std::size_t i = 0; i < coObjects->size(); i++)
	//{
	//	LPGAMEOBJECT e = coObjects->at(i);
	//	if (dynamic_cast<Ground*>(e) && !flagOnGround)
	//	{
	//		Ground* f = dynamic_cast<Ground*> (e);

	//		float l, t, r, b, el, et, er, eb;
	//		this->GetBoundingBox(l, t, r, b);
	//		b = b + 15;
	//		f->GetBoundingBox(el, et, er, eb);
	//		if (CGameObject::AABB(l, t, r, b, el, et, er, eb))
	//		{
	//			flagOnGround = true;
	//		}
	//	}
	//}

	//if (!flagOnGround && this->state != MARIO_STATE_JUMP
	//	&& this->state != MARIO_STATE_FLYLING)
	//{
	//	this->state = MARIO_STATE_IDLE;
	//}
	if (level == MARIO_LEVEL_BIG)
	{
		if (apperance == MARIO_FOX||apperance== MARIO_FOX_FIRE)
		{
			if (state == MARIO_STATE_ATTACK && isSpawnTail == false && isAttack)
			{
			
				tail = new CTail(scene, this->nx);
				if (nx > 0)
				{
					CTailPoint* head = tail->GettailHead();
					head->SetPosition(x + 10 - TAIL_BBOX_WIDTH, y + 19);
					head->SetState(TAIL_HEAD);
					head->SetStartX(x + 10 - TAIL_BBOX_WIDTH);

					CTailPoint* last = tail->GettailLast();
					last->SetPosition(x + 10, y + 19);
					last->SetState(TAIL_LAST);

					CPlayScene* pc = dynamic_cast<CPlayScene*>(scene);
					pc->SpawnObject(head);
					pc->SpawnObject(last);
					pc->SpawnObject(tail);
					this->isSpawnTail = true;
				}
				else
				{
					CTailPoint* head = tail->GettailHead();
					head->SetPosition(x + 8 + TAIL_BBOX_WIDTH, y + 19);

					CTailPoint* last = tail->GettailLast();
					last->SetPosition(x+8, y + 19);

					CPlayScene* pc = dynamic_cast<CPlayScene*>(scene);
					pc->SpawnObject(head);
					pc->SpawnObject(last);
					pc->SpawnObject(tail);
					this->isSpawnTail = true;

				}
			}
		}
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
						this->CountFireball++;
					}
					else
					{
						fireball->SetPosition(x, y + FIRE_BALL);
						CPlayScene* pc = dynamic_cast<CPlayScene*>(scene);
						pc->SpawnObject(fireball);
						this->CountFireball++;
					}
					isSpawnFireBall = true;
				}
			}
			
			if (state == MARIO_STATE_FIRE_BALL_DOUBLE&& isSpawnShot == false&& CheckFrameFireBallDouble()==true)
			{
				CFireBall* fireball = new CFireBall(this->nx);
				if (nx > 0)
				{
					fireball->SetPosition(x + FIRE_BALL, y + FIRE_BALL);
					CPlayScene* pc = dynamic_cast<CPlayScene*>(scene);
					if (CountFireball < 2)
					{
						pc->SpawnObject(fireball);
						this->CountFireball++;
					}
				}
				else
				{
					fireball->SetPosition(x, y + FIRE_BALL);
					CPlayScene* pc = dynamic_cast<CPlayScene*>(scene);
					if (CountFireball < 2)
					{
						pc->SpawnObject(fireball);
						this->CountFireball++;
					}
				}
					isSpawnShot = true;
			}
			if (time_doubleshot > 0 && GetTickCount64() - time_doubleshot > TIME_FIRE_BALL)
			{	
				CFireBall* fireball = new CFireBall(this->nx);
				if (nx > 0)
				{
					fireball->SetPosition(x + FIRE_BALL, y + FIRE_BALL);
					CPlayScene* pc = dynamic_cast<CPlayScene*>(scene);
					if (CountFireball < 2)
					{
						pc->SpawnObject(fireball);
						this->CountFireball++;
					}
				}
				else
				{
					fireball->SetPosition(x, y + FIRE_BALL);
					CPlayScene* pc = dynamic_cast<CPlayScene*>(scene);
					if (CountFireball < 2)
					{
						pc->SpawnObject(fireball);
						this->CountFireball++;
					}
				}
				time_doubleshot = 0;
				isFireBall = false;
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
	isIntro = false;
	if (level > MARIO_LEVEL_SMALL)
	{
		isStatemario = true;
		if (apperance == MARIO_FOX || apperance == MARIO_FOX_FIRE)
		{
			this->is_tail = true;
			this->isTail = true;
			switch (state)
			{
			case MARIO_STATE_WALKING_RIGHT:
				if (GetIntro() == 0)
				{
					vx = MARIO_WALKING_SPEED;
					nx = 1;
				}
				else
				{
					isIntro = true;
					vy = 0;
					vx = MARIO_WALKING_SPEED;
					nx = 1;
					isInPortal = false;
				}
				break;
			case MARIO_STATE_WALKING_LEFT:
				if (GetIntro() == 0)
				{
					vx = -MARIO_WALKING_SPEED;
					nx = -1;
				}
				else
				{
					isIntro = true;
					vy = 0;
					vx = -MARIO_WALKING_SPEED;
					nx = -1;
					isInPortal = false;
				}
				break;
			case MARIO_STATE_JUMP:
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
				vy = -MARIO_JUMP_SPEED_Y_MAX;
				break;
			case MARIO_STATE_IDLE:
				if (a_stop == 0)
				{
					vx = 0;
				}
				isSpawnFireBall = false;
				break;
			case MARIO_STATE_FALL_DOWN:
				if (a_stop == 0)
				{
					vx = 0;
				}
				isDownPipe = false;
				isSpawnFireBall = false;
				break;
			case MARIO_STATE_WALKING_RIGHT_FAST:
				nx = 1;
				a = MARIO_ACCELERATION;
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
			case MARIO_STATE_ATTACK:
				isAttack = true;
				vx = 0;
				break;
			case MARIO_STATE_FIRE_BALL:
				isFireBall = true;
				break;
			case MARIO_STATE_FIRE_BALL_DOUBLE:
				isFireBall = true;
				vy = -MARIO_FIRE_JUMP_SPEED_Y;
				time_doubleshot = GetTickCount64();
				break;
			case MARIO_STATE_STONE_KOOPAS:
				break;
			case MARIO_STATE_HOLD:
				pickingup = true;
				break;
			case MARIO_STATE_START:
				isIntro = true;
				vx = 0;
				vy = 0;
				break;
			case MARIO_STATE_START_UP:
				isInPortal = false;
				isIntro = true;
				vx = 0;
				vy = -MARIO_START;
				break;
			case MARIO_STATE_START_DOWN:
				isIntro = true;
				isInPortal = false;
				vx = 0;
				vy = MARIO_START;
				break;
			case MARIO_STATE_DOWN:
				vx = 0;
				vy = MARIO_START_DOWN;
				break;
			case MARIO_STATE_UP:
				vx = 0;
				vy = -MARIO_START_UP;
				break;
			}
		}
		else
		{
			isTail = false;
			switch (state)
			{
			case MARIO_STATE_WALKING_RIGHT:
				if (GetIntro() == 0)
				{
					vx = MARIO_WALKING_SPEED;
					nx = 1;
				}
				else
				{
					isIntro = true;
					vy = 0;
					vx = MARIO_WALKING_SPEED;
					nx = 1;
					isInPortal = false;
				}
				break;
			case MARIO_STATE_WALKING_LEFT:
				if (GetIntro() == 0)
				{
					vx = -MARIO_WALKING_SPEED;
					nx = -1;
				}
				else
				{
					isIntro = true;
					isInPortal = false;
					vy = 0;
					vx = -MARIO_WALKING_SPEED;
					nx = -1;
				}
				break;
			case MARIO_STATE_JUMP:
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
				vy = -MARIO_JUMP_SPEED_Y_MAX;
				break;
			case MARIO_STATE_IDLE:
				if (a_stop == 0)
				{
					vx = 0;
				}
				isSpawnFireBall = false;
				break;
			case MARIO_STATE_FALL_DOWN:
				if (a_stop == 0)
				{
					vx = 0;
				}
				isSpawnFireBall = false;
				break;
			case MARIO_STATE_WALKING_RIGHT_FAST:
				nx = 1;
				a = MARIO_ACCELERATION;
				a_stop = MARIO_ACCELERATION_STOP;
				break;
			case MARIO_STATE_WALKING_LEFT_FAST:
				nx = -1;
				a = -MARIO_ACCELERATION;
				a_stop = -MARIO_ACCELERATION_STOP;
				break;
			case MARIO_STATE_SIT:
				if (level == MARIO_LEVEL_BIG)
				{
					vx = 0;
					this->isSit = true;
				}
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
			case MARIO_STATE_ATTACK:
				isAttack = true;
				vx = 0;
				break;
			case MARIO_STATE_FIRE_BALL:
				isFireBall = true;
				break;
			case MARIO_STATE_FIRE_BALL_DOUBLE:
				isFireBall = true;
				vy = -MARIO_FIRE_JUMP_SPEED_Y;
				time_doubleshot = GetTickCount64();
				break;
			case MARIO_STATE_STONE_KOOPAS:
				break;
			case MARIO_STATE_HOLD:
				pickingup = true;
				break;
			case MARIO_STATE_START:
				isIntro = true;
				vx = 0;
				vy = 0;
				break;
			case MARIO_STATE_START_UP:
				isInPortal = false;
				isIntro = true;
				vx = 0;
				vy = -MARIO_START;
				break;
			case MARIO_STATE_START_DOWN:
				isInPortal = false;
				isIntro = true;
				vx = 0;
				vy = MARIO_START;
				break;
			case MARIO_STATE_DOWN:
				vx = 0;
				vy = MARIO_START_DOWN;
				break;
			case MARIO_STATE_UP:
				vx = 0;
				vy = -MARIO_START_UP;
				break;
			}
		}
	}
	else
	{
		isStatemario = false;
		isTail = false;
		switch (state)
		{
		case MARIO_STATE_WALKING_RIGHT:
			if (GetIntro() == 0)
			{
				vx = MARIO_WALKING_SPEED;
				nx = 1;
			}
			else
			{
				isIntro = true;
				isInPortal = false;
				vy = 0;
				vx = MARIO_WALKING_SPEED;
				nx = 1;
			}
			break;
		case MARIO_STATE_WALKING_LEFT:
			if (GetIntro() == 0)
			{
				vx = -MARIO_WALKING_SPEED;
				nx = -1;
			}
			else
			{
				isIntro = true;
				isInPortal = false;
				vy = 0;
				vx = -MARIO_WALKING_SPEED;
				nx = -1;
			}
			break;
		case MARIO_STATE_JUMP:
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
			vy = -MARIO_JUMP_SPEED_Y_MAX;
			break;
		case MARIO_STATE_IDLE:
			if (a_stop == 0)
			{
				vx = 0;
			}
			isSpawnFireBall = false;
			break;
		case MARIO_STATE_FALL_DOWN:
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
			a = MARIO_ACCELERATION;
			a_stop = MARIO_ACCELERATION_STOP;
			break;
		case MARIO_STATE_WALKING_LEFT_FAST:
			nx = -1;
			a = -MARIO_ACCELERATION;
			a_stop = -MARIO_ACCELERATION_STOP;
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
		case MARIO_STATE_ATTACK:
			isAttack = true;
			vx = 0;
			break;
		case MARIO_STATE_FIRE_BALL:
			isFireBall = true;
			break;
		case MARIO_STATE_FIRE_BALL_DOUBLE:
			isFireBall = true;
			vy = -MARIO_FIRE_JUMP_SPEED_Y;
			time_doubleshot = GetTickCount64();
			break;
		case MARIO_STATE_STONE_KOOPAS:
			break;
		case MARIO_STATE_HOLD:
			pickingup = true;
			break;
		case MARIO_STATE_START:
			isIntro = true;
			vx = 0;
			vy = 0;
			break;
		case MARIO_STATE_START_UP:
			isInPortal = false;
			isIntro = true;
			vx = 0;
			vy = -MARIO_START;
			break;
		case MARIO_STATE_START_DOWN:
			isInPortal = false;
			isIntro = true;
			vx = 0;
			vy = MARIO_START;
			break;
		case MARIO_STATE_DOWN:
			vx = 0;
			vy = MARIO_START_DOWN;
			break;
		case MARIO_STATE_UP:
			vx = 0;
			vy = -MARIO_START_UP;
			break;
		}
	}
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (GetIntro() == 0)
	{
		switch (level)
		{
		case MARIO_LEVEL_SMALL:
			left = x;
			top = y;
			right = x + MARIO_SMALL_BBOX_WIDTH;
			bottom = y + MARIO_SMALL_BBOX_HEIGHT;
			break;
		case MARIO_LEVEL_BIG:
			if (apperance == MARIO_NORMAL || apperance == MARIO_FIRE)
			{
				left = x;
				top = y;
				if (state == MARIO_STATE_SIT)
				{
					top = y + SIT_BBOX_OFFSET;
				}
				right = x + MARIO_BIG_BBOX_WIDTH;
				bottom = y + MARIO_BIG_BBOX_HEIGHT;
			}
			else if (apperance == MARIO_FOX || apperance == MARIO_FOX_FIRE)
			{
				if (nx > 0)
				{
					left = x + MARIO_FOX_BBOX_OFFSET_X;
					top = y;
					if (state == MARIO_STATE_SIT)
					{
						top = y + SIT_BBOX_OFFSET;
					}
					right = x + MARIO_FOX_BBOX_WIDTH;
					bottom = y + MARIO_FOX_BBOX_HEIGHT - MARIO_FOX_BBOX_OFFSET_Y;
				}
				else
				{
					left = x;
					top = y;
					if (state == MARIO_STATE_SIT)
					{
						top = y + SIT_BBOX_OFFSET;
					}
					right = x + MARIO_FOX_BBOX_WIDTH - MARIO_FOX_BBOX_OFFSET_X;
					bottom = y + MARIO_FOX_BBOX_HEIGHT - MARIO_FOX_BBOX_OFFSET_Y;

				}
			}
			break;
		}
	}
	else
	{
		left = x;
		top = y;
		right = x + MARIO_START_WIDTH;
		bottom = y + MARIO_START_HEIGHT;
	}
}

/*
	Reset Mario status to the beginning state of a scene
*/
void CMario::Reset()
{
	if (GetIntro()==0)
	{
		SetState(MARIO_STATE_IDLE);
		SetLevel(MARIO_LEVEL_BIG);
		SetPosition(start_x, start_y);
		SetSpeed(0, 0);

	}
	else
	{
		SetState(MARIO_STATE_START);
		SetLevel(MARIO_LEVEL_BIG);
		SetPosition(start_x, start_y);
		SetSpeed(0, 0);
	}
	
}
bool CMario::CheckFrameFireBall()
{
	if (nx > 0)
	{
		int ani = MARIO_ANI_BIG_FIRE_BALL_RIGHT;
		if (animation_set->at(ani)->GetCurrentFrame() == CHECK_FAME_FIRE)
		{
			return true;
		}
	}
	else
	{
		int ani = MARIO_ANI_BIG_FIRE_BALL_LEFT;
		if (animation_set->at(ani)->GetCurrentFrame() == CHECK_FAME_FIRE)
		{
			return true;
		}
	}
	return false;
}

bool CMario::CheckFrameFireBallDouble()
{
	if (nx > 0)
	{
		int ani = MARIO_ANI_BIG_FIRE_BALL_DOUBLE_RIGHT;
		if (animation_set->at(ani)->GetCurrentFrame() == CHECK_FAME_FIRE)
		{
			return true;
		}
	}
	else
	{
		int ani = MARIO_ANI_BIG_FIRE_BALL_DOUBLE_LEFT;
		if (animation_set->at(ani)->GetCurrentFrame() == CHECK_FAME_FIRE)
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
				case MARIO_STATE_FALL_DOWN:
				case MARIO_STATE_IDLE:
					if (nx > 0) ani = MARIO_ANI_BIG_IDLE_RIGHT;
					else ani = MARIO_ANI_BIG_IDLE_LEFT;
					break;
				case MARIO_STATE_WALKING_RIGHT:
					if (GetIntro() == 0)
					{
						ani = MARIO_ANI_BIG_WALKING_RIGHT;
					}
					else
					{
						ani = MARIO_ANI_BIG_START;
					}
					break;
				case MARIO_STATE_WALKING_RIGHT_FAST:
					ani = MARIO_ANI_BIG_WALKING_FAST_RIGHT;
					break;
				case MARIO_STATE_WALKING_LEFT:
					if (GetIntro() == 0)
					{
						ani = MARIO_ANI_BIG_WALKING_LEFT;
					}
					else
					{
						ani = MARIO_ANI_BIG_START;
					}
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
				case MARIO_STATE_START:
					ani = MARIO_ANI_BIG_START;
					break;
				case MARIO_STATE_START_UP:
					ani = MARIO_ANI_BIG_START_UP;
					break;
				case MARIO_STATE_START_DOWN:
					ani = MARIO_ANI_BIG_START_DOWN;
					break;
				case MARIO_STATE_DOWN:
					ani = MARIO_ANI_BIG_DOWN;
					break;
				case MARIO_STATE_UP:
					ani = MARIO_ANI_BIG_UP;
					break;
				}


			}
			else if (level == MARIO_LEVEL_SMALL)
			{
				switch (state)
				{
				case MARIO_STATE_FALL_DOWN:
				case MARIO_STATE_IDLE:
					if (nx > 0) ani = MARIO_ANI_SMALL_IDLE_RIGHT;
					else ani = MARIO_ANI_SMALL_IDLE_LEFT;
					break;
				case MARIO_STATE_WALKING_RIGHT:
					if (GetIntro() == 0)
					{
						ani = MARIO_ANI_SMALL_WALKING_RIGHT;
					}
					else
					{
						ani = MARIO_ANI_SMALL_START;
					}
					break;
				case MARIO_STATE_WALKING_RIGHT_FAST:
					ani = MARIO_ANI_SMALL_WALKING_FAST_RIGHT;
					break;
				case MARIO_STATE_WALKING_LEFT:
					if (GetIntro() == 0)
					{
						ani = MARIO_ANI_SMALL_WALKING_LEFT;
					}
					else
					{
						ani = MARIO_ANI_SMALL_START;
					}
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
				case MARIO_STATE_START:
					ani = MARIO_ANI_SMALL_START;
					break;
				case MARIO_STATE_START_UP:
					ani = MARIO_ANI_SMALL_START_UP;
					break;
				case MARIO_STATE_START_DOWN:
					ani = MARIO_ANI_SMALL_START_DOWN;
					break;
				case MARIO_STATE_DOWN:
					ani = MARIO_ANI_SMALL_DOWN;
					break;
				case MARIO_STATE_UP:
					ani = MARIO_ANI_SMALL_UP;
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
				case MARIO_STATE_FALL_DOWN:
				case MARIO_STATE_IDLE:
					if (nx > 0) ani = MARIO_ANI_BIG_FOX_IDLE_RIGHT;
					else ani = MARIO_ANI_BIG_FOX_IDLE_LEFT;
					break;
				case MARIO_STATE_WALKING_RIGHT:
					if (GetIntro() == 0)
					{
						ani = MARIO_ANI_BIG_FOX_WALKING_RIGHT;
					}
					else
					{
						ani = MARIO_ANI_BIG_FOX_START;
					}
					break;
				case MARIO_STATE_WALKING_RIGHT_FAST:
					ani = MARIO_ANI_BIG_FOX_WALKING_FAST_RIGHT;
					break;
				case MARIO_STATE_WALKING_LEFT:
					if (GetIntro() == 0)
					{
						ani = MARIO_ANI_BIG_FOX_WALKING_LEFT;
					}
					else
					{
						ani = MARIO_ANI_BIG_FOX_START;
					}
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
				case MARIO_STATE_START:
					ani = MARIO_ANI_BIG_FOX_START;
					break;
				case MARIO_STATE_START_UP:
					ani = MARIO_ANI_BIG_FOX_START_UP;
					break;
				case MARIO_STATE_START_DOWN:
					ani = MARIO_ANI_BIG_FOX_START_DOWN;
					break;
				case MARIO_STATE_DOWN:
					ani = MARIO_ANI_BIG_FOX_DOWN;
					break;
				case MARIO_STATE_UP:
					ani = MARIO_ANI_BIG_FOX_UP;
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
				case MARIO_STATE_FALL_DOWN:
				case MARIO_STATE_IDLE:
					if (nx > 0) ani = MARIO_ANI_BIG_FIRE_IDLE_RIGHT;
					else ani = MARIO_ANI_BIG_FIRE_IDLE_LEFT;
					break;
				case MARIO_STATE_WALKING_RIGHT:
					if (GetIntro() == 0)
					{
						ani = MARIO_ANI_BIG_FIRE_WALKING_RIGHT;
					}
					else
					{
						ani = MARIO_ANI_BIG_FIRE_START;
					}
					break;
				case MARIO_STATE_WALKING_RIGHT_FAST:
					ani = MARIO_ANI_BIG_FIRE_WALKING_FAST_RIGHT;
					break;
				case MARIO_STATE_WALKING_LEFT:
					if (GetIntro() == 0)
					{
					ani = MARIO_ANI_BIG_FIRE_WALKING_LEFT;
					}
					else
					{
						ani = MARIO_ANI_BIG_FIRE_START;
					}
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
				case MARIO_STATE_START:
					ani = MARIO_ANI_BIG_FIRE_START;
					break;
				case MARIO_STATE_START_UP:
					ani = MARIO_ANI_BIG_FIRE_START_UP;
					break;
				case MARIO_STATE_START_DOWN:
					ani = MARIO_ANI_BIG_FIRE_START_DOWN;
					break;
				case MARIO_STATE_DOWN:
					ani = MARIO_ANI_BIG_FIRE_DOWN;
					break;
				case MARIO_STATE_UP:
					ani = MARIO_ANI_BIG_FIRE_UP;
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
				case MARIO_STATE_FALL_DOWN:
				case MARIO_STATE_IDLE:
					if (nx > 0) ani = MARIO_ANI_BIG_FOX_FIRE_IDLE_RIGHT;
					else ani = MARIO_ANI_BIG_FOX_FIRE_IDLE_LEFT;
					break;
				case MARIO_STATE_WALKING_RIGHT:
					if (GetIntro() == 0)
					{
						ani = MARIO_ANI_BIG_FOX_FIRE_WALKING_RIGHT;
					}
					else
					{
						ani = MARIO_ANI_BIG_FOX_FIRE_START;
					}
					break;
				case MARIO_STATE_WALKING_RIGHT_FAST:
					ani = MARIO_ANI_BIG_FOX_FIRE_WALKING_FAST_RIGHT;
					break;
				case MARIO_STATE_WALKING_LEFT:
					if (GetIntro() == 0)
					{
					ani = MARIO_ANI_BIG_FOX_FIRE_WALKING_LEFT;
					}
					else
					{
						ani = MARIO_ANI_BIG_FOX_FIRE_START;
					}
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
				case MARIO_STATE_START:
					ani = MARIO_ANI_BIG_FOX_FIRE_START;
					break;
				case MARIO_STATE_START_UP:
					ani = MARIO_ANI_BIG_FOX_FIRE_START_UP;
					break;
				case MARIO_STATE_START_DOWN:
					ani = MARIO_ANI_BIG_FOX_FIRE_START_DOWN;
					break;
				case MARIO_STATE_DOWN:
					ani = MARIO_ANI_BIG_FOX_FIRE_DOWN;
					break;
				case MARIO_STATE_UP:
					ani = MARIO_ANI_BIG_FOX_FIRE_UP;
					break;
				}
			}
		}
	}
	int alpha = 255;
	if (untouchable) alpha = 125;

	animation_set->at(ani)->Render(x, y, alpha);

	RenderBoundingBox();
}