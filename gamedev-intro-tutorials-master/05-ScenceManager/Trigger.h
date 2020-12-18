#pragma once
#include "GameObject.h"
#define TRIGGER_DIRECTION_UP	0
#define TRIGGER_DIRECTION_DOWN	1
class Trigger : public CGameObject
{
	int State;
	int width;
	int height;
public:
	Trigger(float l, float t, float r, float b, int state);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	int GetTriggerState() { return this->State; }
};

