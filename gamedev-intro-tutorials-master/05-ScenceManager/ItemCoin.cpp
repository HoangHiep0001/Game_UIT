#include "ItemCoin.h"
#include "PlayScence.h"

CItemCoin::CItemCoin(int nsta)
{
	state = nsta;
	if (state ==ITEM_COIN_STATE_COIN)
	{
		vy = -COIN_FLY_Y;
		time=GetTickCount64();
	}
	this->score = COIN_SCORE;
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(ITEMCOIN_ANI_SET);
	this->SetAnimationSet(ani_set);
	
}

void CItemCoin::Render()
{
	if (isDestroy)
		return;
	int ani = -1;
	if (state == ITEM_COIN_STATE_COIN)
	{
		ani = ITEM_COIN_ANI_COIN;
	}
	else if(state==ITEM_COIN_STATE_IDE)
	{
		ani = ITEM_COIN_ANI_IDE;
	}
	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox();
}

void CItemCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (isDestroy)
	{
		return;
	}
	l = x;
	t = y;
	r = l + 14;
	b = t + COIN_BBOX_X_Y;
}

void CItemCoin::Update(DWORD dt, CScene* scene, vector<LPGAMEOBJECT>* colliable_objects)
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

	if (this->isBornByBrick)
	{
		CPlayScene* pc = dynamic_cast<CPlayScene*>(scene);
		if (pc->GetPlayer()->GetIsP() == false)
		{
			float x, y;
			this->GetPosition(x, y);
			this->Destroy();
			CBrick* brick = new CBrick();
			brick->SetAnimationSet();
			brick->SetPosition(x, y);
			brick->SetItemState(0);
			pc->SpawnObject(brick);
			this->Destroy();
		}
	}

	if (GetTickCount64() - time >= 200 && time>0)
	{
		Destroy();
	}

	x += dx;
	y += dy;
}
