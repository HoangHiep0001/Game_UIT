#pragma once
#include "GameObject.h"
class Trigger : public CGameObject
{
	int State;
	int width;
	int height;
public:
	Trigger(float l, float t, float r, float b, int state);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	int GetGroundState() { return this->State; }
};

