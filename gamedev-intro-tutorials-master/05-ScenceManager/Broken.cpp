#include "Broken.h"


void CBroken::Render()
{
	animation_set->at(0)->Render(x, y);
	RenderBoundingBox();
}

void CBroken::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + COIN_BBOX_WIDTH;
	b = y + COIN_BBOX_HEIGHT;
}