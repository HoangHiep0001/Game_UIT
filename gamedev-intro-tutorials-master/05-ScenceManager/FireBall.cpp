#include "FireBall.h"
#include "Goomba.h"
#include "Ground.h"
#include "Koopas.h"
#include "Brick.h"
#include "QuestionMark.h"
#include "PlayScence.h"


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
	if (isDestroy)
	{
		return;
	}
	left = x;
	top = y;
	right = x + FIREBALL_BBOX_WIDTH;
	bottom = y + FIREBALL_BBOX_HEIGHT;
}

void CFireBall::Update(DWORD dt, CScene* scene, vector<LPGAMEOBJECT>* coObjects)
{
	
	if (!isDestroy)
	{
		CGameObject::Update(dt,scene, coObjects);

		//
		// TO-DO: make sure FIREBALL can interact with the world and to each of them too!
		// 

		CPlayScene* pc = dynamic_cast<CPlayScene*>(scene);
		CMario* mario = pc->GetPlayer();
    if (!CheckInCamera())
	{
		mario->SetCountFireBall(mario->GetCountFireBall() - 1);
		Destroy();
	}
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
				if (dynamic_cast<CGoomba*>(e->obj)) // if e->obj is Goomba 
				{
					CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

					// jump on top >> kill Goomba and deflect a bit 
					if (e->ny < 0|| e->nx != 0)
					{
						if (goomba->GetState() != GOOMBA_STATE_DIE)
						{
							goomba->SetState(GOOMBA_STATE_DIE);
							goomba->Destroy();
							mario->SetCountFireBall(mario->GetCountFireBall()-1);
							Destroy();
						}
					}
				}
				else if (dynamic_cast<CKoopas*>(e->obj))
				{
					CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);
					if (e->ny < 0 || e->nx != 0)
					{
						if (koopas->GetState() != KOOPAS_STATE_DIE_UP)
						{
							koopas->SetState(KOOPAS_STATE_DIE_UP);

							koopas->Destroy();
							mario->SetCountFireBall(mario->GetCountFireBall() - 1);
							Destroy();
						}
					}
				}
				else if (dynamic_cast<Ground*>(e->obj))
				{
					if (e->ny < 0)
					{
						vy = -FIREBALL_Y;
						MaxY = dynamic_cast<Ground*>(e->obj)->y - FIRE_BALL_MAX_Y;
						first_time = false;
					}
					if (e->nx != 0)
					{
						mario->SetCountFireBall(mario->GetCountFireBall() - 1);
						Destroy();

					}
				}
				else if (dynamic_cast<CBrick*>(e->obj))
				{
					if (e->ny < 0)
					{
						vy = -FIREBALL_Y;
						MaxY = dynamic_cast<CBrick*>(e->obj)->y - FIRE_BALL_MAX_Y;
						first_time = false;
					}
					if (e->nx != 0)
					{
						mario->SetCountFireBall(mario->GetCountFireBall() - 1);
						Destroy();
					}
				}
				else if (dynamic_cast<CQuestionMark*>(e->obj))
				{
					if (e->ny < 0)
					{
						vy = -FIREBALL_Y;
						MaxY = dynamic_cast<CQuestionMark*>(e->obj)->y - FIRE_BALL_MAX_Y;
						first_time = false;
					}
					if (e->nx != 0)
					{
						mario->SetCountFireBall(mario->GetCountFireBall() - 1);
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

		animation_set->at(ani)->Render(x, y, 255);

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