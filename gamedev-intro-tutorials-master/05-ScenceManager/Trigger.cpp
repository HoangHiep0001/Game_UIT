#include "Trigger.h"

Trigger::Trigger(float l, float t, float r, float b, int state)
{
	State = state;
	x = l;
	y = t;
	width = r;
	height = b;
}

void Trigger::Render()
{
	//RenderBoundingBox();
}

void Trigger::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}
