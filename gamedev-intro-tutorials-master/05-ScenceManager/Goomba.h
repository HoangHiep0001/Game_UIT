#pragma once
#include "GameObject.h"

#define GOOMBA_WALKING_SPEED 0.03f;
#define GOOMBA_JUMP_FLY_SPEED_Y	0.3f
#define GOOMBA_JUMP_SPEED_Y	0.25f
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
#define GOOMBA_STATE_WALKING_DOWN 4
#define GOOMBA_STATE_FLYLING_DOWN 5
#define GOOMBA_STATE_WALKING_WING_DOWN 6
// ani
#define GOOMBA_ANI_RED_WALKING 4
#define GOOMBA_ANI_RED_FLYLING 5
#define GOOMBA_ANI_RED_WALKING_WING 6
#define GOOMBA_ANI_RED_DIE 7
#define GOOMBA_ANI_RED_WALKING_DOWN 11
#define GOOMBA_ANI_RED_FLYLING_DOWN 12
#define GOOMBA_ANI_RED_WALKING_WING_DOWN 13

#define GOOMBA_ANI_THERE_WALKING 0
#define GOOMBA_ANI_THERE_FLYLING 1
#define GOOMBA_ANI_THERE_WALKING_WING 2
#define GOOMBA_ANI_THERE_DIE 3
#define GOOMBA_ANI_THERE_WALKING_DOWN 8
#define GOOMBA_ANI_THERE_FLYLING_DOWN 9
#define GOOMBA_ANI_THERE_WALKING_WING_DOWN 10


// APP
#define GOOMBA_RED 0
#define GOOMBA_THERE 1

#define GOOMBA_TIME_DIE 300
#define GOOMBA_TIME_WALK 800
#define GOOMBA_TIME_JUMP 200
#define GOOMBA_SCORE 100
class CGoomba : public CGameObject
{
	int apperance;
	int score = GOOMBA_SCORE;
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
	int GetScore() { return this->score; }
};