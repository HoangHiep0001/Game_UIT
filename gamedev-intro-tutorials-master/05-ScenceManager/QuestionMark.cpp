#include "QuestionMark.h"
#include "Item.h"
#include "PlayScence.h"
#include "ItemCoin.h"


void CQuestionMark::Render()
{
	int ani = -1;
	switch (state)
	{
	case MARK_STATE_QUESTION:
		ani = MARK_ANI_QUESTION;
		break;
	case MARK_STATE_N_EMPTY:
		ani = MARK_ANI_QUESTION;
		break;
	case MARK_STATE_EMPTY:
		ani = MARK_ANI_EMPTY;
		break;
	}
	
	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox();
}

CQuestionMark::CQuestionMark()
{
	SetState(MARK_STATE_QUESTION);
	start_y = 0;
}

void CQuestionMark::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case MARK_STATE_QUESTION:
		vx = 0;
		vy = 0;
		break;
	case MARK_STATE_N_EMPTY:
	case MARK_STATE_EMPTY:
		vy = -MARK_CAKE_VY;
		break;
	}
}

void CQuestionMark::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + MARK_BBOX_WIDTH;
	b = y + MARK_BBOX_HEIGHT;
	
}

void CQuestionMark::Update(DWORD dt, CScene* scene, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, scene, coObjects);
	x += dx;
	y += dy;
	CPlayScene* pc = dynamic_cast<CPlayScene*>(scene);
	CMario* mario = pc->GetPlayer();
	if (y <= start_y - MAX_RANGE_Y)
	{
		vy = MARK_CAKE_VY;
		Item* item = new Item();
		item = item->SpawnItem(item_id, scene);
		float l, t, r, b;
		item->GetBoundingBox(l, t, r, b);
		if (item_id == LEAVES_ID && mario->GetLevel() == MARIO_LEVEL_BIG)
		{
			if (mario->GetApperance()==MARIO_NORMAL)
			{
				item->SetPosition(x, y - (b - t) - ITEM_POSITION);
				item->SetOX(x + MARK_BBOX_WIDTH / 2);
			}
			else
			{
				item->SetPosition(x, y - (b - t ) + ITEM_POSITION_Y);
			}
			
		}
		else if(item_id == COIN_ID_WALK)
		{
			item->SetPosition(x, y - (b - t)- ITEM_POSITION);
			CItemCoin* coin = dynamic_cast<CItemCoin*>(item);
			coin->SetStartCoinY(y);
			coin->SetState(ITEM_COIN_STATE_COIN);
		}
		else
		{
			item->SetPosition(x, y - (b - t));
		}
		CPlayScene* p = dynamic_cast<CPlayScene*>(scene);
		p->SpawnObject(item);
	}
	if (vy > 0 && y >= start_y)
	{
		is_up = false;
		vy = 0;
		y = start_y;
	}
}
