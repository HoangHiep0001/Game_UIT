#pragma once
#include "GameObject.h"
#include "FireBall.h"
#include"Game.h"

#define MARIO_WALKING_SPEED		0.15f 
#define MARIO_WALKING_SPEED_MAX	0.3f 
#define MARIO_FLYING_SPEED_X	0.15f 
#define MARIO_LANDING_SPEED_X	0.15f
#define MARIO_ACCELERATION	0.0003f
#define	MARIO_ACCELERATION_STOP	0.0008f

//0.1f
#define MARIO_BIG_JUMP_SPEED_Y	0.25f
#define MARIO_SMALL_JUMP_SPEED_Y 0.25f
#define MARIO_JUMP_SPEED_Y_MAX	0.25f
#define MARIO_FLYLING_SPEED_Y	0.1f
#define MARIO_LANGDING_SPEED_Y	0.03f
#define MARIO_JUMP_DEFLECT_SPEED 0.25f
#define MARIO_GRAVITY			0.002f
#define MARIO_DIE_DEFLECT_SPEED	 0.5f
#define MARIO_FIRE_JUMP_SPEED_Y	0.45f

//state
#pragma region State
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200
#define MARIO_STATE_JUMP			300
#define MARIO_STATE_JUMP_MAX 1600
#define MARIO_STATE_DIE				400
#define MARIO_STATE_WALKING_RIGHT_FAST 500
#define MARIO_STATE_WALKING_LEFT_FAST 600
#define MARIO_STATE_SIT	700
#define MARIO_STATE_STOP	800
#define MARIO_STATE_FLY	900
#define MARIO_STATE_ATTACK 1000
#define MARIO_STATE_FLYLING	1100
#define MARIO_STATE_LANDING	1200
#define MARIO_STATE_HOLD 1300
#define MARIO_STATE_FIRE_BALL 1400
#define MARIO_STATE_FIRE_BALL_DOUBLE 1500
#define MARIO_STATE_STONE_KOOPAS 1700

#pragma endregion
//animation
#pragma region Mario_small
#define MARIO_ANI_SMALL_IDLE_RIGHT		2
#define MARIO_ANI_SMALL_IDLE_LEFT			3
#define MARIO_ANI_SMALL_WALKING_RIGHT		6
#define MARIO_ANI_SMALL_WALKING_LEFT		7
#define MARIO_ANI_SMALL_WALKING_FAST_RIGHT 35
#define MARIO_ANI_SMALL_WALKING_FAST_LEFT 36
#define MARIO_ANI_SMALL_JUMP_IDLE_RIGHT 17
#define MARIO_ANI_SMALL_JUMP_IDLE_LEFT 18
#define MARIO_ANI_SMALL_STOP_IDLE_RIGHT 15
#define MARIO_ANI_SMALL_STOP_IDLE_LEFT 16
#define MARIO_ANI_SMALL_FLY_IDLE_RIGHT 45
#define MARIO_ANI_SMALL_FLY_IDLE_LEFT 46
#define MARIO_ANI_SMALL_HOLD_RIGHT 93
#define MARIO_ANI_SMALL_HOLD_LEFT 94
#define MARIO_ANI_SMALL_STONE_KOOPAS_RIGHT 107
#define MARIO_ANI_SMALL_STONE_KOOPAS_LEFT 108
#define MARIO_ANI_SMALL_START 113
#pragma endregion

#pragma region Mario Big
#define MARIO_ANI_BIG_IDLE_RIGHT		0
#define MARIO_ANI_BIG_IDLE_LEFT			1
#define MARIO_ANI_BIG_WALKING_RIGHT			4
#define MARIO_ANI_BIG_WALKING_LEFT			5
#define MARIO_ANI_BIG_WALKING_FAST_RIGHT 37
#define MARIO_ANI_BIG_WALKING_FAST_LEFT 38
#define MARIO_ANI_BIG_JUMP_IDLE_RIGHT 11
#define MARIO_ANI_BIG_JUMP_IDLE_LEFT 12
#define MARIO_ANI_BIG_SIT_RIGHT 10
#define MARIO_ANI_BIG_SIT_LEFT 9
#define MARIO_ANI_BIG_STOP_IDLE_RIGHT 13
#define MARIO_ANI_BIG_STOP_IDLE_LEFT 14
#define MARIO_ANI_BIG_FLY_IDLE_RIGHT 41
#define MARIO_ANI_BIG_FLY_IDLE_LEFT 42
#define MARIO_ANI_BIG_HOLD_RIGHT 89
#define MARIO_ANI_BIG_HOLD_LEFT 90
#define MARIO_ANI_BIG_STONE_KOOPAS_RIGHT 103
#define MARIO_ANI_BIG_STONE_KOOPAS_LEFT 104
#define MARIO_ANI_BIG_START 114
#pragma endregion

