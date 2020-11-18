#include "Mushrooms.h"
#include "Ground.h"
#include "Brick.h"
#include "QuestionMark.h"
#include "PlayScence.h"

CMushrooms::CMushrooms(int app)
{

	apperance = app;
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(MUSHROOMS_ANI_SET);
	this->SetAnimationSet(ani_set);
	vx = 0;
}
void CMushrooms::Render()
{
	if (isDestroy)
		return;
	int ani = -1;
	if (apperance==MUSHROOMS_RED)
	{
		ani = MUSHROOMS_ANI_RED_WALK;
	}
	else if (apperance == MUSHROOMS_BULE)
	{
		ani = MUSHROOMS_ANI_BULE_WALK;
	}
	animation_set->at(ani)->Render(x, y);

	RenderBoundingBox();
}

void CMushrooms::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + MUSHROOMS_BBOX_X_Y;
	b=y+ MUSHROOMS_BBOX_X_Y;

}

void CMushrooms::Update(DWORD dt, CScene* scene, vector<LPGAMEOBJECT>* colliable_objects)
{
	if (isDestroy)
	{
		return;
	}
	if (!CheckInCamera())
	{
		return;
	}
	CGameObject::Update(dt, scene, colliable_objects);

	if (vx == 0)
	{
		CPlayScene* pc = dynamic_cast<CPlayScene*>(scene);
		CMario* mario = pc->GetPlayer();
		if (mario->nx > 0)
		{
			vx = MUSHROOMS_SPEED_X;
		}
		else
		{
			vx = -MUSHROOMS_SPEED_X;
		}

	}
	vy += MUSHROOMS_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(colliable_objects, coEvents);
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
			}
			else if (dynamic_cast<CBrick*>(e->obj))
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


