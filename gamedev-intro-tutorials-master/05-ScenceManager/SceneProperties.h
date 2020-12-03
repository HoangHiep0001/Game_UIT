#pragma once
class SceneProperties
{
	bool flag;
	//mario properties
	int life;
	int score;
	int mario_level;
	int mario_apperance;
	float mariox;
	float marioy;

	//scene properties
	int time;
	int coin_numer;

public:
	SceneProperties()
	{
		flag = false;
		life = 0;
		score = 0;
		mario_level = 0;
		mario_apperance = 0;
		mariox = 0;
		marioy = 0;
		time = 0;
		coin_numer = 0;
	};
	void SetSceneProperties(int l, int s,int level, int a,int t,int n)
	{
		life = l;
		score = s;
		mario_level = level;
		mario_apperance = a;
		time = t;
		coin_numer = n;
	}
	void SetMarioPosition(float x, float y)
	{
		mariox = x;
		marioy = y;
	}
	bool GetFlag() { return this->flag; }
	void SetFlag() { flag = true; }
	float GetX() { return mariox; }
	float GetY() { return marioy; }
	int GetLife() { return this->life; }
	int GetScore() { return this->score; }
	int GetLevel() { return this->mario_level; }
	int GetApperance() { return this->mario_apperance; }
	int Gettime() { return this->time; }
	int Getcoin_numer() { return this->coin_numer; }
};

