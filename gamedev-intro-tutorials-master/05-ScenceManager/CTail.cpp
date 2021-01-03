#include "CTail.h"
#include "Mario.h"
#include "PlayScence.h"
#include "CBroken.h"
#include "CEffect.h"
#include "Cactus.h"

CTail::CTail(CScene* scene,int dir)
{
	nx = dir;
	this->tailHead = new CTailPoint(dir);
	this->tailLast = new CTailPoint(dir);

}

void CTail::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (isDestroy)
		return;
	float xh, yh, xl, yl;

	tailHead->GetPosition(xh, yh);
	tailLast->GetPosition(xl, yl);

	if (xh < xl)
	{
		left = xh;
		top = yh;
		right = xl;
		bottom = top + TAIL_BBOX_HEIGHT;
	}
	else
	{
		left = xl;
		top = yl;
		right = xh;
		bottom = top + TAIL_BBOX_HEIGHT;
	}
}

void CTail::Update(DWORD dt, CScene* scene, vector<LPGAMEOBJECT>* coObjects)
{
	if (isDestroy)
		return;


	CGameObject::Update(dt, scene, coObjects);

	float xh, yh, xl, yl;
	
	tailHead->GetPosition(xh, yh);
	tailLast->GetPosition(xl, yl);

	if (xh < xl)
	{
		x = xh;
		y = yh;
	}
	else
	{
		x = xl;
		y = yl;
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


			if (dynamic_cast<CKoopas*>(e->obj))
			{
				CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);
				if (e->nx != 0)
				{
					if (koopas->GetState() == KOOPAS_STATE_WALKING || koopas->GetState() == KOOPAS_STATE_FLYLING)
					{
						koopas->SetState(KOOPAS_STATE_LIVING_DOWN);
						vy = -KOOPAS_DIE_VY;
					}
					Effect(scene);
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
					Effect(scene);
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

	for (std::size_t i = 0; i < coObjects->size(); i++)
	{
		LPGAMEOBJECT e = coObjects->at(i);
		if (dynamic_cast<CBrick*>(e))
		{
			CBrick* brick = dynamic_cast<CBrick*> (e);

			float l, t, r, b, el, et, er, eb;
			this->GetBoundingBox(l, t, r, b);
			b = b;
			brick->GetBoundingBox(el, et, er, eb);
			if (CGameObject::AABB(l, t, r, b, el, et, er, eb))
			{
				if (brick->GetItemState() == 1)
				{
					Effect(scene);
					brick->setIsBroken(true);
				}
				else
				{
					brick->setIsBroken(true);
					brick->Destroy();
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
					if (question->GetState() == MARK_STATE_QUESTION || question->GetState() == MARK_STATE_N_EMPTY)
					{
						question->SetItemCount(question->GetItemCount() - 1);
						if (question->GetItemCount() == 0)
						{
							Effect(scene);
							question->SetState(MARK_STATE_EMPTY);
						}
						else
						{
							Effect(scene);
							question->SetState(MARK_STATE_N_EMPTY);
						}
					}
				}
			}
		}
		else if(dynamic_cast<CCactus*>(e))
		{
			CCactus* Cactus = dynamic_cast<CCactus*> (e);

			float l, t, r, b, el, et, er, eb;
			this->GetBoundingBox(l, t, r, b);
			b = b;
			Cactus->GetBoundingBox(el, et, er, eb);
			if (CGameObject::AABB(l, t, r, b, el, et, er, eb))
			{
				Effect(scene);
				Cactus->Destroy();
				
			}
		}
	}
}

void CTail::Render()
{
	if (isDestroy)
		return;
	//RenderBoundingBox();
}

void CTail::Effect(CScene* scene)
{
	float xh, yh, xl, yl;
	tailHead->GetPosition(xh, yh);
	tailLast->GetPosition(xl, yl);

	if (xh < xl)
	{
		x = xh;
		y = yh;
	}
	else
	{
		x = xl;
		y = yl;
	}
	CPlayScene* pc = dynamic_cast<CPlayScene*>(scene);
	if (nx>0)
	{
		CEffect* effect = new CEffect({ x , y }, EFFECT_NX, EFFECT_NY);
		pc->SpawnObject(effect);
		time_effect = GetTickCount64();
		effect->SetTimeEffect(time_effect);
	}
	else
	{
		CEffect* effect = new CEffect({ x , y },-EFFECT_NX, EFFECT_NY);
		pc->SpawnObject(effect);
		time_effect = GetTickCount64();
		effect->SetTimeEffect(time_effect);
	}
}



