#include "CTailPoint.h"
#include "Mario.h"
#include "PlayScence.h"

CTailPoint::CTailPoint(int dir)
{
	nx = dir;
}

void CTailPoint::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (isDestroy)
		return;
	left = x;
	top = y;
	right = x + TAIL_POINT_BBOX_WIDTH;
	bottom = y + TAIL_POINT_BBOX_HEIGHT;

	if (isDestroy)
	{
		right = 0;
		bottom = 0;
	}
}

void CTailPoint::SetState(int state)
{
	this->state = state;
	if (state == TAIL_HEAD)
	{
		if (nx > 0)
		{
			vx = TAIL_ROTATE_VX;
			vy = 0;
		}
		else
		{
			vx = -TAIL_ROTATE_VX;
			vy = 0;
		}
	
	}
}
void CTailPoint::Update(DWORD dt, CScene* scene, vector<LPGAMEOBJECT>* coObjects)
{
	if (this->isDestroy)
		return;
	
	if (count == 0 && state == TAIL_HEAD)
	{
		if (nx > 0)
		{
			if (x - start_x >= 34)
			{
				nx = -nx;
				vx = -vx;
				count++;
			}

		}
		else
		{
			if (start_x - x >= 34)
			{
				nx = -nx;
				vx = -vx;
				count++;
			}
		}
	}

	if (count == 1)
	{
		if (nx > 0)
		{
			if (x>=start_x)
			{
				this->Destroy();
			}
		}
		else
		{
			if ( x <= start_x)
			{
				this->Destroy();
			}
		}
	}

 	x += vx*dt;
	y += dy;                              

}

void CTailPoint::Render()
{
	if (isDestroy)
		return;
	RenderBoundingBox();
}
