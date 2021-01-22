#pragma once
#include <string>
using namespace std;
class CellObject
{
public:
	string info;
	int column;
	int row;

	CellObject()
	{
		info = "";
		column = -1;
		row = -1;
	}
};

