#include "CCheckStop.h"

CCheckStop::CCheckStop(float l, float t, float r, float b, int direction)
{
	this->direction = direction;
	x = l;
	y = t;
	width = r;
	height = b;
}

void CCheckStop::Render()
{
	//RenderBoundingBox();
}

void CCheckStop::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}
