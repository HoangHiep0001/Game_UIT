#pragma once
#include "GameObject.h"




//#cong32*4
#define SEWERPIPES_STATE_ONE 1
//cong32 * 32
#define SEWERPIPES_STATE_TWO 2
//cong32 * 208
#define SEWERPIPES_STATE_THREE 3
//cong32 * 48 den trang
#define SEWERPIPES_STATE_FOUR 4
//cong32 * 64
#define SEWERPIPES_STATE_FIVE 5


#define SEWERPIPES_ANI_ONE 0
#define SEWERPIPES_ANI_TWO 1
#define SEWERPIPES_ANI_THREE 2
#define SEWERPIPES_ANI_FOUR 3
#define SEWERPIPES_ANI_FIVE 4
class SewerPipes : public CGameObject
{

public:
	SewerPipes();
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state);
};

