#include "ItemFlowerFire.h"
#include "PlayScence.h"
#include "Ground.h"
#include "Mario.h"

CFlowerFire::CFlowerFire()
{
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(FLOWER_FIRE_ANI_SET);
	this->SetAnimationSet(ani_set);
}

void CFlowerFire::Render()
{
	if (isDestroy)
		return;
	int ani = FLOWER_FIRE_ANI_FLOWER;
	
	animation_set->at(ani)->Render(x, y);

	RenderBoundingBox();
}

void CFlowerFire::GetBoundingBox(float& l, float& t, float& r, float& b)
{

	if (isDestroy)
		return;
	l = x;
	t = y;
	r = x + FLOWER_FIRE_BBOX_X;
	b = y + FLOWER_FIRE_BBOX_Y;

}

void CFlowerFire::Update(DWORD dt, CScene* scene, vector<LPGAMEOBJECT>* colliable_objects)
{
	if (isDestroy)
	{
		return;
	}
	if (!CheckInCamera())
	{
		return;
	}
	CGameObject::Update(dt, scene, colliable_objects);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
}