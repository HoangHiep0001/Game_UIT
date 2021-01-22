#include <iostream>
#include <fstream>
#include"Utils.h"
#include "CellObject.h"

#define GRID_PATH "..\\05-ScenceManager\\source\\Grid\\"
#define GRID_SOURCE "\Grid_path.txt"

#define CELL_SIZE 150

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TEXTURES 2
#define SCENE_SECTION_SPRITES 3
#define SCENE_SECTION_ANIMATIONS 4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_OBJECTS	6
#define SCENE_SECTION_TILEMAP 7

#define MAX_SCENE_LINE 1024

CellObject* _ADD_OBJECTS_TOGRID(string line)
{
	vector<string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());
	CellObject* cell = new CellObject();

	if (tokens.size() < 3) return cell; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());
	int ani_set_id = atoi(tokens[3].c_str());

	int column = x / CELL_SIZE;
	int row = y / CELL_SIZE;

	cell->info = line;
	cell->column = column;
	cell->row = row;
	return cell;
}
vector<CellObject*> openfile(string path)
{
	ifstream f;
	f.open(path);
	int section = SCENE_SECTION_UNKNOWN;
	char str[MAX_SCENE_LINE];
	vector<CellObject*> cellObjects;
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);
		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[OBJECTS]") {
			section = SCENE_SECTION_OBJECTS; continue;
		}
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		if (section != SCENE_SECTION_OBJECTS) continue;
		

		CellObject* cell = _ADD_OBJECTS_TOGRID(line);
		if (cell->info != "")
		{
			cellObjects.push_back(cell);
		}
	}
	return cellObjects;
}

string getFileName(string line)
{
	string path = "";
	for (int i = line.length(); i >= 0; i--)
	{
		if (line[i] == '\\')
			break;
		path = line[i] + path;
	}
	return path;
}

void XuatFile(vector<CellObject*> cellObjects,string filename)
{
	string path = GRID_PATH + filename;
	ofstream f(path);
	string data = "";
	for (auto const& item : cellObjects)
	{
		data += item->info + "	" + to_string(item->column) + "	" + to_string(item->row)+"\n";
	}
	f << data;
	f.close();
}


int main()
{
	vector<string> path; //vector de luu nhung dong map duoc doc vao
	ifstream f;
	f.open(GRID_SOURCE);

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);
		path.push_back(line);
	}
	f.close();
	for (auto const& item : path)
	{
		string filename = getFileName(item);
		vector<CellObject*> cellObjects = openfile(item);
		XuatFile(cellObjects,filename);
	}
	cout << "Xuat thanh cong";
}