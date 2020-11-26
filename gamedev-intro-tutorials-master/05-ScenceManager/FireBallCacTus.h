#include "GameObject.h"
//0.1f
#define FIREBALL_FLY_TIME 1200;

//bbox
#define FIREBAL_CACTUS_BBOX_WIDTH 9
#define FIREBAL_CACTUS_BBOX_HEIGHT 9

//state
#define FIREBAL_CACTUS_STATE_UP_RIGHT 100
#define FIREBAL_CACTUS_STATE_UP_LEFT 200
#define FIREBAL_CACTUS_STATE_DOWN_RIGHT 300
#define FIREBAL_CACTUS_STATE_DOWN_LEFT 400

//animation
#define FIREBAL_CACTUS_ANI_LEFT 1
#define FIREBAL_CACTUS_ANI_RIGHT 0

#define FIRE_BALL_ANISET 5

#define FIRE_BALL_MAX_Y	30
#define FIRE_BALL	12
#define TIME_FIRE_BALL	120
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

