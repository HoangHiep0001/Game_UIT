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
	case SEWERPIPES_STATE_THREE:
		ani = SEWERPIPES_ANI_THREE;
		break;
	case SEWERPIPES_STATE_FOUR:
		ani = SEWERPIPES_ANI_FOUR;
		break;
	case SEWERPIPES_STATE_FIVE:
		ani = SEWERPIPES_ANI_FIVE;
		break;
	}
	animation_set->at(ani)->Render(x, y);
	//RenderBoundingBox();
}

void SewerPipes::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = 0;
	t = 0;
	r = 0;
	b = 0;
}

void SewerPipes::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case SEWERPIPES_STATE_ONE:
	case SEWERPIPES_STATE_TWO:
	case SEWERPIPES_STATE_THREE:
	case SEWERPIPES_STATE_FOUR:
	case SEWERPIPES_STATE_FIVE:
		vx = 0;
		vy = 0;
		break;
	}
}
