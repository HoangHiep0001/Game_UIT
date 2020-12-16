#pragma once
#include "GameObject.h"
#define CHECKSTOP_DIRECTION_RIGHT	1
#define CHECKSTOP_DIRECTION_LEFT	2
#define CHECKSTOP_DIRECTION_UP	3
#define CHECKSTOP_DIRECTION_DOWN	4
class CCheckStop : public CGameObject
{
	int direction;
	int width;
	int height;
	bool isEnable = false;
public:
	CCheckStop(float l, float t, float r, float b, int state);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	int GetDirection() { return this->direction; }
	void SetIsEnable(bool x) { this->isEnable = x; }
	bool GetISEnable() { return this->isEnable; }
};


