#pragma once
#include <vector>
#include "GameObject.h"
class Cell
{
public:
	std::vector<CGameObject*> objects;
	int column;
	int row;

	Cell()
	{
		column = 0;
		row = 0;
	}
};

