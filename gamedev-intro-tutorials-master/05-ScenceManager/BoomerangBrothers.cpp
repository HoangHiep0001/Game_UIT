//#include "BoomerangBrothers.h"
//#include "PlayScence.h"
//#include "Ground.h"
//
//CBoomerangBrothers::CBoomerangBrothers()
//{
//	SetState(BOOMERANG_BROTHERS_STATE_RIGHT);
//}
//
//void CBoomerangBrothers::GetBoundingBox(float& left, float& top, float& right, float& bottom)
//{
//	left = x;
//	top = y;
//	switch (state)
//	{
//	case BOOMERANG_BROTHERS_STATE_LEFT:
//	case BOOMERANG_BROTHERS_STATE_RIGHT:
//		right = x + BOOMERANG_BROTHERS_BBOX_WIDTH;
//		bottom = y + BOOMERANG_BROTHERS_BBOX_HEIGHT;
//		break;
//	}
//	Bound.left = left;
//	Bound.right = right;
//	Bound.bottom = bottom;
//	Bound.top = top;
//
//	if (isDestroy)
//	{
//		right = 0;
//		bottom = 0;
//	}
//}
//void CBoomerangBrothers::Update(DWORD dt, CScene* scene, vector<LPGAMEOBJECT>* coObjects)
//{
//	if (!CheckInCamera())
//	{
//		if (isDestroy)
//		{
//			//this->SetState(state_goomba);
//			isDestroy = false;
//		}
//		return;
//	}
//
//	if (isDestroy)
//	{
//		this->SetPosition(startx, starty);
//		return;
//	}
//
//	
//	
//
//	CGameObject::Update(dt, scene, coObjects);
//
//	
//
//	vy += BOOMERANG_BROTHERS_GRAVITY * dt;
//
//
//	vector<LPCOLLISIONEVENT> coEvents;
//	vector<LPCOLLISIONEVENT> coEventsResult;
//
//	coEvents.clear();
//
//
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
//				if (state == GOOMBA_STATE_FLYLING || state == GOOMBA_STATE_WALKING || state == GOOMBA_STATE_WALKING_WING)
//				{
//					if (dynamic_cast<Ground*>(e->obj)->GetGroundState() == 1)
//					{
//						if (e->ny > 0)
//						{
//							y += dy;
//							vy = 0;
//						}
//						if (e->nx != 0)
//						{
//							this->nx = -this->nx;
//							vx = -vx;
//
//						}
//						if (e->ny < 0)
//						{
//							vy = 0;
//						}
//					}
//					if (dynamic_cast<Ground*>(e->obj)->GetGroundState() == 0)
//					{
//						if (e->ny < 0)
//						{
//							vy = 0;
//						
//						}
//						if (e->nx != 0)
//						{
//							this->nx = -this->nx;
//							vx = -vx;
//						}
//					}
//				}
//
//
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
//
//	
//
//}
//
//void CBoomerangBrothers::Render()
//{
//	//if (isDestroy)
//	//	return;
//	//int ani = -1;
//	//
//	//	switch (state)
//	//	{
//	//	case BOOMERANG_BROTHERS_STATE_LEFT:
//	//		ani = BOOMERANG_BROTHERS_ANI_RED_LEFT;
//	//		break;
//	//	case BOOMERANG_BROTHERS_STATE_RIGHT:
//	//		ani = BOOMERANG_BROTHERS_ANI_RED_RIGHT;
//	//		break;
//	//	}
//	//animation_set->at(ani)->Render(x, y);
//
//	////RenderBoundingBox();
//}
//
//void CGoomba::SetState(int state)
//{
//	/*CGameObject::SetState(state);
//	switch (state)
//	{
//
//	case BOOMERANG_BROTHERS_STATE_LEFT:
//		vx = -BOOMERANG_BROTHERS_WALKING_SPEED;
//		vy = 0;
//		break;
//	case BOOMERANG_BROTHERS_STATE_RIGHT:
//		vx = BOOMERANG_BROTHERS_WALKING_SPEED;
//		vy = 0;
//		break;
//	}*/
//}
//
