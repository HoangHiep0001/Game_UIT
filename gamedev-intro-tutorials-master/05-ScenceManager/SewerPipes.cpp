#include "SewerPipes.h"

SewerPipes::SewerPipes()
{

}

void SewerPipes::Render()
{
	
	int ani = -1;
	switch (state)
	{
	case SEWERPIPES_STATE_ONE:
		ani = SEWERPIPES_ANI_ONE;
		break;
	case SEWERPIPES_STATE_TWO:
		ani = SEWERPIPES_ANI_TWO;
		break;
	}
	animation_set->at(ani)->Render(x, y);
	//RenderBoundingBox();
}

void SewerPipes::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + 1;
	b = y + 1;
}

void SewerPipes::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case SEWERPIPES_STATE_ONE:
	case SEWERPIPES_STATE_TWO:
		vx = 0;
		vy = 0;
		break;
	}
}
