#pragma once
#include "GameObject.h"

#define GOOMBA_WALKING_SPEED 0.01f;
#define GOOMBA_JUMP_FLY_SPEED_Y	0.3f
#define GOOMBA_JUMP_SPEED_Y	0.05f
#define GOOMBA_GRAVITY			0.001f

#define GOOMBA_BBOX_WING 20
#define GOOMBA_BBOX_FLYING_Y 24
#define GOOMBA_BBOX_X_Y 16
#define GOOMBA_BBOX_Y 7

// state
#define GOOMBA_STATE_WALKING 0
#define GOOMBA_STATE_FLYLING 1
#define GOOMBA_STATE_WALKING_WING 2
#define GOOMBA_STATE_DIE 3

// ani
#define GOOMBA_ANI_RED_WALKING 4
#define GOOMBA_ANI_RED_FLYLING 5
#define GOOMBA_ANI_RED_WALKING_WING 6
#define GOOMBA_ANI_RED_DIE 7


#define GOOMBA_ANI_THERE_WALKING 0
#define GOOMBA_ANI_THERE_FLYLING 1
#define GOOMBA_ANI_THERE_WALKING_WING 2
#define GOOMBA_ANI_THERE_DIE 3


// APP
#define GOOMBA_RED 0
#define GOOMBA_THERE 1

#define GOOMBA_TIME_DIE 200
#define GOOMBA_TIME_WALK 800
#define GOOMBA_TIME_JUMP 200

class CGoomba : public CGameObject
{
	int apperance;

	DWORD time_die = 0;
	DWORD time = 0;
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, CScene* scene,vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();

public: 	
	int GetApperance() { return apperance; }
	CGoomba(int appe);
	virtual void SetState(int state);
	void Updateflyling();
};