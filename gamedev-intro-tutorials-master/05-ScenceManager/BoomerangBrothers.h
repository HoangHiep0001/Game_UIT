//#pragma once
//#include "GameObject.h"
//
//#define BOOMERANG_BROTHERS_WALKING_SPEED 0.035f;
//#define BOOMERANG_BROTHERS_GRAVITY			0.001f
//
//#define BOOMERANG_BROTHERS_BBOX_WIDTH 16
//#define BOOMERANG_BROTHERS_BBOX_HEIGHT 24
//
//// state
//#define BOOMERANG_BROTHERS_STATE_LEFT 0
//#define BOOMERANG_BROTHERS_STATE_RIGHT 1
//
//// ani
//#define BOOMERANG_BROTHERS_ANI_RED_LEFT 0
//#define BOOMERANG_BROTHERS_ANI_RED_RIGHT 1
//
//
//
//
//#define BOOMERANG_BROTHERS_TIME_DIE 300
//#define BOOMERANG_BROTHERS_TIME_WALK 800
//#define BOOMERANG_BROTHERS_TIME_JUMP 200
//#define BOOMERANG_BROTHERS_SCORE 100
//class CBoomerangBrothers : public CGameObject
//{
//	int apperance;
//	int score = BOOMERANG_BROTHERS_SCORE;
//	DWORD time_die = 0;
//	DWORD time = 0;
//	float startx, starty;
//	int state_goomba;
//	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
//	virtual void Update(DWORD dt, CScene* scene, vector<LPGAMEOBJECT>* coObjects);
//	virtual void Render();
//
//public:
//	void SetStartPoint(float x0, float y0) { startx = x0; starty = y0; }
//
//	void SetStatePoint(int sta) { state_goomba = sta; }
//	int GetApperance() { return apperance; }
//	CBoomerangBrothers();
//	virtual void SetState(int state);
//	int GetScore() { return this->score; }
//};
