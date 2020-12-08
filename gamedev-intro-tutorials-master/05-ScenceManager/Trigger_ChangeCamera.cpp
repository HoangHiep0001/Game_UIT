#include "Trigger_ChangeCamera.h"

Trigger_ChangeCamera::Trigger_ChangeCamera(float l, float t, float r, float b, int mapid,float mx,float my)
{
	x = l;
	y = t;
	width = r;
	height = b;
	mapcamera_id = mapid;
	mario_x = mx;
	mario_y = my;

}

void Trigger_ChangeCamera::Render()
{
	RenderBoundingBox();
}

void Trigger_ChangeCamera::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}
