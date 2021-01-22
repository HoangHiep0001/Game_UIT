#pragma once
#include "GameObject.h"

#define KOOPAS_WALKING_SPEED 0.03f;
#define KOOPAS_JUMP_SPEED_Y 0.25f
#define KOOPAS_GRAVITY 0.001f
#define KOOPAS_TORTOISESHELL 0.15f
#define KOOPAS_VY 0.002f
#define KOOPAS_DIE_VY 0.35f
//BBOX
#define KOOPAS_BBOX_WIDTH 16
#define KOOPAS_BBOX_HEIGHT 27
#define KOOPAS_BBOX_LIVING 15.7
//STATE
#define KOOPAS_STATE_WALKING 0
#define KOOPAS_STATE_FLYLING 1
#define KOOPAS_STATE_TORTOISESHELL_UP 2
#define KOOPAS_STATE_TORTOISESHELL_DOWN 3
#define KOOPAS_STATE_DIE_UP 4
#define KOOPAS_STATE_DIE_DOWN 5
#define KOOPAS_STATE_LIVING_UP 6
#define KOOPAS_STATE_LIVING_DOWN 7
#define KOOPAS_STATE_LIVE_FOOT_UP 8
#define KOOPAS_STATE_LIVE_FOOT_DOWN 9



//ANI
#define KOOPAS_ANI_BULE_WALKING_RIGHT 0
#define KOOPAS_ANI_BULE_WALKING_LEFT 1
#define KOOPAS_ANI_BULE_FLYLING_RIGHT 2
#define KOOPAS_ANI_BULE_FLYLING_LEFT 3
#define KOOPAS_ANI_BULE_TORTOISESHELL_UP 4
#define KOOPAS_ANI_BULE_TORTOISESHELL_DOWN 5
#define KOOPAS_ANI_BULE_DIE_UP 6
#define KOOPAS_ANI_BULE_DIE_DOWN 7
#define KOOPAS_ANI_BULE_LIVE_FOOT_UP 16
#define KOOPAS_ANI_BULE_LIVE_FOOT_DOWN 18

#define KOOPAS_ANI_RED_WALKING_RIGHT 8 
#define KOOPAS_ANI_RED_WALKING_LEFT 9
#define KOOPAS_ANI_RED_FLYLING_RIGHT 10
#define KOOPAS_ANI_RED_FLYLING_LEFT 11
#define KOOPAS_ANI_RED_TORTOISESHELL_UP 12
#define KOOPAS_ANI_RED_TORTOISESHELL_DOWN 13
#define KOOPAS_ANI_RED_DIE_UP 14
#define KOOPAS_ANI_RED_DIE_DOWN 15
#define KOOPAS_ANI_RED_LIVE_FOOT_UP 17
#define KOOPAS_ANI_RED_LIVE_FOOT_DOWN 19


#define KOOPAS_RED 0
#define KOOPAS_BULE 1

#define KOOPAS_JUMP_Y 35
#define KOOPAS_BIG_HOLD 5
#define KOOPAS_SMALL_HOLD 3
#define KOOPAS_TIME_LIVE 4000
#define KOOPAS_TIME_LIVE_FOOT 6000
#define KOOPAS_TIME_LIVING 6000
#define KOOPAS_TIME_DIE 1000
#define KOOPAS_Y 14

#define KOOPAS_SCORE 100
class CKoopas : public CGameObject
{
	DWORD time = 0;
	int apperance;
	int score = KOOPAS_SCORE;
	virtual void Update(DWORD dt, CScene* scene, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	bool ispickup= false;
	bool iskoopas = false;
	float startx, starty;
	float distance_a, distance_b;
	int state_koopas;
	int direction;

public:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void SetStatePoint(int sta) { state_koopas = sta; }
	void SetStartPoint(float x0, float y0) { startx = x0; starty = y0; }
	void SetDistance(float a, float b) { distance_a = a; distance_b = b; }
	void SetDirection(int dir) { direction = dir; }
	float GetDistance_a() {return distance_a;}
	float GetDistance_b() { return distance_b; }
	int GetDirection() { return direction; }
	int GetApperance() { return apperance; }
	CKoopas(int appe);
	bool CheckPosition();
	void SetState(int state);
	void SetIsPick(bool flag) {
		this->ispickup = flag;
	}
	void SetIsKoopas(bool pas) {
		this->iskoopas = pas;
	}
};

