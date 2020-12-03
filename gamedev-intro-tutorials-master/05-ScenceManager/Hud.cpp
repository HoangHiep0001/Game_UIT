#include "Hud.h"

Hud::Hud(CPlayScene* Scene)
{
	PlayScene = Scene;
	Game->GetInstance()->GetCamPos(x, y);
	y += Game->GetInstance()->GetScreenHeight() - SEEN_HEIGHT;
	word = PlayScene->GetWord();
	time = PlayScene->GetTime();
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
			for (int i = 0; i < maxv;i++) 
			{
				CSprites::GetInstance()->Get(HUB_SPIRE_ARROW)->Draw(x + HUB_LOCATION_HUB_X + HUB_LOCATION_ARROW_X1+(i)*8, y + HUB_LOCATION_HUB_Y + HUB_LOCATION_ARROW_Y, 255);
			}
			if (maxv >= 6)
			{
				CSprites::GetInstance()->Get(HUB_SPIRE_MAX_P)->Draw(x + HUB_LOCATION_HUB_X + HUB_LOCATION_P_X, y + HUB_LOCATION_HUB_Y + HUB_LOCATION_ARROW_Y, 255);
			}
		}
	}
	CSprites::GetInstance()->Get(drawNumber(word))->Draw(x + HUB_LOCATION_HUB_X + 37, y + HUB_LOCATION_HUB_Y + 7, 255);
	CSprites::GetInstance()->Get(drawNumber(time1))->Draw(x + HUB_LOCATION_HUB_X + 124, y + HUB_LOCATION_HUB_Y + 15, 255);
	CSprites::GetInstance()->Get(drawNumber(time2))->Draw(x + HUB_LOCATION_HUB_X + 132, y + HUB_LOCATION_HUB_Y + 15, 255);
	CSprites::GetInstance()->Get(drawNumber(time3))->Draw(x + HUB_LOCATION_HUB_X + 140, y + HUB_LOCATION_HUB_Y + 15, 255);
	if (number1 != 0)
	{
		CSprites::GetInstance()->Get(drawNumber(number1))->Draw(x + HUB_LOCATION_HUB_X + 132, y + HUB_LOCATION_HUB_Y + 7, 255);
	}
	CSprites::GetInstance()->Get(drawNumber(number2))->Draw(x + HUB_LOCATION_HUB_X + 140, y + HUB_LOCATION_HUB_Y + 7, 255);
	for ( int i = 6; i >=0; i--)
	{
		CSprites::GetInstance()->Get(drawNumber(score[i]))->Draw(x + HUB_LOCATION_HUB_X + 100 - i*8, y + HUB_LOCATION_HUB_Y + 15, 255);
	}
	CSprites::GetInstance()->Get(drawNumber(life1))->Draw(x + HUB_LOCATION_HUB_X + 29, y + HUB_LOCATION_HUB_Y + 15, 255);
	CSprites::GetInstance()->Get(drawNumber(life2))->Draw(x + HUB_LOCATION_HUB_X + 37, y + HUB_LOCATION_HUB_Y + 15, 255);
}



void Hud::Update()
{
	GetScore();
	Game->GetInstance()->GetCamPos(x, y);
	y += Game->GetInstance()->GetScreenHeight() - SEEN_HEIGHT;
	word=PlayScene->GetWord();
	time = PlayScene->GetTime();
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
	if (PlayScene->GetPlayer()->GetCoin_number() >= 0)
	{
		number1 = PlayScene->GetPlayer()->GetCoin_number() /10;
		number2 = PlayScene->GetPlayer()->GetCoin_number() % 10;
	}
	if (PlayScene->GetPlayer()->GetLife() >= 0)
	{
		life1 = PlayScene->GetPlayer()->GetLife() / 10;
		life2 = PlayScene->GetPlayer()->GetLife() % 10;
	}
}

int Hud::drawNumber(int num)
{
	int x = HUB_SPIRE_0;
	switch (num)
	{
	case 1:
		x = HUB_SPIRE_1;
		break;
	case 2:
		x = HUB_SPIRE_2;
		break;
	case 3:
		x = HUB_SPIRE_3;
		break;
	case 4:
		x = HUB_SPIRE_4;
		break;
	case 5:
		x = HUB_SPIRE_5;
		break;
	case 6:
		x = HUB_SPIRE_6;
		break;
	case 7:
		x = HUB_SPIRE_7;
		break;
	case 8:
		x = HUB_SPIRE_8;
		break;
	case 9:
		x = HUB_SPIRE_9;
		break;
	}
	return x;
}

void Hud::GetScore()
{
	for (int i = 0; i <=6; i++)
	{
		int x = 1;
		for (int j = 0; j < i; j++)
		{
			x *= 10;
		}
		score[i] = ((PlayScene->GetPlayer()->GetScore()) / x) % 10;
	}
}