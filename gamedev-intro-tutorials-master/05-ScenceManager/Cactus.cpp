#include "Cactus.h"
#include "PlayScence.h"
#include "FireBallCacTus.h"

CCactus::CCactus(int appe,int stype,int sewer, float pipes)
{
	pipes_y = pipes;
	sewer_pipes = sewer;
	type = stype;
	apperance = appe;
	vy = -CACTUS_VY;
}
void CCactus::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case CACTUS_STATE_UP:
		break;
	case CACTUS_STATE_DOWN:
		break;
	case CACTUS_STATE_IDE_UP_SONG:
		time = GetTickCount64();
		vy = 0;
		break;
	case CACTUS_STATE_IDE_UP_SHUT:
		break;
	case CACTUS_STATE_FIRE_UP:
	case CACTUS_STATE_FIRE_DOWN:
		vy = 0;
		time = GetTickCount64();
		break;
	}
}
void CCactus::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	
		if (number==CACTUS_NUMBER_ONE)
		{
			right = x + CACTUS_BBOX_ONE_X;
			bottom = y + CACTUS_BBOX_ONE_Y;
		}
		else
		{
			right = x + CACTUS_BBOX_TWO_X;
			bottom = y + CACTUS_BBOX_TWO_Y;
		}
	if (isDestroy)
	{
		right = 0;
		bottom = 0;
	}
}

void CCactus::Update(DWORD dt, CScene* scene, vector<LPGAMEOBJECT>* coObjects)
{
	if (isDestroy)
	{
		return;
	}



	if (!CheckInCamera())
	{
		return;
	}
	CGameObject::Update(dt, scene, NULL);
	CPlayScene* pc = dynamic_cast<CPlayScene*>(scene);
	CMario* mario = pc->GetPlayer();

	if (y > pipes_y && abs(mario->x - x) < 30)
	{
		return;
	}

	if (mario->x<x)
	{
		nx = -1;
	}
	else
	{
		nx =1;
	}
	
	
	if (vy > 0 && y >= start_y)
	{
		vy = -CACTUS_VY;
	}

	if (GetType() == CACTUS_TYPE_WALK)
	{
		if (vy < 0)
		{
			if (mario->y < y)
			{
				SetState(CACTUS_STATE_UP);
			}
			else
			{
				SetState(CACTUS_STATE_DOWN);
			}
		}
		if (vy < 0 && start_y - y >= sewer_pipes)
		{
			if (mario->y < y)
			{
				SetState(CACTUS_STATE_FIRE_UP);
			}
			else
			{
				SetState(CACTUS_STATE_FIRE_DOWN);
			}
			if (GetState() == CACTUS_STATE_FIRE_DOWN || GetState() == CACTUS_STATE_FIRE_UP)
			{
				if (isSpawnFireBall == false)
				{
					if (abs(mario->x - x) > 30)
					{
						CFireBallCacTus* fireball = new CFireBallCacTus(this->nx);
						if (nx > 0)
						{
							fireball->SetPosition(x + FIREBALL_CACTUS_BALL, y + FIREBALL_CACTUS_BALL);
							CPlayScene* pc = dynamic_cast<CPlayScene*>(scene);
							pc->SpawnObject(fireball);
						}
						else
						{
							fireball->SetPosition(x, y + FIREBALL_CACTUS_BALL);
							CPlayScene* pc = dynamic_cast<CPlayScene*>(scene);
							pc->SpawnObject(fireball);
						}
						isSpawnFireBall = true;
					}
				}
			}

		}
		if (GetTickCount64() - time >= 1000 && time > 0)
		{
			if (mario->y < y)
			{
				SetState(CACTUS_STATE_UP);
			}
			else
			{
				SetState(CACTUS_STATE_DOWN);
			}
			vy = CACTUS_VY;
			time = 0;
			isSpawnFireBall = false;
		}
	}
	else
	{
		if (vy < 0 && start_y - y >= sewer_pipes)
		{
			SetState(CACTUS_STATE_IDE_UP_SONG);
		}
		if (GetTickCount64() - time >= 2000 && time > 0)
		{
			vy = CACTUS_VY;
			time = 0;
			SetState(CACTUS_STATE_IDE_UP_SHUT);
		}
	}
	x += dx;
	y += dy;
}

void CCactus::Render()
{
	if (isDestroy)
		return;
	int ani = -1;
	if (apperance == CACTUS_RED)
	{
		switch (state)
		{
		case CACTUS_STATE_IDE_UP_SONG:
		case CACTUS_STATE_IDE_UP_SHUT:
			break;
		case CACTUS_STATE_UP:
			if (nx>0)
			{
				ani = CACTUS_RED_ANI_UP_RIGHT;
			}
			else
			{
				ani = CACTUS_RED_ANI_UP_LEFT;
			}
			break;
		case CACTUS_STATE_DOWN:
			if (nx > 0)
			{
				ani = CACTUS_RED_ANI_DOWN_RIGHT;
			}
			else
			{
				ani = CACTUS_RED_ANI_DOWN_LEFT;
			}
			break;
		case CACTUS_STATE_FIRE_UP:
			if (nx > 0)
			{
				ani = CACTUS_RED_ANI_FIRE_UP_RIGHT;
			}
			else
			{
				ani = CACTUS_RED_ANI_FIRE_UP_LEFT;
			}
			break;
		case CACTUS_STATE_FIRE_DOWN:
			if (nx > 0)
			{
				ani = CACTUS_RED_ANI_FIRE_DOWN_RIGHT;
			}
			else
			{
				ani = CACTUS_RED_ANI_FIRE_DOWN_LEFT;
			}
			break;
		}
	}
	else if (apperance == CACTUS_BULE)
	{
		switch (state)
		{
		case CACTUS_STATE_IDE_UP_SONG:
			ani = CACTUS_BULE_IDE_UP_SONG;
			break;
		case CACTUS_STATE_IDE_UP_SHUT:
			ani = CACTUS_BULE_IDE_UP_SHUT;
			break;
		case CACTUS_STATE_UP:
			if (nx > 0)
			{
				ani = CACTUS_BULE_ANI_UP_RIGHT;
			}
			else
			{
				ani = CACTUS_BULE_ANI_UP_LEFT;
			}
			break;
		case CACTUS_STATE_DOWN:
			if (nx > 0)
			{
				ani = CACTUS_BULE_ANI_DOWN_RIGHT;
			}
			else
			{
				ani = CACTUS_BULE_ANI_DOWN_LEFT;
			}
			break;
		case CACTUS_STATE_FIRE_UP:
			if (nx > 0)
			{
				ani = CACTUS_BULE_ANI_FIRE_UP_RIGHT;
			}
			else
			{
				ani = CACTUS_BULE_ANI_FIRE_UP_LEFT;
			}
			break;
		case CACTUS_STATE_FIRE_DOWN:
			if (nx > 0)
			{
				ani = CACTUS_BULE_ANI_FIRE_DOWN_RIGHT;
			}
			else
			{
				ani = CACTUS_BULE_ANI_FIRE_DOWN_LEFT;
			}
			break;
		}
	}

	animation_set->at(ani)->Render(x, y);

	RenderBoundingBox();
}

