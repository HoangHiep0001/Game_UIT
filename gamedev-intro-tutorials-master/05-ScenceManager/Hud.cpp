#include "Hud.h"

Hud::Hud(CPlayScene* Scene)
{
	PlayScene = Scene;
	Game->GetInstance()->GetCamPos(x, y);
	y += Game->GetInstance()->GetScreenHeight() - SEEN_HEIGHT;
	word = PlayScene->GetWord();
	time = PlayScene->GetTime();
	number = PlayScene->GetNumber();
}

void Hud::Render()
{
	CSprites::GetInstance()->Get(HUB_SPIRE_SUPER_BLACK)->Draw(x , y , 255);
	CSprites::GetInstance()->Get(HUB_SPIRE_HUB)->Draw(x + HUB_LOCATION_HUB_X,y + HUB_LOCATION_HUB_Y, 255);
	CSprites::GetInstance()->Get(HUB_SPIRE_NETWORK_M)->Draw(x + HUB_LOCATION_HUB_X+4, y + HUB_LOCATION_HUB_Y+15, 255);
	CMario* mario = PlayScene->GetPlayer();
	if (mario->GetState() != MARIO_STATE_WALKING_RIGHT || mario->GetState() == MARIO_STATE_WALKING_LEFT)
	{
		if (mario->GetState() == MARIO_STATE_WALKING_RIGHT_FAST || mario->GetState() == MARIO_STATE_WALKING_LEFT_FAST || mario->GetState() == MARIO_FLYLING_SPEED_Y)
		{
			if (maxv >= 1)
			{
				CSprites::GetInstance()->Get(HUB_SPIRE_ARROW)->Draw(x + HUB_LOCATION_HUB_X + HUB_LOCATION_ARROW_X1, y + HUB_LOCATION_HUB_Y + HUB_LOCATION_ARROW_Y, 255);
			}
			if (maxv >= 2)
			{
				CSprites::GetInstance()->Get(HUB_SPIRE_ARROW)->Draw(x + HUB_LOCATION_HUB_X + HUB_LOCATION_ARROW_X2, y + HUB_LOCATION_HUB_Y + HUB_LOCATION_ARROW_Y, 255);
			}
			if (maxv >= 3)
			{
				CSprites::GetInstance()->Get(HUB_SPIRE_ARROW)->Draw(x + HUB_LOCATION_HUB_X + HUB_LOCATION_ARROW_X3, y + HUB_LOCATION_HUB_Y + HUB_LOCATION_ARROW_Y, 255);
			}
			if (maxv >= 4)
			{
				CSprites::GetInstance()->Get(HUB_SPIRE_ARROW)->Draw(x + HUB_LOCATION_HUB_X + HUB_LOCATION_ARROW_X4, y + HUB_LOCATION_HUB_Y + HUB_LOCATION_ARROW_Y, 255);
			}
			if (maxv >= 5)
			{
				CSprites::GetInstance()->Get(HUB_SPIRE_ARROW)->Draw(x + HUB_LOCATION_HUB_X + HUB_LOCATION_ARROW_X5, y + HUB_LOCATION_HUB_Y + HUB_LOCATION_ARROW_Y, 255);
			}
			if (maxv >= 6)
			{
				CSprites::GetInstance()->Get(HUB_SPIRE_ARROW)->Draw(x + HUB_LOCATION_HUB_X + HUB_LOCATION_ARROW_X6, y + HUB_LOCATION_HUB_Y + HUB_LOCATION_ARROW_Y, 255);
				CSprites::GetInstance()->Get(HUB_SPIRE_MAX_P)->Draw(x + HUB_LOCATION_HUB_X + HUB_LOCATION_P_X, y + HUB_LOCATION_HUB_Y + HUB_LOCATION_ARROW_Y, 255);
			}
		}
	}
	switch ( word )
	{
	case 0:
		CSprites::GetInstance()->Get(HUB_SPIRE_0)->Draw(x + HUB_LOCATION_HUB_X + 37, y + HUB_LOCATION_HUB_Y + 7, 255);
		break;
	case 1:
		CSprites::GetInstance()->Get(HUB_SPIRE_1)->Draw(x + HUB_LOCATION_HUB_X + 37, y + HUB_LOCATION_HUB_Y + 7, 255);
		break;
	case 2:
		CSprites::GetInstance()->Get(HUB_SPIRE_2)->Draw(x + HUB_LOCATION_HUB_X + 37, y + HUB_LOCATION_HUB_Y + 7, 255);
		break;
	case 3:
		CSprites::GetInstance()->Get(HUB_SPIRE_3)->Draw(x + HUB_LOCATION_HUB_X + 37, y + HUB_LOCATION_HUB_Y + 7, 255);
		break;
	case 4:
		CSprites::GetInstance()->Get(HUB_SPIRE_4)->Draw(x + HUB_LOCATION_HUB_X + 37, y + HUB_LOCATION_HUB_Y + 7, 255);
		break;
	case 5:
		CSprites::GetInstance()->Get(HUB_SPIRE_5)->Draw(x + HUB_LOCATION_HUB_X + 37, y + HUB_LOCATION_HUB_Y + 7, 255);
		break;
	case 6:
		CSprites::GetInstance()->Get(HUB_SPIRE_6)->Draw(x + HUB_LOCATION_HUB_X + 37, y + HUB_LOCATION_HUB_Y + 7, 255);
		break;
	case 7:
		CSprites::GetInstance()->Get(HUB_SPIRE_7)->Draw(x + HUB_LOCATION_HUB_X + 37, y + HUB_LOCATION_HUB_Y + 7, 255);
		break;
	case 8:
		CSprites::GetInstance()->Get(HUB_SPIRE_8)->Draw(x + HUB_LOCATION_HUB_X + 37, y + HUB_LOCATION_HUB_Y + 7, 255);
		break;
	case 9:
		CSprites::GetInstance()->Get(HUB_SPIRE_9)->Draw(x + HUB_LOCATION_HUB_X + 37, y + HUB_LOCATION_HUB_Y + 7, 255);
		break;
	}
	//time
	switch (time1)
	{
	case 0:
		CSprites::GetInstance()->Get(HUB_SPIRE_0)->Draw(x + HUB_LOCATION_HUB_X + 124, y + HUB_LOCATION_HUB_Y + 15, 255);
		break;
	case 1:
		CSprites::GetInstance()->Get(HUB_SPIRE_1)->Draw(x + HUB_LOCATION_HUB_X + 124, y + HUB_LOCATION_HUB_Y + 15, 255);
		break;
	case 2:
		CSprites::GetInstance()->Get(HUB_SPIRE_2)->Draw(x + HUB_LOCATION_HUB_X + 124, y + HUB_LOCATION_HUB_Y + 15, 255);
		break;
	case 3:
		CSprites::GetInstance()->Get(HUB_SPIRE_3)->Draw(x + HUB_LOCATION_HUB_X + 124, y + HUB_LOCATION_HUB_Y + 15, 255);
		break;
	case 4:
		CSprites::GetInstance()->Get(HUB_SPIRE_4)->Draw(x + HUB_LOCATION_HUB_X + 124, y + HUB_LOCATION_HUB_Y + 15, 255);
		break;
	case 5:
		CSprites::GetInstance()->Get(HUB_SPIRE_5)->Draw(x + HUB_LOCATION_HUB_X + 124, y + HUB_LOCATION_HUB_Y + 15, 255);
		break;
	case 6:
		CSprites::GetInstance()->Get(HUB_SPIRE_6)->Draw(x + HUB_LOCATION_HUB_X + 124, y + HUB_LOCATION_HUB_Y + 15, 255);
		break;
	case 7:
		CSprites::GetInstance()->Get(HUB_SPIRE_7)->Draw(x + HUB_LOCATION_HUB_X + 124, y + HUB_LOCATION_HUB_Y + 15, 255);
		break;
	case 8:
		CSprites::GetInstance()->Get(HUB_SPIRE_8)->Draw(x + HUB_LOCATION_HUB_X + 124, y + HUB_LOCATION_HUB_Y + 15, 255);
		break;
	case 9:
		CSprites::GetInstance()->Get(HUB_SPIRE_9)->Draw(x + HUB_LOCATION_HUB_X + 124, y + HUB_LOCATION_HUB_Y + 15, 255);
		break;
	}
	switch (time2)
	{
	case 0:
		CSprites::GetInstance()->Get(HUB_SPIRE_0)->Draw(x + HUB_LOCATION_HUB_X + 132, y + HUB_LOCATION_HUB_Y + 15, 255);
		break;
	case 1:
		CSprites::GetInstance()->Get(HUB_SPIRE_1)->Draw(x + HUB_LOCATION_HUB_X + 132, y + HUB_LOCATION_HUB_Y + 15, 255);
		break;
	case 2:
		CSprites::GetInstance()->Get(HUB_SPIRE_2)->Draw(x + HUB_LOCATION_HUB_X + 132, y + HUB_LOCATION_HUB_Y + 15, 255);
		break;
	case 3:
		CSprites::GetInstance()->Get(HUB_SPIRE_3)->Draw(x + HUB_LOCATION_HUB_X + 132, y + HUB_LOCATION_HUB_Y + 15, 255);
		break;
	case 4:
		CSprites::GetInstance()->Get(HUB_SPIRE_4)->Draw(x + HUB_LOCATION_HUB_X + 132, y + HUB_LOCATION_HUB_Y + 15, 255);
		break;
	case 5:
		CSprites::GetInstance()->Get(HUB_SPIRE_5)->Draw(x + HUB_LOCATION_HUB_X + 132, y + HUB_LOCATION_HUB_Y + 15, 255);
		break;
	case 6:
		CSprites::GetInstance()->Get(HUB_SPIRE_6)->Draw(x + HUB_LOCATION_HUB_X + 132, y + HUB_LOCATION_HUB_Y + 15, 255);
		break;
	case 7:
		CSprites::GetInstance()->Get(HUB_SPIRE_7)->Draw(x + HUB_LOCATION_HUB_X + 132, y + HUB_LOCATION_HUB_Y + 15, 255);
		break;
	case 8:
		CSprites::GetInstance()->Get(HUB_SPIRE_8)->Draw(x + HUB_LOCATION_HUB_X + 132, y + HUB_LOCATION_HUB_Y + 15, 255);
		break;
	case 9:
		CSprites::GetInstance()->Get(HUB_SPIRE_9)->Draw(x + HUB_LOCATION_HUB_X + 132, y + HUB_LOCATION_HUB_Y + 15, 255);
		break;
	}
	switch (time3)
	{
	case 0:
		CSprites::GetInstance()->Get(HUB_SPIRE_0)->Draw(x + HUB_LOCATION_HUB_X + 140, y + HUB_LOCATION_HUB_Y + 15, 255);
		break;
	case 1:
		CSprites::GetInstance()->Get(HUB_SPIRE_1)->Draw(x + HUB_LOCATION_HUB_X + 140, y + HUB_LOCATION_HUB_Y + 15, 255);
		break;
	case 2:
		CSprites::GetInstance()->Get(HUB_SPIRE_2)->Draw(x + HUB_LOCATION_HUB_X + 140, y + HUB_LOCATION_HUB_Y + 15, 255);
		break;
	case 3:
		CSprites::GetInstance()->Get(HUB_SPIRE_3)->Draw(x + HUB_LOCATION_HUB_X + 140, y + HUB_LOCATION_HUB_Y + 15, 255);
		break;
	case 4:
		CSprites::GetInstance()->Get(HUB_SPIRE_4)->Draw(x + HUB_LOCATION_HUB_X + 140, y + HUB_LOCATION_HUB_Y + 15, 255);
		break;
	case 5:
		CSprites::GetInstance()->Get(HUB_SPIRE_5)->Draw(x + HUB_LOCATION_HUB_X + 140, y + HUB_LOCATION_HUB_Y + 15, 255);
		break;
	case 6:
		CSprites::GetInstance()->Get(HUB_SPIRE_6)->Draw(x + HUB_LOCATION_HUB_X + 140, y + HUB_LOCATION_HUB_Y + 15, 255);
		break;
	case 7:
		CSprites::GetInstance()->Get(HUB_SPIRE_7)->Draw(x + HUB_LOCATION_HUB_X + 140, y + HUB_LOCATION_HUB_Y + 15, 255);
		break;
	case 8:
		CSprites::GetInstance()->Get(HUB_SPIRE_8)->Draw(x + HUB_LOCATION_HUB_X + 140, y + HUB_LOCATION_HUB_Y + 15, 255);
		break;
	case 9:
		CSprites::GetInstance()->Get(HUB_SPIRE_9)->Draw(x + HUB_LOCATION_HUB_X + 140, y + HUB_LOCATION_HUB_Y + 15, 255);
		break;
	}
	switch (number1)
	{
	case 0:
		break;
	case 1:
		CSprites::GetInstance()->Get(HUB_SPIRE_1)->Draw(x + HUB_LOCATION_HUB_X + 132, y + HUB_LOCATION_HUB_Y + 7, 255);
		break;
	case 2:
		CSprites::GetInstance()->Get(HUB_SPIRE_2)->Draw(x + HUB_LOCATION_HUB_X + 132, y + HUB_LOCATION_HUB_Y + 7, 255);
		break;
	case 3:
		CSprites::GetInstance()->Get(HUB_SPIRE_3)->Draw(x + HUB_LOCATION_HUB_X + 132, y + HUB_LOCATION_HUB_Y + 7, 255);
		break;
	case 4:
		CSprites::GetInstance()->Get(HUB_SPIRE_4)->Draw(x + HUB_LOCATION_HUB_X + 132, y + HUB_LOCATION_HUB_Y + 7, 255);
		break;
	case 5:
		CSprites::GetInstance()->Get(HUB_SPIRE_5)->Draw(x + HUB_LOCATION_HUB_X + 132, y + HUB_LOCATION_HUB_Y + 7, 255);
		break;
	case 6:
		CSprites::GetInstance()->Get(HUB_SPIRE_6)->Draw(x + HUB_LOCATION_HUB_X + 132, y + HUB_LOCATION_HUB_Y + 7, 255);
		break;
	case 7:
		CSprites::GetInstance()->Get(HUB_SPIRE_7)->Draw(x + HUB_LOCATION_HUB_X + 132, y + HUB_LOCATION_HUB_Y + 7, 255);
		break;
	case 8:
		CSprites::GetInstance()->Get(HUB_SPIRE_8)->Draw(x + HUB_LOCATION_HUB_X + 132, y + HUB_LOCATION_HUB_Y + 7, 255);
		break;
	case 9:
		CSprites::GetInstance()->Get(HUB_SPIRE_9)->Draw(x + HUB_LOCATION_HUB_X + 132, y + HUB_LOCATION_HUB_Y + 7, 255);
		break;
	}
	switch (number2)
	{
	case 0:
		CSprites::GetInstance()->Get(HUB_SPIRE_0)->Draw(x + HUB_LOCATION_HUB_X + 140, y + HUB_LOCATION_HUB_Y + 7, 255);
		break;
	case 1:
		CSprites::GetInstance()->Get(HUB_SPIRE_1)->Draw(x + HUB_LOCATION_HUB_X + 140, y + HUB_LOCATION_HUB_Y + 7, 255);
		break;
	case 2:
		CSprites::GetInstance()->Get(HUB_SPIRE_2)->Draw(x + HUB_LOCATION_HUB_X + 140, y + HUB_LOCATION_HUB_Y + 7, 255);
		break;
	case 3:
		CSprites::GetInstance()->Get(HUB_SPIRE_3)->Draw(x + HUB_LOCATION_HUB_X + 140, y + HUB_LOCATION_HUB_Y + 7, 255);
		break;
	case 4:
		CSprites::GetInstance()->Get(HUB_SPIRE_4)->Draw(x + HUB_LOCATION_HUB_X + 140, y + HUB_LOCATION_HUB_Y + 7, 255);
		break;
	case 5:
		CSprites::GetInstance()->Get(HUB_SPIRE_5)->Draw(x + HUB_LOCATION_HUB_X + 140, y + HUB_LOCATION_HUB_Y + 7, 255);
		break;
	case 6:
		CSprites::GetInstance()->Get(HUB_SPIRE_6)->Draw(x + HUB_LOCATION_HUB_X + 140, y + HUB_LOCATION_HUB_Y + 7, 255);
		break;
	case 7:
		CSprites::GetInstance()->Get(HUB_SPIRE_7)->Draw(x + HUB_LOCATION_HUB_X + 140, y + HUB_LOCATION_HUB_Y + 7, 255);
		break;
	case 8:
		CSprites::GetInstance()->Get(HUB_SPIRE_8)->Draw(x + HUB_LOCATION_HUB_X + 140, y + HUB_LOCATION_HUB_Y + 7, 255);
		break;
	case 9:
		CSprites::GetInstance()->Get(HUB_SPIRE_9)->Draw(x + HUB_LOCATION_HUB_X + 140, y + HUB_LOCATION_HUB_Y + 7, 255);
		break;
	}
}
void Hud::Update()
{
	Game->GetInstance()->GetCamPos(x, y);
	y += Game->GetInstance()->GetScreenHeight() - SEEN_HEIGHT;
	word=PlayScene->GetWord();
	time = PlayScene->GetTime();
	number = PlayScene->GetNumber();
	CMario*  mario = PlayScene->GetPlayer();
	if (mario->GetState() != MARIO_STATE_WALKING_RIGHT || mario->GetState() == MARIO_STATE_WALKING_LEFT)
	{
		if (mario->GetState() == MARIO_STATE_WALKING_RIGHT_FAST || mario->GetState() == MARIO_STATE_WALKING_LEFT_FAST || mario->GetState() == MARIO_FLYLING_SPEED_Y)
		{
			if (abs(mario->vx) > MARIO_WALKING_SPEED_MAX)
			{
				maxv = 6;
			}
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
		else 
		{
			maxv = 0;
		}
	}
	
	if (time>=0)
	{
		time3 = time % 10;
		time2 = (time / 10) % 10;
		time1 = time / 100;
	}
	if (number>=0)
	{
		number1 = number /10;
		number2 = number % 10;
	}
}