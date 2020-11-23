#pragma once
#include "GameObject.h"
#define SEWERPIPES_STATE_ONE 1
#define SEWERPIPES_STATE_TWO 2

#define SEWERPIPES_ANI_ONE 0
#define SEWERPIPES_ANI_TWO 1
class SewerPipes : public CGameObject
{

public:
	SewerPipes();
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state);
};

