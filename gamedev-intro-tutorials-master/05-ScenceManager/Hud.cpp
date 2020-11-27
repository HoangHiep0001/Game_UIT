#include "Hud.h"

Hud::Hud(CPlayScene* Scene)
{
	PlayScene = Scene;
	Game->GetInstance()->GetCamPos(x, y);
	y += Game->GetInstance()->GetScreenHeight() -48;
}

void Hud::Render()
{
	CSprites::GetInstance()->Get(HUB_SPIRE_SUPER_BLACK)->Draw(x , y -2, 255);
	CSprites::GetInstance()->Get(HUB_SPIRE_HUB)->Draw(x+30,y+10, 255);
	if (maxv >= 1)
	{
		CSprites::GetInstance()->Get(HUB_SPIRE_ARROW)->Draw(x + 30 + 52, y + 10 + 7, 255);
	}
}
void Hud::Update()
{
	Game->GetInstance()->GetCamPos(x, y);
	y += Game->GetInstance()->GetScreenHeight() - 48;

	CMario*  mario = PlayScene->GetPlayer();

	if (mario->GetState() == MARIO_STATE_WALKING_RIGHT_FAST || mario->GetState() == MARIO_STATE_WALKING_LEFT_FAST)
	{
		if (abs(mario->vx) > MARIO_WALKING_SPEED_MAX)
			maxv = 6;
		else if (abs(mario->vx) > MARIO_WALKING_SPEED_MAX * 5 / 6)
			maxv = 5;
		else if (abs(mario->vx) > MARIO_WALKING_SPEED_MAX * 4 / 6)
			maxv = 4;
		else if (abs(mario->vx) > MARIO_WALKING_SPEED_MAX * 3 / 6)
			maxv = 3;
		else if (abs(mario->vx) > MARIO_WALKING_SPEED_MAX * 2 / 6)
			maxv = 2;
		else if (abs(mario->vx) > MARIO_WALKING_SPEED_MAX * 1 / 6)
			maxv = 1;

	}
	else maxv = 0;
}