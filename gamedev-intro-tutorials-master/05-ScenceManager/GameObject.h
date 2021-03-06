#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>

#include "Sprites.h"
#include "Animations.h"
#include "Scence.h"

using namespace std;

#define ID_TEX_BBOX -100		// special texture to draw object bounding box
#define SIT_BBOX_OFFSET 9
#define TIAL_BBOX_OFFSET 5
#define START_BBOX_OFFSET 3
class CGameObject;
typedef CGameObject * LPGAMEOBJECT;

struct CCollisionEvent;
typedef CCollisionEvent * LPCOLLISIONEVENT;
struct CCollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;
	
	int dx, dy;		// *RELATIVE* movement distance between this object and obj

	CCollisionEvent(float t, float nx, float ny, float dx = 0, float dy = 0, LPGAMEOBJECT obj = NULL) 
	{ 
		this->t = t; 
		this->nx = nx; 
		this->ny = ny;
		this->dx = dx;
		this->dy = dy;
		this->obj = obj; 
	}

	static bool compare(const LPCOLLISIONEVENT &a, LPCOLLISIONEVENT &b)
	{
		return a->t < b->t;
	}
};


class CGameObject
{
public:
	float x; 
	float y;

	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	float vx;
	float vy;

	int nx;	
	int ny;
	
	int colum;
	int row;

	int state;

	bool isSit;
	bool isTail;
	bool isIntro;
	bool isStatemario;
	DWORD dt; 

	RECT Bound;

	LPANIMATION_SET animation_set;
	bool isDestroy = false;
	bool isQuestionBroken = false;

	bool isAlwaysUpdate = false;

public: 
	void Destroy() { this->isDestroy = true; }
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetPosition(float &x, float &y) { x = this->x; y = this->y; }
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }

	void SetIsAlwaysUpdate(bool x) { this->isAlwaysUpdate = x; }
	bool GetIsAlwaysUpdate() { return this->isAlwaysUpdate; }

	int GetState() { return this->state; }
	void SetColum(int colum) {this->colum = colum;}
	void SetRow(int row) { this->row = row; }
	int GetColum() { return this->colum; }
	int GetRow() { return this->row; }
	void RenderBoundingBox();

	void SetAnimationSet(LPANIMATION_SET ani_set) { animation_set = ani_set; }

	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT> &coEvents, 
		vector<LPCOLLISIONEVENT> &coEventsResult, 
		float &min_tx, 
		float &min_ty, 
		float &nx, 
		float &ny, 
		float &rdx, 
		float &rdy);

	CGameObject();

	bool AABB(float l, float t, float r, float b, float l1, float t1, float r1, float b1);

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Update(DWORD dt,CScene* scene, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render() = 0;
	virtual void SetState(int state) { this->state = state; }
	bool  CheckInCamera();
	~CGameObject();
};

