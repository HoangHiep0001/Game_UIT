//
//#include "Koopas.h"
//#include "Ground.h"
//#include "Brick.h"
//#include "QuestionMark.h"
//#include "Utils.h"
//
//CKoopas::CKoopas(int appe)
//{
//	apperance = appe;
//	SetState(KOOPAS_STATE_WALKING);
//}
//void CKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
//{
//	left = x;
//	top = y;
//	switch (state)
//	{
//	case KOOPAS_STATE_WALKING:
//		right = x + KOOPAS_BBOX_WIDTH;
//		bottom = y + KOOPAS_BBOX_HEIGHT;
//		break;
//	case KOOPAS_STATE_FLYLING:
//		right = x + KOOPAS_BBOX_WIDTH;
//		bottom = y + KOOPAS_BBOX_HEIGHT;
//		break;
//	case KOOPAS_STATE_DIE_UP:
//		right = x;
//		bottom = y;
//		break;
//	case KOOPAS_STATE_LIVING_UP:
//		right = x + KOOPAS_BBOX_LIVING;
//		bottom = y + KOOPAS_BBOX_LIVING;
//		break;
//	case KOOPAS_STATE_TORTOISESHELL_UP:
//		right = x + KOOPAS_BBOX_LIVING;
//		bottom = y + KOOPAS_BBOX_LIVING;
//		break;
//	case KOOPAS_STATE_DIE_DOWN:
//		right = x;
//		bottom = y;
//		break;
//	case KOOPAS_STATE_LIVING_DOWN:
//		right = x + KOOPAS_BBOX_LIVING;
//		bottom = y + KOOPAS_BBOX_LIVING;
//		break;
//	case KOOPAS_STATE_TORTOISESHELL_DOWN:
//		right = x + KOOPAS_BBOX_LIVING;
//		bottom = y + KOOPAS_BBOX_LIVING;
//		break;
//	}
//	Bound.left = left;
//	Bound.right = right;
//	Bound.bottom = bottom;
//	Bound.top = top;
//	if (isDestroy)
//	{
//		right = 0;
//		bottom = 0;
//	}
//}
//
//void CKoopas::Update(DWORD dt, CScene* scene, vector<LPGAMEOBJECT>* coObjects)
//{
//	if (!CheckInCamera())
//	{
//		return;
//	}
//	if (isDestroy)
//	{
//		return;
//	}
//	CGameObject::Update(dt, scene, coObjects);
//	vy += KOOPAS_GRAVITY * dt;
//	vector<LPCOLLISIONEVENT> coEvents;
//	vector<LPCOLLISIONEVENT> coEventsResult;
//
//	coEvents.clear();
//
//	CalcPotentialCollisions(coObjects, coEvents);
//	if (coEvents.size() == 0)
//	{
//		x += dx;
//		y += dy;
//	}
//	else
//	{
//		float min_tx, min_ty, nx = 0, ny;
//		float rdx = 0;
//		float rdy = 0;
//
//		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
//		x += min_tx * dx + nx * 0.4f;
//		y += min_ty * dy + ny * 0.4f;
//
//
//		for (UINT i = 0; i < coEventsResult.size(); i++)
//		{
//			LPCOLLISIONEVENT e = coEventsResult[i];
//			if (dynamic_cast<Ground*>(e->obj))
//			{
//				if (e->ny < 0)
//				{
//					vy = 0;
//				}
//				if (e->nx != 0)
//				{
//					nx = -nx;
//					vx = -vx;
//				}
//			}
//			else if (dynamic_cast<CBrick*>(e->obj))
//			{
//				if (e->ny < 0)
//				{
//					vy = 0;
//				}
//				if (e->nx != 0)
//				{
//					nx = -nx;
//					vx = -vx;
//				}
//			}
//			else if (dynamic_cast<CQuestionMark*>(e->obj))
//			{
//				if (e->ny < 0)
//				{
//					vy = 0;
//				}
//				if (e->nx != 0)
//				{
//					nx = -nx;
//					vx = -vx;
//				}
//			}
//			else
//			{
//				if (e->nx != 0)
//					x += dx;
//				if (e->ny != 0)
//					y += dy;
//			}
//		}
//	}
//	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
//}
//
//void CKoopas::Render()
//{
//
//	if (isDestroy)
//		return;
//	int ani = -1;
//	if (apperance==KOOPAS_BULE)
//	{
//		switch (state)
//		{
//		case KOOPAS_STATE_WALKING:
//			if (nx>0)
//			{
//				ani = KOOPAS_ANI_BULE_WALKING_RIGHT;
//			}
//			else
//			{
//				ani = KOOPAS_ANI_BULE_WALKING_LEFT;
//			}
//			break;
//		case KOOPAS_STATE_FLYLING:
//			if (nx>0)
//			{
//				ani = KOOPAS_ANI_BULE_FLYLING_RIGHT;
//			}
//			else
//			{
//				ani = KOOPAS_ANI_BULE_FLYLING_LEFT;
//			}
//			break;
//		case KOOPAS_STATE_DIE_UP:
//		case KOOPAS_STATE_LIVING_UP:
//			ani = KOOPAS_ANI_BULE_DIE_UP;
//			break;
//		case KOOPAS_STATE_DIE_DOWN:
//		case KOOPAS_STATE_LIVING_DOWN:
//			ani = KOOPAS_ANI_BULE_DIE_DOWN;
//			break;
//		case KOOPAS_STATE_TORTOISESHELL_UP:
//			ani = KOOPAS_ANI_BULE_TORTOISESHELL_UP;
//			break;
//		case KOOPAS_STATE_TORTOISESHELL_DOWN:
//			ani = KOOPAS_ANI_BULE_TORTOISESHELL_DOWN;
//			break;
//		}
//	}
//	else if (apperance==KOOPAS_BULE)
//	{
//		switch (state)
//		{
//		case KOOPAS_STATE_WALKING:
//			if (nx > 0)
//			{
//				ani = KOOPAS_ANI_RED_WALKING_RIGHT;
//			}
//			else
//			{
//				ani = KOOPAS_ANI_RED_WALKING_LEFT;
//			}
//			break;
//		case KOOPAS_STATE_FLYLING:
//			if (nx > 0)
//			{
//				ani = KOOPAS_ANI_RED_FLYLING_RIGHT;
//			}
//			else
//			{
//				ani = KOOPAS_ANI_RED_FLYLING_LEFT;
//			}
//			break;
//		case KOOPAS_STATE_DIE_UP:
//		case KOOPAS_STATE_LIVING_UP:
//			ani = KOOPAS_ANI_RED_DIE_UP;
//			break;
//		case KOOPAS_STATE_DIE_DOWN:
//		case KOOPAS_STATE_LIVING_DOWN:
//			ani = KOOPAS_ANI_RED_DIE_DOWN;
//			break;
//		case KOOPAS_STATE_TORTOISESHELL_UP:
//			ani = KOOPAS_ANI_RED_TORTOISESHELL_UP;
//			break;
//		case KOOPAS_STATE_TORTOISESHELL_DOWN:
//			ani = KOOPAS_ANI_RED_TORTOISESHELL_DOWN;
//			break;
//		}
//	}
//	int alpha = 255;
//    animation_set->at(ani)->Render(x, y,alpha);
//	RenderBoundingBox();
//}
//
//void CKoopas::SetState(int state)
//{
//	switch (state)
//	{
//	case KOOPAS_STATE_DIE_UP:
//		vx = 0;
//		vy = 0;
//		break;
//	case KOOPAS_STATE_LIVING_UP:
//		y += KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_LIVING;
//		vx = 0;
//		vy = 0;
//		break;
//	case KOOPAS_STATE_DIE_DOWN:
//		vx = 0;
//		vy = 0;
//		break;
//	case KOOPAS_STATE_LIVING_DOWN:
//		y += KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_LIVING;
//		vx = 0;
//		vy = 0;
//		break;
//	case KOOPAS_STATE_WALKING:
//		vx = -KOOPAS_WALKING_SPEED;
//		break;
//	case KOOPAS_STATE_FLYLING:
//		vy = -KOOPAS_JUMP_SPEED_Y;
//		vx = -KOOPAS_WALKING_SPEED;
//		break;
//	case KOOPAS_STATE_TORTOISESHELL_UP:
//		vx = KOOPAS_TORTOISESHELL;
//		break;
//	case KOOPAS_STATE_TORTOISESHELL_DOWN:
//		vx = KOOPAS_TORTOISESHELL;
//		break;
//	}
//}