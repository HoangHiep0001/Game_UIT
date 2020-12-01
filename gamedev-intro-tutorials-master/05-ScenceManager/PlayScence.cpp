#include <iostream>
#include <fstream>
#include "Map.h"
#include "PlayScence.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include"Ground.h"
#include "Coin.h"
#include "FireBall.h"
#include "QuestionMark.h"
#include "Mushrooms.h"
#include "ItemLeaves.h"
#include "Cactus.h"
#include "SewerPipes.h"
#include "ItemCoin.h"
#include "ItemSign.h"
#include "CTree.h"
using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath, int word, int time):CScene(id, filePath, word, time)
{
	key_handler = new CPlayScenceKeyHandler(this);
	time_start = GetTickCount64();
}

/*
	Load scene resources from scene file (textures, sprites, animations and objects)
	See scene1.txt, scene2.txt for detail format specification
*/

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TEXTURES 2
#define SCENE_SECTION_SPRITES 3
#define SCENE_SECTION_ANIMATIONS 4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_OBJECTS	6
#define SCENE_SECTION_TILEMAP 7

#define OBJECT_TYPE_MARIO	0
#define OBJECT_TYPE_BRICK	1
#define OBJECT_TYPE_GOOMBA	2
#define OBJECT_TYPE_KOOPAS	3
#define OBJECT_TYPE_GROUND	4
#define OBJECT_TYPE_CAMERA	5
#define OBJECT_TYPE_COIN	7
#define OBJECT_TYPE_MAP_CAMERA 6
#define OBJECT_TYPE_QUESTIONMARK	8
#define OBJECT_TYPE_MUSHROOMS	9
#define OBJECT_TYPE_LEAVES 10
#define OBJECT_TYPE_ITEM_COIN	11
#define OBJECT_TYPE_ITEM_SIGN	12
#define OBJECT_TYPE_CACTUS 20
#define OBJECT_TYPE_TREE 21
#define OBJECT_TYPE_SEWERPIPES 40
#define OBJECT_TYPE_PORTAL	50


#define MAX_SCENE_LINE 1024



void CPlayScene::_ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return; // skip invalid lines

	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());

	CTextures::GetInstance()->Add(texID, path.c_str(), D3DCOLOR_XRGB(R, G, B));
}

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return; 
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i+1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}



void CPlayScene::_ParseSection_ANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; // skip invalid lines - an animation set must at least id and one animation id

	int ani_set_id = atoi(tokens[0].c_str());

	LPANIMATION_SET s = new CAnimationSet();

	CAnimations *animations = CAnimations::GetInstance();

	for (int i = 1; i < tokens.size(); i++)
	{
		int ani_id = atoi(tokens[i].c_str());
		
		LPANIMATION ani = animations->Get(ani_id);
		s->push_back(ani);
	}
	CAnimationSets::GetInstance()->Add(ani_set_id, s);
}

