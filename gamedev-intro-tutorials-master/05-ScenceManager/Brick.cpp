#include "Brick.h"
#include "PlayScence.h"
#include "Item.h"
#include "QuestionMark.h"

void CBrick::Render()
{
	if (isDestroy)
		return;
	animation_set->at(0)->Render(x, y);
	RenderBoundingBox();
}

void CBrick::Update(DWORD dt, CScene* scene, vector<LPGAMEOBJECT>* coObjects)
{
	CPlayScene* pc = dynamic_cast<CPlayScene*>(scene);
	CQuestionMark* mark = dynamic_cast<CQuestionMark*>(pc->GetPlayer());
	if (isDestroy)
	{
		if (item_count != 0)
		{
			if (item_state == 0)
			{
				Item* item = new Item();
				item = item->SpawnItem(item_id, scene);
				float l, t, r, b;
				item->GetBoundingBox(l, t, r, b);
				item->SetPosition(x, y);
				pc->SpawnObject(item);
				item_count--;
			}
			else
			{
				Item* item = new Item();
				item = item->SpawnItem(item_id, scene);
				float l, t, r, b;
				item->GetBoundingBox(l, t, r, b);
				item->SetPosition(x, y);
				pc->SpawnObject(item);
				//mark->SetState(MARK_STATE_QUESTION);
				item_count--;
			}
		}
		return;
	}
	CGameObject::Update(dt, scene, coObjects);
	x += dx;
	y += dy;

}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	if (isDestroy)
		return;
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}