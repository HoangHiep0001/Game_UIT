#pragma once
#include "GameObject.h"

#define MARIO_WALKING_SPEED		0.15f 
#define MARIO_WALKING_SPEED_MAX	0.2f 
#define MARIO_FLYING_SPEED_X	0.15f 
#define MARIO_ACCELERATION	0.0003f
#define	MARIO_ACCELERATION_STOP	0.0008f
//0.1f
#define MARIO_JUMP_SPEED_Y		0.45f
#define MARIO_FLYLING_SPEED_Y	0.1f
#define MARIO_SMALL_JUMP_SPEED_Y 0.35f
#define MARIO_JUMP_DEFLECT_SPEED 0.2f
#define MARIO_GRAVITY			0.002f
#define MARIO_DIE_DEFLECT_SPEED	 0.5f


//state
#pragma region State
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200
#define MARIO_STATE_JUMP			300
#define MARIO_STATE_DIE				400
#define MARIO_STATE_WALKING_RIGHT_FAST 500
#define MARIO_STATE_WALKING_LEFT_FAST 600
#define MARIO_STATE_SIT	700
#define MARIO_STATE_STOP	800
#define MARIO_STATE_FLY	900
#define MARIO_STATE_ATTACK 1000
#define MARIO_STATE_FLYLING	1100
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
#define MARIO_ANI_SMALL_STOP_IDLE_RIGHT 45
#define MARIO_ANI_SMALL_STOP_IDLE_LEFT 46
#define MARIO_ANI_SMALL_FLY_IDLE_RIGHT 14
#define MARIO_ANI_SMALL_FLY_IDLE_LEFT 15
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

#pragma endregion

#define MARIO_ANI_DIE				8

//level
#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2

//ngoai hinh
#define MARIO_NORMAL 0
#define MARIO_FOX	1
#define MARIO_FIRE	2
#define MARIO_FOX_FIRE	3

//bbox
#define MARIO_BIG_BBOX_WIDTH  15
#define MARIO_BIG_BBOX_HEIGHT 27

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 15

#define MARIO_FOX_BBOX_WIDTH	22
#define MARIO_FOX_BBOX_HEIGHT	28

#define MARIO_UNTOUCHABLE_TIME 5000

#define UPLEVEL_OFFSET	12
#define MARIO_FOX_BBOX_OFFSET 1
#define TIME_STOP_MARIO 400

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
public: 
	CMario(float x = 0.0f, float y = 0.0f);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();

	void SetState(int state);
	void SetLevel(int l) { level = l; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	void Reset();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);

	void UpLevel();
	void ChangeApperance(int apperance);
	DWORD GetTimeStop() { return time_stop; }
	int GetApperance() { return apperance; }
	float GetV() { return this->vx; }
};