/*
	Parse a line in section [OBJECTS] 
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());
	int ani_set_id = atoi(tokens[3].c_str());

	CAnimationSets * animation_sets = CAnimationSets::GetInstance();

	CGameObject *obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
		if (player!=NULL) 
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = new CMario(x,y); 
		player = (CMario*)obj;  
		
		DebugOut(L"[INFO] Player object created!\n");
		break;
	case OBJECT_TYPE_GOOMBA:
	{
		int app = atof(tokens[4].c_str());
		int state = atof(tokens[5].c_str());
		obj = new CGoomba(app);
		obj->SetState(state); 
	}
	break;
	case OBJECT_TYPE_BRICK:
	{
		int state = atof(tokens[4].c_str());
		obj = new CBrick();
		CBrick* q = dynamic_cast<CBrick*>(obj);
		int id = atof(tokens[5].c_str());
		q->SetItemID(id);
		int count = atof(tokens[6].c_str());
		q->SetItemCount(count);
		int nstate = atof(tokens[7].c_str());
		q->SetItemState(nstate);
		obj->SetState(state);
	}
	break;
	case OBJECT_TYPE_KOOPAS:
	{ 

		int app = atof(tokens[4].c_str());
		int state = atof(tokens[5].c_str());
		obj = new CKoopas(app);
		obj->SetState(state);
	}
	break;
	case OBJECT_TYPE_COIN:
	{
		obj = new CCoin();	
	}
	break;
	case OBJECT_TYPE_ITEM_COIN:
	{
		int nstate = atof(tokens[4].c_str());
		obj = new CItemCoin(nstate);
	}
	break;
	case OBJECT_TYPE_QUESTIONMARK:
	{
		int state = atof(tokens[4].c_str());
		obj = new CQuestionMark();
		CQuestionMark* q = dynamic_cast<CQuestionMark*>(obj);
		q->SetStartY(y);
		int id = atof(tokens[5].c_str());
		q->SetItemID(id);
		int count = atof(tokens[6].c_str());
		q->SetItemCount(count);
		obj->SetState(state);
		break;
	}
	case OBJECT_TYPE_GROUND: 
	{
		float w = atof(tokens[4].c_str());
		float h = atof(tokens[5].c_str());
		int state = atof(tokens[6].c_str());
		obj = new Ground(x, y, w, h, state);
		break; 
	}
	case OBJECT_TYPE_CAMERA:
	{
		float w = atof(tokens[4].c_str());
		float h = atof(tokens[5].c_str());
		camera.left = x;
		camera.top = y;
		camera.right = x + w;
		camera.bottom = y + h;
		break;
	}
	case OBJECT_TYPE_MAP_CAMERA:
	{
		float w = atof(tokens[4].c_str());
		float h = atof(tokens[5].c_str());
		mapCamera.left = x;
		mapCamera.top = y;
		mapCamera.right = x + w;
		mapCamera.bottom = y + h;
		break;
	}
	case OBJECT_TYPE_PORTAL:
	{
		float r = atof(tokens[4].c_str());
		float b = atof(tokens[5].c_str());
		int scene_id = atoi(tokens[6].c_str());
		obj = new CPortal(x, y, r, b, scene_id);
	}
	break;

	case OBJECT_TYPE_MUSHROOMS:
	{
		int app = atof(tokens[4].c_str());
		obj = new CMushrooms(app);	
	}
	break;
	case OBJECT_TYPE_LEAVES:
	{
		int state = atof(tokens[4].c_str());
		obj = new CLeaves();
		obj->SetState(state);
	}
	break;
	case OBJECT_TYPE_CACTUS:
	{
		int num = atof(tokens[4].c_str());
		int app = atof(tokens[5].c_str());
		int state = atof(tokens[6].c_str());
		int stype = atof(tokens[7].c_str());
		int sewer = atof(tokens[8].c_str());
		int pipes = atof(tokens[9].c_str());
		obj = new CCactus(app,stype,sewer,pipes);
		CCactus* c= dynamic_cast<CCactus*>(obj);
		obj->SetState(state);
		c->SetStartY(y);
		c->SetNumber(num);
		break;
	}
	case OBJECT_TYPE_SEWERPIPES:
	{
		int state = atof(tokens[4].c_str());
		obj = new SewerPipes();
		obj->SetState(state);
		break;
	}
	case OBJECT_TYPE_ITEM_SIGN:
	{
		int nstate = atof(tokens[4].c_str());
		obj = new CItemSign(nstate);
	}
	break;
	case OBJECT_TYPE_TREE:
	{
		obj = new CTree();
	}
	break;
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}
	
	// General object setup
	if (object_type != OBJECT_TYPE_CAMERA && object_type != OBJECT_TYPE_MAP_CAMERA)
	{
		obj->SetPosition(x, y);
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

		obj->SetAnimationSet(ani_set);
		objects.push_back(obj);

	}

}

void CPlayScene::_ParseSection_TILEMAP_DATA(string line)
{
	LPCWSTR path = ToLPCWSTR(line);
	ifstream f;

	f.open(path);

	int ID;
	int rowMap, columnMap, columnTile, rowTile, totalTiles;
	f >> ID >> rowMap >> columnMap >> rowTile >> columnTile >> totalTiles;
	//khoi tao ma tran data
	std::vector<std::vector<int>> tileMapData;
	tileMapData.resize(rowMap);
	for (int i = 0; i < rowMap; i++)
		tileMapData[i].resize(columnMap);
	for (int i = 0; i < rowMap; i++)
	{
		for (int j = 0; j < columnMap; j++)
		{
			f >> tileMapData[i][j];
		}
	}
	f.close();


	tileMap = new Map(ID, rowMap, columnMap, rowTile, columnTile, totalTiles);
	tileMap->ExtractTileFromTileSet();
	tileMap->SetTileMapData(tileMapData);
}



void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;					

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[TEXTURES]") { section = SCENE_SECTION_TEXTURES; continue; }
		if (line == "[SPRITES]") { 
			section = SCENE_SECTION_SPRITES; continue; }
		if (line == "[ANIMATIONS]") { 
			section = SCENE_SECTION_ANIMATIONS; continue; }
		if (line == "[ANIMATION_SETS]") { 
			section = SCENE_SECTION_ANIMATION_SETS; continue; }
		if (line == "[OBJECTS]") { 
			section = SCENE_SECTION_OBJECTS; continue; }
		if (line == "[TILE_MAP_DATA]")
		{
			section = SCENE_SECTION_TILEMAP; continue;
		}
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }	

		//
		// data section
		//
		switch (section)
		{ 
			case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
			case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
			case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
			case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
			case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
			case SCENE_SECTION_TILEMAP: _ParseSection_TILEMAP_DATA(line); break;
		}
	}

	f.close();

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	CGame::GetInstance()->SetCamPos(0,0);

	hud = new Hud(this);

	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 
	if(GetTickCount()- time_start > GAME_TIME)
	{
		time_start = 0;
	}
	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt,this, &coObjects);
	}

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return; 

	// Update camera to follow mario
	float cx, cy;
	float x_mario, y_mario;
	player->GetPosition(cx, cy);
	player->GetPosition(x_mario, y_mario);

	CGame *game = CGame::GetInstance();
	cx -= (float)game->GetScreenWidth() / 2;
	cy -= (float)game->GetScreenHeight() / 2;

	float x_cam;
	float y_cam;
	CGame::GetInstance()->GetCamPos(x_cam, y_cam);

	//khoa cam x
	if (cx < mapCamera.left)
	{
		cx = 0;
	}
	else if (cx > mapCamera.right- game->GetScreenWidth())
	{
		cx = mapCamera.right-game->GetScreenWidth();
	}

	//khoa cam y
	if ((y_mario > camera.top + (game->GetScreenHeight()*1 / 4)) )
	{
		CGame::GetInstance()->SetCamPos(cx, camera.top/*cy*/);
	}
	else if (y_cam <= mapCamera.top)
	{
		CGame::GetInstance()->SetCamPos(cx, y_cam/*cy*/);
	}
	else
	{
		CGame::GetInstance()->SetCamPos(cx, cy/*cy*/);
	}
	CGame::GetInstance()->GetCamPos(x_cam, y_cam);
	tileMap->SetCamera(x_cam, y_cam);

	hud->Update();
}

