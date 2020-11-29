#include "Scence.h"

CScene::CScene(int id, LPCWSTR filePath,int word)
{
	this->word = word;
	this->id = id;
	this->sceneFilePath = filePath;
}