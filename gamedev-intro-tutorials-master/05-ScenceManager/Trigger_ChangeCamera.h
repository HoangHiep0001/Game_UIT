#pragma once
#include "GameObject.h"
class Trigger_ChangeCamera : public CGameObject
{
	int width;
	int height;

	int mapcamera_id;
	float mario_x, mario_y;
public:
	Trigger_ChangeCamera(float l, float t, float r, float b, int mapcamera_id,float mario_x,float mario_y);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	int getCameraMapID() { return this->mapcamera_id; }
	float getMarioX() { return this->mario_x; }
	float getMarioY() { return this->mario_y; }

};