#pragma region Mario Big fox
#define MARIO_ANI_BIG_FOX_IDLE_RIGHT 19
#define MARIO_ANI_BIG_FOX_IDLE_LEFT 20
#define MARIO_ANI_BIG_FOX_WALKING_RIGHT 21
#define MARIO_ANI_BIG_FOX_WALKING_LEFT 22
#define MARIO_ANI_BIG_FOX_WALKING_FAST_RIGHT 39
#define MARIO_ANI_BIG_FOX_WALKING_FAST_LEFT 40
#define MARIO_ANI_BIG_FOX_JUMP_IDLE_RIGHT 25
#define MARIO_ANI_BIG_FOX_JUMP_IDLE_LEFT 26
#define MARIO_ANI_BIG_FOX_SIT_RIGHT 23
#define MARIO_ANI_BIG_FOX_SIT_LEFT 24
#define MARIO_ANI_BIG_FOX_STOP_IDLE_RIGHT 27
#define MARIO_ANI_BIG_FOX_STOP_IDLE_LEFT 28
#define MARIO_ANI_BIG_FOX_FLY_IDLE_RIGHT 31
#define MARIO_ANI_BIG_FOX_FLY_IDLE_LEFT 32
#define MARIO_ANI_BIG_FOX_FLYLING_IDLE_RIGHT 85 
#define MARIO_ANI_BIG_FOX_FLYLING_IDLE_LEFT 86
#define MARIO_ANI_BIG_FOX_ATTACK_IDLE_RIGHT 33
#define MARIO_ANI_BIG_FOX_ATTACK_IDLE_LEFT 34
#define MARIO_ANI_BIG_FOX_HOLD_RIGHT 91
#define MARIO_ANI_BIG_FOX_HOLD_LEFT 92
#define MARIO_ANI_BIG_FOX_STONE_KOOPAS_RIGHT 105
#define MARIO_ANI_BIG_FOX_STONE_KOOPAS_LEFT 106
#define MARIO_ANI_BIG_FOX_START 115
#pragma endregion

#pragma region Mario big fire
#define MARIO_ANI_BIG_FIRE_IDLE_RIGHT 49
#define MARIO_ANI_BIG_FIRE_IDLE_LEFT	50
#define MARIO_ANI_BIG_FIRE_WALKING_RIGHT	51
#define MARIO_ANI_BIG_FIRE_WALKING_LEFT			52
#define MARIO_ANI_BIG_FIRE_WALKING_FAST_RIGHT 61
#define MARIO_ANI_BIG_FIRE_WALKING_FAST_LEFT 62
#define MARIO_ANI_BIG_FIRE_JUMP_IDLE_RIGHT 55
#define MARIO_ANI_BIG_FIRE_JUMP_IDLE_LEFT 56
#define MARIO_ANI_BIG_FIRE_SIT_RIGHT 54
#define MARIO_ANI_BIG_FIRE_SIT_LEFT 53
#define MARIO_ANI_BIG_FIRE_STOP_IDLE_RIGHT 59
#define MARIO_ANI_BIG_FIRE_STOP_IDLE_LEFT 60
#define MARIO_ANI_BIG_FIRE_FLY_IDLE_RIGHT 63
#define MARIO_ANI_BIG_FIRE_FLY_IDLE_LEFT 64
#define MARIO_ANI_BIG_FIRE_HOLD_RIGHT 95
#define MARIO_ANI_BIG_FIRE_HOLD_LEFT 96
#define MARIO_ANI_BIG_FIRE_BALL_RIGHT 99
#define MARIO_ANI_BIG_FIRE_BALL_LEFT 100
#define MARIO_ANI_BIG_FIRE_BALL_DOUBLE_RIGHT 101
#define MARIO_ANI_BIG_FIRE_BALL_DOUBLE_LEFT 102
#define MARIO_ANI_BIG_FIRE_STONE_KOOPAS_RIGHT 109
#define MARIO_ANI_BIG_FIRE_STONE_KOOPAS_LEFT 110
#define MARIO_ANI_BIG_FIRE_START 116
#pragma endregion 

