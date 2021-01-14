#include "CPortalintro.h"

CPortalintro::CPortalintro(float l, float t, float r, float b, int scene_id, float mariox, float marioy)
{
	this->scene_id = scene_id;
	x = l;
	y = t;
	width = r - l + 1;
	height = b - t + 1;
	this->mario_x = mariox;
	this->mario_y = marioy;
}

void CPortalintro::Render()
{
	//RenderBoundingBox();
}

void CPortalintro::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}
