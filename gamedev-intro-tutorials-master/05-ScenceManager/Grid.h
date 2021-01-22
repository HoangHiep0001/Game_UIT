#pragma once
#include <cmath>
#include "Cell.h"
#include "Game.h"

#define CELL_SIZE 150

typedef std::vector<LPGAMEOBJECT> cellObjects;

class Grid
{
	float width;
	float height;
	
	int SumColum;
	int SumRow;

	std::vector<std::vector<cellObjects>>cells;
	std::vector<LPGAMEOBJECT> allwaysUpdateOBject;
public:
	Grid(float w, float h) {
		this->width = w;
		this->height = h;
		this->SumColum = ceil((float)this->width / CELL_SIZE) + 1;
		this->SumRow = ceil((float)this->height / CELL_SIZE);

		this->cells.resize(SumRow);
		for (int i = 0; i < SumRow; i++)
		{
			cells[i].resize(SumColum);
		}
		for (size_t i = 0; i < SumRow; i++)
		{
			for (size_t j = 0; j < SumColum; j++)
			{
				this->cells[i][j].clear();
			}
		}
	}

	std::vector<std::vector<cellObjects>> GetCells()
	{
		return this->cells;
	}
	std::vector<LPGAMEOBJECT> getallwaysUpdateOBject()
	{
		return this->allwaysUpdateOBject;
	}

	void pushAlwaysObject(LPGAMEOBJECT object)
	{
		this->allwaysUpdateOBject.push_back(object);
	}

	void pushObject(LPGAMEOBJECT object, int row, int column)
	{
		cells[row][column].push_back(object);
	}

	void GetListObject(std::vector<LPGAMEOBJECT>& listObject)
	{
		float camx, camy;
		CGame::GetInstance()->GetCamPos(camx, camy);
		int startColumn = floor(camx / CELL_SIZE);
		if (startColumn > 0)
		{
			startColumn -= 1;
		}
		else startColumn = 0;

		int endColumn = floor((camx + CGame::GetInstance()->GetScreenWidth()) / CELL_SIZE);
		if (endColumn >= SumColum)
			endColumn = SumColum;
		else endColumn += 1;
		
		for (size_t i = 0; i < this->allwaysUpdateOBject.size(); i++)
		{
			LPGAMEOBJECT ob = allwaysUpdateOBject.at(i);
			listObject.push_back(ob);
		}

		for (int i = 0; i < this->SumRow; i++)
		{
			for (int j = startColumn; j < endColumn; j++)
			{
				for (size_t k = 0; k < this->cells[i][j].size(); k++)
				{
					LPGAMEOBJECT obj = this->cells[i][j].at(k);
					listObject.push_back(obj);
				}
			}
		}
	}

	void Add(LPGAMEOBJECT object)
	{
		float x_, y_;
		object->GetPosition(x_, y_);
		//tinh vi tri cua object
		int cellX = (int)(x_ / CELL_SIZE);
		int cellY = (int)(y_ / CELL_SIZE);
		if (cellX > SumColum)
		{
			return;
		}
		if (cellY > SumRow)
		{
			return;
		}
		object->SetRow(cellY);
		object->SetColum(cellX);
		if (!object->GetIsAlwaysUpdate())
			this->cells[cellY][cellX].push_back(object);
		else
			allwaysUpdateOBject.push_back(object);
	}

	void Update(LPGAMEOBJECT object)
	{
		if (object->GetIsAlwaysUpdate())
			return;
		float cx, cy;

		CGame::GetInstance()->GetCamPos(cx, cy);

		float x, y;
		object->GetPosition(x, y);

		float l, t, r, b;
		object->GetBoundingBox(l, t, r, b);

		int oldComlumn = object->GetColum();
		int oldRow = object->GetRow();
		//tim vi tri cu cua cell chua object
		//xem object dang o cell nao

		int cellX = (int)(x / CELL_SIZE)+1;
		int cellY = (int)(y / CELL_SIZE);


		if (oldComlumn == cellX && oldRow == cellY)
		{
			return;
		}
		if (oldComlumn != -1 && oldRow != -1) // loại bỏ cell cũ
		{
			for (vector<LPGAMEOBJECT>::iterator it = cells[oldRow][oldComlumn].begin(); it != cells[oldRow][oldComlumn].end(); ) {
				if ((*it) == object) {
					it = cells[oldRow][oldComlumn].erase(it);
				}
				else ++it;
			}

		}

		//thêm lại vào cell mới
		Add(object);
	}
};



