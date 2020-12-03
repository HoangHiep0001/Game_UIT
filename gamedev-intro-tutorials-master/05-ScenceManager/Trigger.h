#pragma once
#include "GameObject.h"
#define TRIGGER_STATE_SEWERPIPES_MAP1 1
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

