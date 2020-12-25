#pragma once
#include "GameObject.h"
//0.1f
#define FIREBALL_X 0.055f;
#define FIREBALL_Y 0.04f;
//bbox
#define FIREBALL_BBOX_WIDTH 9
#define FIREBALL_BBOX_HEIGHT 9

//state
#define FIREBALL_STATE_UP_RIGHT 100
#define FIREBALL_STATE_UP_LEFT 200
#define FIREBALL_STATE_DOWN_RIGHT 300
#define FIREBALL_STATE_DOWN_LEFT 400

//animation
#define FIREBALL_ANI_LEFT 1
#define FIREBALL_ANI_RIGHT 0

#define FIRE_BALL_ANISET 5

#define FIRE_BALL_MAX_Y	30
#define FIRE_BALL	12
#define TIME_FIRE_BALL	200
class CFireBall : public CGameObject
{
	bool first_time = true;
	float MaxY = 0;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
public:
	CFireBall(int nx);
	virtual void SetState(int state);
	virtual void Update(DWORD dt, CScene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();


};


