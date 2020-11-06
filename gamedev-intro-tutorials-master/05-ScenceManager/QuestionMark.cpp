#include "QuestionMark.h"
void CQuestionMark::Render()
{
	animation_set->at(0)->Render(x, y);
	RenderBoundingBox();
}

void CQuestionMark::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + MARK_BBOX_WIDTH;
	b = y + MARK_BBOX_HEIGHT;
}