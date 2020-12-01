#pragma once
#include "Game.h"
#include "PlayScence.h"
#include "GameObject.h"
class CGame;
class CPlayScene;
// STATE
#define HUB_SPIRE_HUB 1100
#define HUB_SPIRE_ARROW 1101
#define HUB_SPIRE_MAX_P 1102
#define HUB_SPIRE_SUPER_BLACK 1103
#define HUB_SPIRE_0 1104
#define HUB_SPIRE_1 1105
#define HUB_SPIRE_2 1106
#define HUB_SPIRE_3 1107
#define HUB_SPIRE_4 1108
#define HUB_SPIRE_5 1109
#define HUB_SPIRE_6 1110
#define HUB_SPIRE_7 1111
#define HUB_SPIRE_8 1112
#define HUB_SPIRE_9 1113
#define HUB_SPIRE_A 1114
#define HUB_SPIRE_B 1115
#define HUB_SPIRE_C 1116
#define HUB_SPIRE_D 1117
#define HUB_SPIRE_E 1118
#define HUB_SPIRE_F 1119
#define HUB_SPIRE_G 1120
#define HUB_SPIRE_H 1121
#define HUB_SPIRE_I 1122
#define HUB_SPIRE_J 1123
#define HUB_SPIRE_K 1124
#define HUB_SPIRE_L 1125
#define HUB_SPIRE_M 1126
#define HUB_SPIRE_N 1127
#define HUB_SPIRE_O 1128
#define HUB_SPIRE_P 1129
#define HUB_SPIRE_Q 1130
#define HUB_SPIRE_R 1131
#define HUB_SPIRE_S 1132
#define HUB_SPIRE_T 1133
#define HUB_SPIRE_U 1134
#define HUB_SPIRE_V 1135
#define HUB_SPIRE_W 1136
#define HUB_SPIRE_X 1137
#define HUB_SPIRE_Y 1138
#define HUB_SPIRE_Z 1139
#define HUB_SPIRE_MUSHROOMS 1140
#define HUB_SPIRE_TREE 1141
#define HUB_SPIRE_STAR 1142
#define HUB_SPIRE_NETWORK_M 1143
#define HUB_SPIRE_NETWORK_L 1144


// location
#define SEEN_HEIGHT 50 
#define HUB_LOCATION_HUB_X 15
#define HUB_LOCATION_HUB_Y 10
#define HUB_LOCATION_ARROW_X1 52
#define HUB_LOCATION_ARROW_X2 60
#define HUB_LOCATION_ARROW_X3 68
#define HUB_LOCATION_ARROW_X4 76
#define HUB_LOCATION_ARROW_X5 84
#define HUB_LOCATION_ARROW_X6 92
#define HUB_LOCATION_P_X 100
#define HUB_LOCATION_ARROW_Y 7
class Hud
{
	bool isDestroy = false;
	CGame* Game;
	CPlayScene* PlayScene;
	float x, y;
	int word;
	int maxv=0;
	int time;
	int time1;
	int time2;
	int time3;
	int number=0;
	DWORD time_start = 0;
public:
	void Destroy() { this->isDestroy = true; }
	Hud(CPlayScene* Scene);
	void Render();
	void Update();

};

