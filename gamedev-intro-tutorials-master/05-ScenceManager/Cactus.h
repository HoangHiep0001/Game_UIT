#pragma once
#include "GameObject.h"

#define CACTUS_SPEED_Y	0.07f
#define CACTUS_VY	0.01f
/// BBOX
#define CACTUS_BBOX_ONE_X 16
#define CACTUS_BBOX_ONE_Y 24
#define CACTUS_BBOX_TWO_X 16
#define CACTUS_BBOX_TWO_Y 32

//state
#define CACTUS_STATE_IDE_UP_SONG 5
#define CACTUS_STATE_IDE_UP_SHUT 0
#define CACTUS_STATE_UP 1
#define CACTUS_STATE_DOWN 2
#define CACTUS_STATE_FIRE_UP 3
#define CACTUS_STATE_FIRE_DOWN 4



//ANI
#define CACTUS_RED_ANI_UP_RIGHT 0
#define CACTUS_RED_ANI_UP_LEFT 1
#define CACTUS_RED_ANI_DOWN_RIGHT 2
#define CACTUS_RED_ANI_DOWN_LEFT 3
#define CACTUS_RED_ANI_FIRE_UP_RIGHT 4
#define CACTUS_RED_ANI_FIRE_UP_LEFT 5
#define CACTUS_RED_ANI_FIRE_DOWN_RIGHT 6 
#define CACTUS_RED_ANI_FIRE_DOWN_LEFT 7

#define CACTUS_BULE_ANI_UP_RIGHT 8
#define CACTUS_BULE_ANI_UP_LEFT 9
#define CACTUS_BULE_ANI_DOWN_RIGHT 10
#define CACTUS_BULE_ANI_DOWN_LEFT 11
#define CACTUS_BULE_ANI_FIRE_UP_RIGHT 12
#define CACTUS_BULE_ANI_FIRE_UP_LEFT 13
#define CACTUS_BULE_ANI_FIRE_DOWN_RIGHT 14
#define CACTUS_BULE_ANI_FIRE_DOWN_LEFT 15
#define CACTUS_BULE_IDE_UP_SONG 16
#define CACTUS_BULE_IDE_UP_SHUT 17
// APP
#define CACTUS_RED 0 
#define CACTUS_BULE 1
//type
#define CACTUS_TYPE_IDE 0 
#define CACTUS_TYPE_WALK 1
// NUMBER
#define CACTUS_NUMBER_ONE 0 
#define CACTUS_NUMBER_TWO 1

class CCactus: public CGameObject
{
	int apperance;
	int type;
	int number;
	bool isSpawnFireBall = false;
	int start_y;

	int sewer_pipes;

	float pipes_y;

	DWORD time_die = 0;
	DWORD time = 0;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, CScene* scene, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

public:
	virtual void SetNumber(int num) { number = num; }
	int GetApperance() { return apperance; }
	int GetSewerPipes() { return sewer_pipes; }
	int GetPipes() { return pipes_y; }
	int GetType() { return type; }
	CCactus(int appe,int stype,int sewer,float pipes);
	virtual void SetState(int state);
	int GetStartY() { return this->start_y; }
	void SetStartY(int y) { this->start_y = y; }
};

