#include "CCheckUpdate.h"
CCheckUpdate::CCheckUpdate(float l, float t, float r, float b, int scene_id, float mariox, float marioy)
{
	x = l;
	y = t;
	width = r;
	height = b;
	this->scene_id = scene_id;
	this->mario_x = mariox;
	this->mario_y = marioy;
}

void CCheckUpdate::Render()
{
	RenderBoundingBox();
}

void CCheckUpdate::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}
