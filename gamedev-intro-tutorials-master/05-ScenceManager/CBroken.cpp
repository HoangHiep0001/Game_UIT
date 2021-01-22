#include "CBroken.h"
#include "PlayScence.h"
#include "Game.h"
CBroken::CBroken(D3DXVECTOR2 position, int nx, int ny)
{
	x = position.x;
	y = position.y;
	vx = BROKEN_VX * nx;
	vy = -BROKEN_VY * ny;
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(BROKEN_ANIMATION_SET_ID);
	this->animation_set = ani_set;
}

void CBroken::Render()
{
	if (isDestroy)
		return;
	animation_set->at(0)->Render(x, y);
	//RenderBoundingBox();
}

void CBroken::Update(DWORD dt, CScene* scene, vector<LPGAMEOBJECT>* coObjects)
{
	if (!CheckInCamera())
	{
			return;
	}
	vy += BROKEN_GRAVITY;
	CGameObject::Update(dt, scene, coObjects);

	x += dx;
	y += dy; 
}


void CBroken::GetBoundingBox(float& l, float& t, float& r, float& b)
{

	if (isDestroy)
		return;
	l = 0;
	t = 0;
	r = 0;
	b = 0;
}


