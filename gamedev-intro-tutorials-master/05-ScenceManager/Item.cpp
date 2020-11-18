#include "Item.h"
#include "Mushrooms.h"
#include "ItemCoin.h"
#include "ItemLeaves.h"
#include "ItemSign.h"
Item* Item::SpawnItem(int id)
{
	switch (id)
	{
	case MUSHROOMS_ID_RED:
		return new CMushrooms(MUSHROOMS_RED);
		break;
	case MUSHROOMS_ID_BULE:
		return new CMushrooms(MUSHROOMS_BULE);
		break;
	case COIN_ID:
		return new CItemCoin();
		break;
	case LEAVES_ID:
		return new CLeaves();
		break;
	case SIGN_ID:
		return new CItemSign();
		break;
	}
}
