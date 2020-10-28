#pragma once
#include "GameObject.h"

#define MARIO_WALKING_SPEED		0.15f 
#define MARIO_WALKING_SPEED_MAX	0.25f 
#define MARIO_ACCELERATION	0.0003f
//0.1f
#define MARIO_JUMP_SPEED_Y		0.45f
#define MARIO_SMALL_JUMP_SPEED_Y 0.35f
#define MARIO_JUMP_DEFLECT_SPEED 0.2f
#define MARIO_GRAVITY			0.002f
#define MARIO_DIE_DEFLECT_SPEED	 0.5f


//state
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200
#define MARIO_STATE_JUMP			300
#define MARIO_STATE_DIE				400
#define MARIO_STATE_WALKING_RIGHT_FAST 500
#define MARIO_STATE_WALKING_LEFT_FAST 600
#define MARIO_STATE_SIT	700

//animation

#define MARIO_ANI_SMALL_IDLE_RIGHT		2
#define MARIO_ANI_SMALL_IDLE_LEFT			3
#define MARIO_ANI_SMALL_WALKING_RIGHT		6
#define MARIO_ANI_SMALL_WALKING_LEFT		7
#define MARIO_ANI_SMALL_WALKING_FAST_RIGHT 35
#define MARIO_ANI_SMALL_WALKING_FAST_LEFT 36
#define MARIO_ANI_SMALL_JUMP_IDLE_RIGHT 17
#define MARIO_ANI_SMALL_JUMP_IDLE_LEFT 18


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

#define MARIO_ANI_BIG_FOX_IDLE_RIGHT 19
#define MARIO_ANI_BIG_FOX_IDLE_LEFT 20
#define MARIO_ANI_BIG_FOX_WALKING_RIGHT 21
#define MARIO_ANI_BIG_FOX_WALKING_LEFT 22
#define MARIO_ANI_BIG_FOX_WALKING_FAST_RIGHT 39
#define MARIO_ANI_BIG_FOX_WALKING_FAST_LEFT 40
#define MARIO_ANI_BIG_FOX_JUMP_IDLE_RIGHT 27
#define MARIO_ANI_BIG_FOX_JUMP_IDLE_LEFT 26
#define MARIO_ANI_BIG_FOX_SIT_RIGHT 23
#define MARIO_ANI_BIG_FOX_SIT_LEFT 24

#define MARIO_ANI_DIE				8

//level
#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2

//ngoai hinh
#define MARIO_NORMAL 0
#define MARIO_FOX	1

//bbox
#define MARIO_BIG_BBOX_WIDTH  15
#define MARIO_BIG_BBOX_HEIGHT 27

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 15

#define MARIO_UNTOUCHABLE_TIME 5000

#define UPLEVEL_OFFSET	12

class CMario : public CGameObject
{
	int apperance;
	int level;
	int untouchable;
	DWORD untouchable_start;

	float start_x;			// initial position of Mario at scene
	float start_y; 
	
	float a; //gia toc
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
};