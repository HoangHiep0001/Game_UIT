#include "Coin.h"


void CCoin::Render()
{
	if (isDestroy)
	{
		return;
	}
	animation_set->at(0)->Render(x, y);
	//RenderBoundingBox();
}

void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (isDestroy)
	{
		return;
	}
	l = x;
	t = y;
	r = x + COIN_BBOX_WIDTH;
	b = y + COIN_BBOX_HEIGHT;
}

