#include "Cactus.h"

CCactus::CCactus(int appe)
{
	apperance = appe;
}
void CCactus::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case CACTUS_STATE_UP:
		vy = -CACTUS_VY;
		break;
	case CACTUS_STATE_DOWN:
		vy = CACTUS_VY;
		break;
	case CACTUS_STATE_IDE_UP_SHUT:
		vy = -CACTUS_VY;
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
	CGameObject::Update(dt, scene, NULL);

	if (vy > 0 && y >= start_y)
	{
		vy = -CACTUS_VY;
	}
	if (vy < 0 && start_y - y >= 48)
	{
		vy = CACTUS_VY;
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

