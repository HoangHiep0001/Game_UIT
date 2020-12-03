#pragma once

#include "GameObject.h"

/*
	Object that triggers scene switching
*/
class CPortal : public CGameObject
{
	int scene_id;	// target scene to switch to 

	int width;
	int height; 

	float mario_x;
	float mario_y;
public:
	CPortal(float l, float t, float r, float b, int scene_id,float mariox,float marioy);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	float GetMarioX() { return this->mario_x; }
	float GetMarioY() { return this->mario_y; }
	int GetSceneId() { return scene_id;  }
};