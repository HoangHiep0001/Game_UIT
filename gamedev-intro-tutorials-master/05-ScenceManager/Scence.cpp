#include "Scence.h"

CScene::CScene(int id, LPCWSTR filePath,int word,int time, int number)
{
	this->number = number;
	this->time = time;
	this->word = word;
	this->id = id;
	this->sceneFilePath = filePath;
}