#include "Brick.h"
#include "PlayScence.h"
#include "Item.h"
#include "QuestionMark.h"
#include "ItemSign.h"
#include "ItemCoin.h"
#include "CBroken.h"

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
	case BRICK_STATE_BROKEN:
		ani = BRICK_ANI_BROKEN;
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
	if (this->Isbroken)
	{
		if (this->GetState() == BRICK_STATE_BRICK)
		{
			CPlayScene* pc = dynamic_cast<CPlayScene*>(scene);
			CBroken* topLeftPiece = new CBroken({ x - BRICK_X1, y - BRICK_Y1 }, -BRICK_NX, -BRICK_NY);
			CBroken* topRightPiece = new CBroken({ x + BRICK_X2, y - BRICK_Y1 }, BRICK_NX, -BRICK_NY);
			CBroken* bottomLeftPiece = new CBroken({ x - BRICK_X1, y + BRICK_Y2 }, -BRICK_NX, BRICK_NY);
			CBroken* bottomRightPiece = new CBroken({ x + BRICK_X2, y + BRICK_Y2 }, BRICK_NX, BRICK_NY);
			pc->SpawnObject(topLeftPiece);
			pc->SpawnObject(topRightPiece);
			pc->SpawnObject(bottomLeftPiece);
			pc->SpawnObject(bottomRightPiece);
			this->Isbroken = false;
			if (this->GetItemCount() >= 0)
			{
				this->SetState(BRICK_STATE_EMPTY);
			}
		}
	}


	CPlayScene* pc = dynamic_cast<CPlayScene*>(scene);
	CGameObject::Update(dt, scene, coObjects);
	x += dx;
	y += dy;


	
	if (this->item_state == 0)
	{
		if (pc->GetPlayer()->GetIsP() && !isDestroy)
		{
			float x, y;
			this->GetPosition(x, y);
			this->Destroy();
			CItemCoin* coin = new CItemCoin(ITEM_COIN_STATE_IDE);
			time = GetTickCount64();
			coin->SetTimeCoin(time);
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

void CBrick::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BRICK_STATE_BRICK:
		break;
	}
}
