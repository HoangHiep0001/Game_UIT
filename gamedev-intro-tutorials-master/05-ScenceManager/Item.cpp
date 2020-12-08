#include "Item.h"
#include "Mushrooms.h"
#include "ItemCoin.h"
#include "ItemLeaves.h"
#include "ItemSign.h"
#include "PlayScence.h"
#include "Mario.h"
#include "Brick.h"
Item* Item::SpawnItem(int id, CScene* scene)
{
	CPlayScene* pc = dynamic_cast<CPlayScene*>(scene);
	CMario* mario = pc->GetPlayer();
	CItemSign* sign = dynamic_cast<CItemSign*>(pc->GetPlayer());
	CBrick* brick = dynamic_cast<CBrick*>(pc->GetPlayer());
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
			return new CLeaves();
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
