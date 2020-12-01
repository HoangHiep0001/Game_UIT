#include "CTree.h"

void CTree::Render()
{
	animation_set->at(0)->Render(x, y);
	//RenderBoundingBox();
}

void CTree::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + 0;
	b = y +0 ;
}
