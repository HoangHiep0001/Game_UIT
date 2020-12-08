#include "ItemCoin.h"
#include "PlayScence.h"

CItemCoin::CItemCoin(int nsta)
{
	if (state == ITEM_COIN_STATE_COIN)
	{
		time = GetTickCount64();
	}
	state = nsta;
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
	r = l + 0;
	b = t + 0;
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
    CPlayScene* pc = dynamic_cast<CPlayScene*>(scene);
	CMario* mario = pc->GetPlayer();
	if (this->isBornByBrick)
	{
		
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

	
	if (state==ITEM_COIN_STATE_COIN)
	{
		vy = -COIN_FLY_Y;

		if (GetTickCount64() - time >= 200 )
		{
			mario->SetScore(score+ mario->GetScore());
			mario->SetCoin_number(coin_number + mario->GetCoin_number());
			Destroy();
		}
		
	}
	x += dx;
	y += dy;
}

void CItemCoin::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ITEM_COIN_STATE_COIN:
		time = GetTickCount64();
		break;
	case ITEM_COIN_STATE_IDE:
		vy = 0;
		vx = 0;
		break;
	}
}
