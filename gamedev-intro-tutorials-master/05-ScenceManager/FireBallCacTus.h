#include "GameObject.h"
//0.1f
#define FIREBALL_FLY_TIME 1200;

//bbox
#define FIREBALL_CACTUS_BBOX_WIDTH 9
#define FIREBALL_CACTUS_BBOX_HEIGHT 9

//state
#define FIREBALL_CACTUS_STATE_UP_RIGHT 100
#define FIREBALL_CACTUS_STATE_UP_LEFT 200
#define FIREBALL_CACTUS_STATE_DOWN_RIGHT 300
#define FIREBALL_CACTUS_STATE_DOWN_LEFT 400

//animation
#define FIREBALL_CACTUS_ANI_LEFT 1
#define FIREBALL_CACTUS_ANI_RIGHT 0

#define FIRE_BALL_ANISET 5

#define FIREBALL_CACTUS_BALL	12

class CFireBallCacTus : public CGameObject
{
	bool first_time = true;
	float MaxY = 0;
public:
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	CFireBallCacTus(int dir);
	virtual void SetState(int state);
	virtual void Update(DWORD dt, CScene* scene, vector<LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();


};

