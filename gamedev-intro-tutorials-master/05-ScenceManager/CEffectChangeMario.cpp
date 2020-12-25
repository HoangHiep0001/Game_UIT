#include "CEffectChangeMario.h"
#include "PlayScence.h"
#include "Game.h"
CEffectChangeMario::CEffectChangeMario(D3DXVECTOR2 position)
{
	x = position.x;
	y = position.y;
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(EFFECT_CHANGE_MARIO_ANIMATION_SET_ID);
	this->animation_set = ani_set;
}

void CEffectChangeMario::Render()
{
	if (isDestroy)
		return;
	animation_set->at(0)->Render(x, y);
	//RenderBoundingBox();
}

void CEffectChangeMario::Update(DWORD dt, CScene* scene, vector<LPGAMEOBJECT>* coObjects)
{
	if (isDestroy)
		return;
	if (GetTickCount64() - time_effect >= EFFECT_CHANGE_MARIO_TIME)
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


void CEffectChangeMario::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (isDestroy)
		return;
	l = 0;
	t = 0;
	r = 0;
	b = 0;
}
