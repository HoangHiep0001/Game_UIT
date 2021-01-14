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
#include "Trigger.h"
#include "Trigger_ChangeCamera.h"
#include "CTail.h"
#include "CBroken.h"
#include "CCheckStop.h"
#include "CPortalintro.h"
#include "CEffectItem.h"
#include "CCheckUpdate.h"
using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath, int word, int time,int intro):CScene(id, filePath, word, time, intro)
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
#define OBJECT_TYPE_BROKEN	13
#define OBJECT_TYPE_CHECKSTOP 15
#define OBJECT_TYPE_CHECKUPDATE	35
#define OBJECT_TYPE_CACTUS 20
#define OBJECT_TYPE_TREE 21
#define OBJECT_TYPE_EFFECTITEM 22
#define OBJECT_TYPE_SEWERPIPES 40
#define OBJECT_TYPE_TRIGGERPIPES 41
#define OBJECT_TYPE_TRIGGER_CHANGE_CAMERA 42
#define OBJECT_TYPE_PORTALINTRO	49
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
		
		obj = new CMario(this->intro,x,y); 
		player = (CMario*)obj;  
		DebugOut(L"[INFO] Player object created!\n");
		break;
	case OBJECT_TYPE_GOOMBA:
	{
		int app = atoi(tokens[4].c_str());
		int state = atoi(tokens[5].c_str());
		obj = new CGoomba(app);
		CGoomba* q = dynamic_cast<CGoomba*>(obj);
		q->SetState(state); 
		q->SetStartPoint(x, y);
		q->SetStatePoint(state);
		
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
		float diriction = atof(tokens[6].c_str());
		float distance_a= atof(tokens[7].c_str());
		float distance_b = atof(tokens[8].c_str());
		obj = new CKoopas(app);
		CKoopas* q = dynamic_cast<CKoopas*>(obj);
		q->SetStartPoint(x, y);
		q->SetStatePoint(state);
		q->SetState(state);
		q->SetDirection(diriction);
		q->SetDistance(distance_a, distance_b);

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
	case OBJECT_TYPE_CHECKUPDATE:
	{
		float w = atof(tokens[4].c_str());
		float h = atof(tokens[5].c_str());
		int scene_id = atoi(tokens[6].c_str());
		float mariox = atof(tokens[7].c_str());
		float marioy = atof(tokens[8].c_str());
		obj = new CCheckUpdate(x, y, w, h, scene_id, mariox, marioy);
		break;
	}
	case OBJECT_TYPE_CHECKSTOP:
	{
		float w = atof(tokens[4].c_str());
		float h = atof(tokens[5].c_str());
		int direction = atof(tokens[6].c_str());
		obj = new CCheckStop(x, y, w, h, direction);
		break;
	}
	case OBJECT_TYPE_CAMERA:
	{
		RECT cam;
		float w = atof(tokens[4].c_str());
		float h = atof(tokens[5].c_str());
		int id = atoi(tokens[6].c_str());
		cam.left = x;
		cam.top = y;
		cam.right = x + w;
		cam.bottom = y + h;
		Cameras[id] = cam;

		break;
	}
	case OBJECT_TYPE_MAP_CAMERA:
	{
		float w = atof(tokens[4].c_str());
		float h = atof(tokens[5].c_str());
		int id= atoi(tokens[6].c_str());
		int n = atoi(tokens[7].c_str());
		mapCamera.left = x;
		mapCamera.top = y;
		mapCamera.right = x + w;
		mapCamera.bottom = y + h;
		mapCameras[id] = mapCamera;
		isSpecialCamera[id] = n;
		break;
	}
	case OBJECT_TYPE_PORTAL:
	{
		float r = atof(tokens[4].c_str());
		float b = atof(tokens[5].c_str());
		int scene_id = atoi(tokens[6].c_str());
		float mariox = atof(tokens[7].c_str());
		float marioy = atof(tokens[8].c_str());
		obj = new CPortal(x, y, r, b, scene_id,mariox,marioy);
	}
	break;
	case OBJECT_TYPE_PORTALINTRO:
	{
		float r = atof(tokens[4].c_str());
		float b = atof(tokens[5].c_str());
		int scene_id = atoi(tokens[6].c_str());
		float mariox = atof(tokens[7].c_str());
		float marioy = atof(tokens[8].c_str());
		obj = new CPortalintro(x, y, r, b, scene_id, mariox, marioy);
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
	case OBJECT_TYPE_TRIGGERPIPES:
	{
		float w = atof(tokens[4].c_str());
		float h = atof(tokens[5].c_str());
		int state = atof(tokens[6].c_str());
		obj = new Trigger(x, y, w, h, state);
		break;
	}
	case OBJECT_TYPE_TRIGGER_CHANGE_CAMERA:
	{
		float w = atof(tokens[4].c_str());
		float h = atof(tokens[5].c_str());
		int id_camera = atof(tokens[6].c_str());
		float mx = atof(tokens[7].c_str());
		float my = atof(tokens[8].c_str());
		obj = new Trigger_ChangeCamera(x, y, w, h, id_camera,mx,my);
	}
		break;
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

	case OBJECT_TYPE_EFFECTITEM:
	{
		int state = atof(tokens[4].c_str());
		obj = new CEffectItem(state);
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

	if (CGame::GetInstance()->GetProperties()->GetFlag())
	{
		player->SetMarioProperties();
	}

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));

	CGame::GetInstance()->SetCamPos(0,0);

	hud = new Hud(this);
	mapCamera = mapCameras.at(0);
	isSpecialMap = isSpecialCamera.at(0);
	camera = Cameras.at(0);
	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 
	GetCountDown();
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

	if (cy < mapCamera.top)
	{
		cy = mapCamera.top;
	}
	float x_cam;	//0	0
	float y_cam;
	CGame::GetInstance()->GetCamPos(x_cam, y_cam);

	//khoa cam x

	if (this->intro == INTRO_MAP_MAP)
	{
		CGame::GetInstance()->SetCamPos(camera.left, camera.top/*cy*/);
	}
	else
	{
		if (isSpecialMap==SPECIAL_MAP_STATIC)
		{
			if (cx < mapCamera.left)
			{
				cx = mapCamera.left;
			}
			if (cx > mapCamera.right - CGame::GetInstance()->GetScreenWidth())
			{
				cx = mapCamera.right - CGame::GetInstance()->GetScreenWidth();
			}

			//khoa cam y
			if ((y_mario > camera.top))
			{
				CGame::GetInstance()->SetCamPos(cx, camera.top/*cy*/);
			}
			else if (y_cam <= mapCamera.top)
			{
				CGame::GetInstance()->SetCamPos(cx, mapCamera.top/*cy*/);
			}
			else
			{
				CGame::GetInstance()->SetCamPos(cx, cy/*cy*/);
			}
		}
		else
		{
			if (x_specialcamera <= (mapCamera.right- CGame::GetInstance()->GetScreenWidth()))
			{
				x_specialcamera += INTRO_NX;
			}
			else
			{
				x_specialcamera = (mapCamera.right - CGame::GetInstance()->GetScreenWidth());
			}
			//khoa cam y
			if ((y_mario > camera.top))
			{
				CGame::GetInstance()->SetCamPos(x_specialcamera, camera.top/*cy*/);
			}
			else if (y_cam <= mapCamera.top)
			{
				CGame::GetInstance()->SetCamPos(x_specialcamera, mapCamera.top/*cy*/);
			}
			else
			{
				CGame::GetInstance()->SetCamPos(x_specialcamera, cy/*cy*/);
			}

		}
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
	if (player != NULL)
	{
		CGame::GetInstance()->SetSceneProperties(player->GetLife(), player->GetScore(), player->GetLevel(), player->GetApperance(),player->GetCoin_number());
		CGame::GetInstance()->GetProperties()->SetFlag();
	}
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];
	player = NULL;
	objects.clear();
	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void CPlayScene::GetCountDown()
{
	if (time_start == 0)
	{
		time_start = GetTickCount64();
	}
	else
	{
		if (GetTickCount64()-this->time_start> GAME_TIME)
		{
			time--;
			time_start = 0;
		}
	}
}

void CPlayScenceKeyHandler::OnKeyUp(int KeyCode)
{
	CMario* mario = ((CPlayScene*)scence)->GetPlayer();
	switch (KeyCode)
	{
	case DIK_S:
		if ( mario->GetState()==MARIO_STATE_FLYLING)
		{
			mario->SetState(MARIO_STATE_LANDING);
			mario->ResetTimeFly();
		}
		break;
	case DIK_D:
		mario->SetPick(false);
		break;
	}
}

void CPlayScenceKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	CMario *mario = ((CPlayScene*)scence)->GetPlayer();
	CPlayScene* scene = dynamic_cast<CPlayScene*>(scence);
	if (mario->GetIntro() == 0)
	{
		switch (KeyCode)
		{
		case DIK_E:
			mario->SetPosition(470,288);
			break;
		case DIK_5:
			DebugOut(L"Hello!", KeyCode);
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
		case DIK_Q:
			if (mario->GetApperance() == MARIO_FIRE)
			{
				mario->SetState(MARIO_STATE_FIRE_BALL_DOUBLE);
			}
			break;
		case DIK_D:
			{
				mario->SetState(MARIO_STATE_HOLD);
			}
			break;
		case DIK_A:
			if (mario->GetApperance() == MARIO_FIRE)
			{
				if (mario->GetState() == MARIO_STATE_IDLE)
				{
					if (mario->GetCountFireBall() < 2)
					{
						mario->SetState(MARIO_STATE_FIRE_BALL);
					}
				}
			}
			else if (mario->GetApperance() == MARIO_FOX)
			{
				mario->SetState(MARIO_STATE_ATTACK);
			}
			break;
		case DIK_S:
			if (((abs(mario->GetV()) >= MARIO_WALKING_SPEED_MAX &&(mario->GetApperance() == MARIO_FOX || mario->GetApperance() == MARIO_FOX_FIRE))|| (mario->GetState() == MARIO_STATE_FLYLING || mario->GetState() == MARIO_STATE_LANDING)))
			{
				mario->SetState(MARIO_STATE_FLYLING);
			}
			break;
		}
	}
	else
	{
		switch (KeyCode)
		{
		case DIK_S:
			if (mario->GetIsInPortal()) {
				CGame::GetInstance()->GetProperties()->SetMarioPosition(mario->GetPortal()->GetMarioX(), mario->GetPortal()->GetMarioY());
				CGame::GetInstance()->SwitchScene(mario->GetPortal()->GetSceneId());
			}
			break;
		case DIK_RIGHT:
			mario->SetState(MARIO_STATE_WALKING_RIGHT);
			break;
		case DIK_LEFT:
			mario->SetState(MARIO_STATE_WALKING_LEFT);
			break;
		case DIK_UP:
			mario->SetState(MARIO_STATE_START_UP);
			break;
		case DIK_DOWN:
			mario->SetState(MARIO_STATE_START_DOWN);
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
		}
	}
}

