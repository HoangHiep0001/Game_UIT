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
	CGameObject::Update(dt, scene, coObjects);
	if (count == 0 && state == TAIL_HEAD)
	{
		if (nx > 0)
		{
			if (abs(x - start_x )>= CIRCLE_DIAMETER)
			{
				nx = -nx;
				vx = -vx;
				count++;
			}

		}
		else
		{
			if (abs(x - start_x) >= CIRCLE_DIAMETER)
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


			if (dynamic_cast<CKoopas*>(e->obj))
			{
				CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);
				if (e->nx != 0)
				{
					if (koopas->GetState() == KOOPAS_STATE_WALKING || koopas->GetState() == KOOPAS_STATE_FLYLING)
					{
						koopas->SetState(KOOPAS_STATE_LIVING_DOWN);
					}
				}
				if (e->ny != 0)
				{
					vy = 0;
				}
			}
			else if (dynamic_cast<CGoomba*>(e->obj))
			{
				CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
				if (e->nx != 0)
				{
					if (goomba->state == GOOMBA_STATE_WALKING)
					{
						goomba->SetState(GOOMBA_STATE_WALKING_DOWN);
					}
					else if (goomba->GetState() == GOOMBA_STATE_FLYLING)
					{
						SetState(GOOMBA_STATE_FLYLING_DOWN);
					}
					else if (goomba->GetState() == GOOMBA_STATE_WALKING_WING)
					{
						SetState(GOOMBA_STATE_WALKING_WING_DOWN);
					}
				}
			}
			else if (dynamic_cast<CBrick*>(e->obj))
			{
				CBrick* brick = dynamic_cast<CBrick*>(e->obj);
				if (brick->GetItemState() == 1)
				{
					if (brick->GetState() == BRICK_STATE_BRICK)
					{
						if (brick->GetItemCount() >= 0)
						{
							brick->SetState(BRICK_STATE_EMPTY);
						}
					}
				}
				else
				{
					brick->Destroy();
				}
			}
			else if (dynamic_cast<CQuestionMark*>(e->obj))
			{
				CQuestionMark* question = dynamic_cast<CQuestionMark*>(e->obj);
				if (e->nx != 0)
				{
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

void CTailPoint::Render()
{
	if (isDestroy)
		return;
	RenderBoundingBox();
}
