#include "QuestionMark.h"
#include "Item.h"
#include "PlayScence.h"


void CQuestionMark::Render()
{
	int ani = -1;
	switch (state)
	{
	case MARK_STATE_QUESTION:
		ani = MARK_ANI_QUESTION;
		break;
	case MARK_STATE_N_EMPTY:
		ani = MARK_ANI_QUESTION;
		break;
	case MARK_STATE_EMPTY:
		ani = MARK_ANI_EMPTY;
		break;
	}
	
	animation_set->at(ani)->Render(x, y);
	RenderBoundingBox();
}

CQuestionMark::CQuestionMark()
{
	SetState(MARK_STATE_QUESTION);
	start_y = 0;
}

void CQuestionMark::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case MARK_STATE_QUESTION:
		vx = 0;
		vy = 0;
		break;
	case MARK_STATE_N_EMPTY:
	case MARK_STATE_EMPTY:
		vy = -MARK_CAKE_VY;
		break;
	}
}

void CQuestionMark::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + MARK_BBOX_WIDTH;
	b = y + MARK_BBOX_HEIGHT;
	
}

void CQuestionMark::Update(DWORD dt, CScene* scene, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, scene, coObjects);
	x += dx;
	y += dy;
	if (y <= start_y - MAX_RANGE_Y)
	{
		vy = MARK_CAKE_VY;
		Item* item = new Item();
		item = item->SpawnItem(item_id,scene);
		float l, t, r, b;
		item->GetBoundingBox(l, t,r,b);
		item->SetPosition(x, y - (b - t));
		CPlayScene* pc = dynamic_cast<CPlayScene*>(scene);
		pc->SpawnObject(item);
	}
	if (vy > 0 && y >= start_y)
	{
		vy = 0;
		y = start_y;
	}

}