#pragma region Mario big fox fire
#define MARIO_ANI_BIG_FOX_FIRE_IDLE_RIGHT		65
#define MARIO_ANI_BIG_FOX_FIRE_IDLE_LEFT			66
#define MARIO_ANI_BIG_FOX_FIRE_WALKING_RIGHT			67
#define MARIO_ANI_BIG_FOX_FIRE_WALKING_LEFT			68
#define MARIO_ANI_BIG_FOX_FIRE_WALKING_FAST_RIGHT 77
#define MARIO_ANI_BIG_FOX_FIRE_WALKING_FAST_LEFT 78
#define MARIO_ANI_BIG_FOX_FIRE_JUMP_IDLE_RIGHT 71
#define MARIO_ANI_BIG_FOX_FIRE_JUMP_IDLE_LEFT 72
#define MARIO_ANI_BIG_FOX_FIRE_SIT_RIGHT 70
#define MARIO_ANI_BIG_FOX_FIRE_SIT_LEFT 69
#define MARIO_ANI_BIG_FOX_FIRE_STOP_IDLE_RIGHT 75
#define MARIO_ANI_BIG_FOX_FIRE_STOP_IDLE_LEFT 76
#define MARIO_ANI_BIG_FOX_FIRE_FLY_IDLE_RIGHT 79
#define MARIO_ANI_BIG_FOX_FIRE_FLY_IDLE_LEFT 80
#define MARIO_ANI_BIG_FOX_FIRE_FLYLING_IDLE_RIGHT 87
#define MARIO_ANI_BIG_FOX_FIRE_FLYLING_IDLE_LEFT 88
#define MARIO_ANI_BIG_FOX_FIRE_ATTACK_IDLE_RIGHT 81
#define MARIO_ANI_BIG_FOX_FIRE_ATTACK_IDLE_LEFT 82
#define MARIO_ANI_BIG_FOX_FIRE_HOLD_RIGHT 97
#define MARIO_ANI_BIG_FOX_FIRE_HOLD_LEFT 98
#define MARIO_ANI_BIG_FOX_FIRE_STONE_KOOPAS_RIGHT 111
#define MARIO_ANI_BIG_FOX_FIRE_STONE_KOOPAS_LEFT 112
#define MARIO_ANI_BIG_FOX_FIRE_START 117
#pragma endregion

#define MARIO_ANI_DIE 8

//level
#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2

//APP
#define MARIO_NORMAL 0
#define MARIO_FOX	1
#define MARIO_FIRE	2
#define MARIO_FOX_FIRE	3

//bbox
#define MARIO_BIG_BBOX_WIDTH  16
#define MARIO_BIG_BBOX_HEIGHT 27

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 15

#define MARIO_FOX_BBOX_WIDTH	21
#define MARIO_FOX_BBOX_HEIGHT	28

#define MARIO_UNTOUCHABLE_TIME 5000

#define UPLEVEL_OFFSET	12
#define MARIO_FOX_BBOX_OFFSET_Y 1
#define MARIO_FOX_BBOX_OFFSET_X 5 

#define TIME_STOP_MARIO 400
#define TIME_FLYLING_MARIO	800
#define TIME_JUMP_MARIO 220

#define CHECK_FAME_FIRE 1

class CMario : public CGameObject
{
	int apperance;
	int level;
	int untouchable;
	DWORD untouchable_start;

	float start_x;			// initial position of Mario at scene
	float start_y; 
	
	float a; //gia toc
	float a_stop; // gia toc ham~

	DWORD time_stop;
	DWORD time_fly;

	bool isSpawnShot = false;
	DWORD time_doubleshot = 0;
	
	bool isAttack = false;

	bool pickingup = false;

	//fireball
	bool isFireBall = false;
	bool isSpawnFireBall = false;
	DWORD time_jump = 0;

	int CountFireball = 0;

	bool isP = false;
	DWORD isP_time = 0;
	int coin_number;
	int score;
	int life;
public: 
	int GetScore() { return this->score; }
	int GetLife() { return this->life; }
	int GetCoin_number() { return this->coin_number; }
	void SetCoin_number(int coin) { coin_number = coin; }
	void SetScore(int core) { score = core; }
	DWORD GetTimeJump() { return this->time_jump; }
	bool GetIsFireBall() { return this->isFireBall; }
	CMario(float x = 0.0f, float y = 0.0f);
	virtual void Update(DWORD dt, CScene* scene, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();

	void SetState(int state);
	void SetLevel(int l) { level = l; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	void Reset();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);

	void SetIsP(bool P) { isP = P; }
	bool GetIsP() { return this->isP; }

	void UpLevel();
	void ChangeApperance(int apperance);
	DWORD GetTimeStop() { return time_stop; }
	DWORD GetTimeFly() { return time_fly; }
	int GetApperance() { return apperance; }
	int GetLevel() { return level; }
	float GetV() { return this->vx; }
	int GetNx() { return this->nx; }
	void ResetTimeFly() { time_fly = 0; }
	bool GetIsAttack() { return this->isAttack; }
	bool CheckLastFrameAttack();
	void SetPick(bool x) { pickingup = x; }
	bool GetPick() { return this->pickingup; }
	bool CheckFrameFireBall();
	bool CheckFrameFireBallDouble();
	int GetCountFireBall() { return this->CountFireball; }
	void SetCountFireBall(int count) { this->CountFireball = count; }

	void SetMarioProperties()
	{
		this->level = CGame::GetInstance()->GetProperties()->GetLevel();
		this->apperance = CGame::GetInstance()->GetProperties()->GetApperance();
		this->score = CGame::GetInstance()->GetProperties()->GetScore();
		this->life = CGame::GetInstance()->GetProperties()->GetLife();
		this->coin_number = CGame::GetInstance()->GetProperties()->GetCoin_numer();
	}
};