void CPlayScene::Render()
{
	tileMap->Render();
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();
	hud->Render();
}

/*
	Unload current scene
*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void CPlayScenceKeyHandler::OnKeyUp(int KeyCode)
{
	CMario* mario = ((CPlayScene*)scence)->GetPlayer();
	switch (KeyCode)
	{
	case DIK_SPACE:
		if ( mario->GetState()==MARIO_STATE_FLYLING)
		{
			mario->SetState(MARIO_STATE_LANDING);
			mario->ResetTimeFly();
		}
		break;
	case DIK_B:
		mario->SetPick(false);
		break;
	}
}

void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	CMario *mario = ((CPlayScene*)scence)->GetPlayer();
	CPlayScene* scene = dynamic_cast<CPlayScene*>(scence);
	switch (KeyCode)
	{
	case DIK_SPACE:
		if (((abs(mario->GetV()) >= MARIO_WALKING_SPEED_MAX &&
			(mario->GetApperance() == MARIO_FOX || mario->GetApperance() == MARIO_FOX_FIRE)))
			|| mario->GetState() == MARIO_STATE_FLYLING || mario->GetState() == MARIO_STATE_LANDING)
		{
			mario->SetState(MARIO_STATE_FLYLING);
		}
		break;
	case DIK_W: 
		mario->Reset();
		break;
	case DIK_L:
		mario->UpLevel();
		break;
	case DIK_K:
		mario->ChangeApperance(MARIO_FOX);
		break;
	case DIK_J:
		mario->ChangeApperance(MARIO_FIRE);
		break;
	case DIK_I:
		mario->ChangeApperance(MARIO_FOX_FIRE);
		break;
	case DIK_M:
		mario->SetState(MARIO_STATE_FLY);
		break;
	case DIK_B:
		mario->SetState(MARIO_STATE_HOLD);
		break;
	case DIK_A:
		if (mario->GetApperance() == MARIO_FIRE)
		{
			mario->SetState(MARIO_STATE_FIRE_BALL_DOUBLE);
		}
		break;
	case DIK_D:
		if (mario->GetApperance() == MARIO_FIRE)
		{
			if (mario->GetCountFireBall() < 2)
			{
				mario->SetState(MARIO_STATE_FIRE_BALL);
			}
		}
		else if (mario->GetApperance() == MARIO_FOX)
		{
			mario->SetState(MARIO_STATE_ATTACK);
		}
		break;

	}
}

void CPlayScenceKeyHandler::KeyState(BYTE *states)
{
	CGame *game = CGame::GetInstance();
	CMario *mario = ((CPlayScene*)scence)->GetPlayer();

	if(mario!=NULL)
	// disable control key when Mario die 
	if (mario->GetState() == MARIO_STATE_DIE) return;
	if (game->IsKeyDown(DIK_DOWN))
	{
		if (mario->GetState() != MARIO_STATE_JUMP)
		{
			mario->SetState(MARIO_STATE_SIT);
		}
	}
	else if (game->IsKeyDown(DIK_RIGHT))
	{
		if (!mario->GetIsAttack())
		{
			if (mario->GetState() != MARIO_STATE_LANDING || mario->GetNx() < 0)
			{
				if (mario->GetState() != MARIO_STATE_FLYLING)
				{
					if (mario->GetState() == MARIO_STATE_WALKING_LEFT || mario->GetState() == MARIO_STATE_WALKING_LEFT_FAST) // kiem tra khi bam nut phai thi co dang di ve ben trai khong ?
					{
						mario->SetState(MARIO_STATE_STOP); // dang di thi chuyen sang trang thai danh tay
					}
					else if (GetTickCount64() - mario->GetTimeStop() > TIME_STOP_MARIO) // gettickcount64 la ham lay thoi gian hien tai
					{
						if (mario->GetState() != MARIO_STATE_JUMP)
						{
							if (game->IsKeyDown(DIK_LSHIFT))
							{
								mario->SetState(MARIO_STATE_WALKING_RIGHT_FAST);
							}
							else
							{
								mario->SetState(MARIO_STATE_WALKING_RIGHT);
							}
							if (game->IsKeyDown(DIK_B))
							{
								mario->SetState(MARIO_STATE_HOLD);
							}
						}
					}
				}
			}
		}
		if (game->IsKeyDown(DIK_SPACE))
		{
			if (mario->GetState() != MARIO_STATE_WALKING_RIGHT_FAST && mario->GetState() != MARIO_STATE_WALKING_LEFT_FAST
				&&mario->GetState() != MARIO_STATE_FLYLING && mario->GetState()!=MARIO_STATE_LANDING)
			{
				if (GetTickCount64() - mario->GetTimeJump() <= TIME_JUMP_MARIO || mario->GetTimeJump() == 0)
				{
 					mario->SetState(MARIO_STATE_JUMP);
				}
			}
		}
	}
	else if (game->IsKeyDown(DIK_SPACE))
	{
		if (mario->GetState() != MARIO_STATE_WALKING_RIGHT_FAST && mario->GetState() != MARIO_STATE_WALKING_LEFT_FAST
			&& mario->GetState() != MARIO_STATE_FLYLING && mario->GetState() != MARIO_STATE_LANDING)
		{
			if (GetTickCount64()-mario->GetTimeJump()<= TIME_JUMP_MARIO ||mario->GetTimeJump()==0)
			{
				mario->SetState(MARIO_STATE_JUMP);
			}
		}
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		if (!mario->GetIsAttack())
		{
			if (mario->GetState() != MARIO_STATE_LANDING || mario->GetNx() > 0)
			{
				if (mario->GetState() != MARIO_STATE_FLYLING)
				{
					if (mario->GetState() == MARIO_STATE_WALKING_RIGHT || mario->GetState() == MARIO_STATE_WALKING_RIGHT_FAST)
					{
						mario->SetState(MARIO_STATE_STOP);
					}
					else if (GetTickCount64() - mario->GetTimeStop() > TIME_STOP_MARIO)
					{
						if (mario->GetState() != MARIO_STATE_JUMP)
						{
							if (game->IsKeyDown(DIK_LSHIFT))
							{
								mario->SetState(MARIO_STATE_WALKING_LEFT_FAST);
							}
							else mario->SetState(MARIO_STATE_WALKING_LEFT);
							if (game->IsKeyDown(DIK_B))
							{
								mario->SetState(MARIO_STATE_HOLD);
							}
						}
					}
				}
			}
		}
		if (game->IsKeyDown(DIK_SPACE))
		{
			if (mario->GetState() != MARIO_STATE_WALKING_RIGHT_FAST && mario->GetState() != MARIO_STATE_WALKING_LEFT_FAST
				&& mario->GetState() != MARIO_STATE_FLYLING && mario->GetState() != MARIO_STATE_LANDING)
			{
				if (GetTickCount64() - mario->GetTimeJump() <= TIME_JUMP_MARIO || mario->GetTimeJump() == 0)
				{
					mario->SetState(MARIO_STATE_JUMP);
				}
			}
		}
	}
	else
	{
		if ((mario->GetState() != MARIO_STATE_JUMP&& mario->GetState()!=MARIO_STATE_FIRE_BALL_DOUBLE)
			&& (!mario->GetIsAttack()) && !mario->GetIsFireBall())
		{
			mario->SetState(MARIO_STATE_IDLE);
		}
	}
	
}