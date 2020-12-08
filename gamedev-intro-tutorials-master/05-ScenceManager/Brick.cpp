#include "Brick.h"
#include "PlayScence.h"
#include "Item.h"
#include "QuestionMark.h"
#include "ItemSign.h"
#include "ItemCoin.h"

void CBrick::Render()
{
	if (isDestroy)
		return;
	int ani = -1;
	switch (state)
	{
	case BRICK_STATE_BRICK:
		ani = BRICK_ANI_BRICK;
		break;
	case BRICK_STATE_EMPTY:
		ani = BRICK_ANI_EMPTY;
		break;
	}
	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox();
}

void CBrick::Update(DWORD dt, CScene* scene, vector<LPGAMEOBJECT>* coObjects)
{
	
	if (!CheckInCamera())
	{
		return;
	}

	CGameObject::Update(dt, scene, coObjects);
	x += dx;
	y += dy;

	CPlayScene* pc = dynamic_cast<CPlayScene*>(scene);
	
	if (this->item_state == 0)
	{
		if (pc->GetPlayer()->GetIsP() && !isDestroy)
		{
			float x, y;
			this->GetPosition(x, y);
			this->Destroy();
			CItemCoin* coin = new CItemCoin(ITEM_COIN_STATE_IDE);
			coin->SetPosition(x, y);
			coin->SetIsBornByBrick(true);
			pc->SpawnObject(coin);

		}
	}
	else
	{
		if (state == BRICK_STATE_EMPTY && this->item_count > 0)
	{
		if (item_state != 0)
		{
			Item* item = new Item();
			item = item->SpawnItem(item_id, scene);
			float l, t, r, b;
			item->GetBoundingBox(l, t, r, b);
			item->SetPosition(x, y -(b-t));
			pc->SpawnObject(item);
			this->item_count--;
		}
	}
		if (isDestroy)
	{
		if (item_count != 0 && GetState() == BRICK_STATE_BRICK)
		{
			if (item_state != 0)
			{
				Item* item = new Item();
				item = item->SpawnItem(item_id, scene);
				float l, t, r, b;
				item->GetBoundingBox(l, t, r, b);
				item->SetPosition(x, y-(b - t));
				pc->SpawnObject(item);
				item_count--;
			}
			else
			{
				Destroy();
			}
		}
		return;
	}
	}
}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	if (isDestroy)
		return;
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}

CBrick::CBrick()
{
	SetState(BRICK_STATE_BRICK);
}
