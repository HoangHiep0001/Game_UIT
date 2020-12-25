#include "CEffect.h"
#include "PlayScence.h"
#include "Game.h"
CEffect::CEffect(D3DXVECTOR2 position, int nx, int ny)
{
	x = position.x;
	y = position.y;
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(EFFECT_ANIMATION_SET_ID);
	this->animation_set = ani_set;
}

void CEffect::Render()
{
	if (isDestroy)
		return;
	animation_set->at(0)->Render(x, y);
	//RenderBoundingBox();
}

void CEffect::Update(DWORD dt, CScene* scene, vector<LPGAMEOBJECT>* coObjects)
{
	if (isDestroy)
		return;
	if (GetTickCount64() - time_effect >= EFFECT_TIME)
	{
		Destroy();
	}
	if (!CheckInCamera())
	{
		return;
	}
	CGameObject::Update(dt, scene, coObjects);
	x += dx;
	y += dy;
}


void CEffect::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (isDestroy)
		return;
	l = 0;
	t = 0;
	r = 0;
	b = 0;
}