void CPlayScenceKeyHandler::KeyState(BYTE *states)
{
	CGame *game = CGame::GetInstance();
	CMario *mario = ((CPlayScene*)scence)->GetPlayer();
	if (mario->GetIntro()==0)
	{
		if(mario!=NULL)
		// disable control key when Mario die 
		if (mario->GetState() == MARIO_STATE_DIE) return;
		if (game->IsKeyDown(DIK_DOWN))
		{
			if (mario->getisDownPipe())
			{
				mario->SetState(MARIO_STATE_DOWN);
			}
			else
			{
				if (mario->GetState() != MARIO_STATE_JUMP)
				{
					mario->SetState(MARIO_STATE_SIT);
				}
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
								if (game->IsKeyDown(DIK_A))
								{
									mario->SetState(MARIO_STATE_WALKING_RIGHT_FAST);
								}
								else
								{
									mario->SetState(MARIO_STATE_WALKING_RIGHT);
								}
								if (game->IsKeyDown(DIK_D))
								{
									mario->SetState(MARIO_STATE_HOLD);
								}
								
							}
						}
					}
				}
				else
				{
					mario->SetState(MARIO_STATE_LANDING);
				}
			}
			if (game->IsKeyDown(DIK_S))
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
		else if (game->IsKeyDown(DIK_S))
		{
			if (mario->GetState() != MARIO_STATE_WALKING_RIGHT_FAST && mario->GetState() != MARIO_STATE_WALKING_LEFT_FAST&& mario->GetState() != MARIO_STATE_FLYLING && mario->GetState() != MARIO_STATE_LANDING)
			{
				if ((GetTickCount64()-mario->GetTimeJump()<= TIME_JUMP_MARIO ||mario->GetTimeJump()==0) && !mario->GetColliTop())
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
								if (game->IsKeyDown(DIK_A))
								{
									mario->SetState(MARIO_STATE_WALKING_LEFT_FAST);
								}
								else mario->SetState(MARIO_STATE_WALKING_LEFT);
								if (game->IsKeyDown(DIK_D))
								{
									mario->SetState(MARIO_STATE_HOLD);
								}
							}
						}
					}
				}
				else
				{
					mario->SetState(MARIO_STATE_LANDING);
				}
			}
			if (game->IsKeyDown(DIK_S))
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
		else if (game->IsKeyDown(DIK_UP))
		{
			if (mario->GetisUpPipe())
			{
				mario->SetState(MARIO_STATE_UP);
			}
		}
		else if (game->IsKeyDown(DIK_Z))
		{
			if (mario->GetApperance() == MARIO_FIRE)
			{
				mario->SetState(MARIO_STATE_FIRE_DOUBLE);
			}
		}
		else
		{
			if  (mario->GetState() != MARIO_STATE_UP&&mario->GetState()!=MARIO_STATE_DOWN
				&& (!mario->GetIsAttack()) && !mario->GetIsFireBall()&& mario->GetIntro()==0 && mario->GetState() != MARIO_STATE_IDLE&& mario->GetState() != MARIO_STATE_LANDING )
			{
				if (mario->GetState() != MARIO_STATE_FLYLING && mario->GetState() != MARIO_STATE_LANDING)
				{
					mario->SetState(MARIO_STATE_FALL_DOWN);
				}
			}
		}
	}
	
}