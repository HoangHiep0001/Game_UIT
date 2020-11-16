#include "Item.h"
#include "Mushrooms.h"
#include "ItemCoin.h"
Item* Item::SpawnItem(int id)
{
	switch (id)
	{
	case MUSHROOMS_ID_RED:
		return new CMushrooms(MUSHROOMS_RED);
		break;
	case COIN_ID:
		return new CItemCoin();
		break;
	
	}
}
