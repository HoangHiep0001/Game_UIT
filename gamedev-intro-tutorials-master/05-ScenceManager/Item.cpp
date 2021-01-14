#include "Item.h"
#include "Mushrooms.h"
#include "ItemCoin.h"
#include "ItemLeaves.h"
#include "ItemSign.h"
#include "PlayScence.h"
#include "Mario.h"
#include "Brick.h"
#include "ItemFlowerFire.h"
Item* Item::SpawnItem(int id, CScene* scene)
{
	CPlayScene* pc = dynamic_cast<CPlayScene*>(scene);
	CMario* mario = pc->GetPlayer();
	switch (id)
	{
	case MUSHROOMS_ID_BULE:
		return new CMushrooms(MUSHROOMS_BULE);
		break;
	case COIN_ID_WALK:
		return new CItemCoin(ITEM_COIN_STATE_COIN);
		break;
	case COIN_ID_IDE:
		break;
	case LEAVES_ID:
		if (mario->GetLevel() == MARIO_LEVEL_BIG)
		{
			if (mario->GetApperance() == MARIO_FOX)
			{
				return new CFlowerFire();
			}
			else
			{
				return new CLeaves();
			}
		}
		else
		{
			return new CMushrooms(MUSHROOMS_RED);
		}
		break;
	case SIGN_ID:
		return new CItemSign(ITEM_SIGN_STATE_P);
		break;
	}
}
