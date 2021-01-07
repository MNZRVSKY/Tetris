#include "Shape.h"
#include <iostream>
using namespace std;

Shape::Shape()
{
	this->m_Size = 0;
	this->SetAsix_X(0);
	this->SetAsix_Y(0);
}
Shape::Shape(int arr[][2])
{
	this->m_Size = 2;
	this->SetAsix_X(4);
	this->SetAsix_Y(0);
	for(int i = 0; i < this->m_Size; i ++)
	{
		for(int j = 0; j <this-> m_Size; j ++)
		{
			this->m_Arr[i][j] = arr[i][j];
		}
	}
}
Shape::Shape(int arr[][3])
{
	this->m_Size = 3;
	this->SetAsix_X(4);
	this->SetAsix_Y(0);
	for(int i = 0; i < this->m_Size; i ++)
	{
		for(int j = 0; j <this-> m_Size; j ++)
		{
			this->m_Arr[i][j] = arr[i][j];
		}
	}
}
Shape::Shape(int arr[][4])
{
	this->m_Size = 4;
	this->SetAsix_X(3);
	this->SetAsix_Y(0);
	for(int i = 0; i < this->m_Size; i ++)
	{
		for(int j = 0; j <this-> m_Size; j ++)
		{
			this->m_Arr[i][j] = arr[i][j];
		}
	}
}
Shape::Shape(Shape & obj)
{
	this->m_Size = obj.m_Size;
	this->SetAsix_X(obj.GetAsix_X());
	this->SetAsix_Y(obj.GetAsix_Y());
	for(int i = 0; i < this->m_Size; i ++)
	{
		for(int j = 0; j <this-> m_Size; j ++)
		{
			this->m_Arr[i][j] = obj.m_Arr[i][j];
		}
	}
}
Shape::~Shape(){}

Shape Shape::Random()
{
	Shape shape[7];
	//==================== Figures ==================
	int kube[2][2] = {1, 1,
						1, 1};
	//----------------------------------
	int piramid[3][3] = {0, 2, 0,
							2, 2, 2,
							0, 0 ,0};
	//----------------------------------
	int hook_left[3][3] = {0, 0, 3,
							3, 3, 3,
							0, 0, 0};
	//----------------------------------
	int hook_right[3][3] = {4, 0, 0,
							4, 4, 4,
							0, 0, 0};
	//-----------------------------------
	int flash_left[3][3] = {5, 5, 0,
								0, 5, 5,
								0, 0, 0};
	//----------------------------------
	int flash_right[3][3] = {0, 6, 6,
							6, 6, 0,
							0, 0, 0};
	//----------------------------------
	int stick[4][4] = {0, 0, 0, 0,
						7, 7, 7, 7,
						0, 0, 0, 0,
						0, 0, 0, 0};
	//----------------------------------
	shape[0] = Shape(kube);
	shape[1] = Shape(piramid);
	shape[2] = Shape(hook_left);
	shape[3] = Shape(hook_right);
	shape[4] = Shape(flash_left);
	shape[5] = Shape(flash_right);
	shape[6] = Shape(stick);
	return *this = shape[-1 + rand()% 7 + 1];
}
bool Shape::FirstLaneIsEmpty()
{
	int lich = 0;
	for(int i = 0; i < this->m_Size; i ++)
	{
		if(this->m_Arr[0][i] != 0) { lich ++; }
	}
	return (lich == 0) ? true :  false;
}
bool Shape::SecondLaneIsEmpty()
{
	int lich = 0;
	for(int i = 0; i < this->m_Size; i ++)
	{
		if(this->m_Arr[1][i] != 0) { lich ++; }
	}
	return (lich == 0) ? true :  false;
}
bool Shape::PenultimateLaneIsEmpty()
{
	int lich = 0;
	for(int i = 0; i < this->m_Size; i ++)
	{
		if(this->m_Arr[this->m_Size - 2][i] != 0) { lich ++; }
	}
	return (lich == 0) ? true :  false;
}
bool Shape::LatestLaneIsEmpty()
{
	int lich = 0;
	for(int i = 0; i < this->m_Size; i ++)
	{
		if(this->m_Arr[this->m_Size - 1][i] != 0) { lich ++; }
	}
	return (lich == 0) ? true :  false;
}
	 
bool Shape::FirstColumnIsEmpty()
{
	int lich = 0;
	for(int i = 0; i < this->m_Size; i ++)
	{
		if(this->m_Arr[i][0] != 0) { lich++; }
	}
	return (lich == 0) ? true : false;
}
bool Shape::SecondColumnIsEmpty()
{
	int lich = 0;
	for(int i = 0; i < this->m_Size; i ++)
	{
		if(this->m_Arr[i][1] != 0) { lich++; }
	}
	return (lich == 0) ? true :  false;
}
bool Shape::PenultimateColumnIsEmpty()
{
	int lich = 0;
	for(int i = 0; i < this->m_Size; i ++)
	{
		if(this->m_Arr[i][this->m_Size - 2] != 0) { lich++; }
	}
	return (lich == 0) ? true : false;
}
bool Shape::LatestColumnIsEmpty()
{
	int lich = 0;
	for(int i = 0; i < this->m_Size; i ++)
	{
		if(this->m_Arr[i][this->m_Size - 1] != 0) { lich++; }
	}
	return (lich == 0) ? true : false;
}

char Shape::GetElementByPosition(int i, int j)
{
	if(i < this->m_Size && j < this->m_Size) { return this->m_Arr[i][j]; }
	else{ exit(0); }
}

void Shape::Rotate()
{
	Shape tmp(this->m_Arr);
	for(int i = 0; i < this->m_Size; i ++)
	{
		for(int j = 0; j < this->m_Size; j ++)
		{
			tmp.m_Arr[this->m_Size - 1 - j][i] = this->m_Arr[i][j];
		}
	}
	for(int i = 0; i < this->m_Size; i ++)
	{
		for(int j = 0; j < this->m_Size; j ++)
		{
			this->m_Arr[i][j] = tmp.m_Arr[i][j];
		}
	}
}

void Shape::ToTopPosition()
{
	this->m_Asix_Y = 0;

	if(this->m_Size == 4) this->m_Asix_X = 3;
	else if(this->m_Size == 3) this->m_Asix_X = 4;
	else if(this->m_Size == 2) this->m_Asix_X = 5;

	if(this->FirstLaneIsEmpty()  && this->SecondLaneIsEmpty() )
	{
		this->SetAsix_Y(this->GetAsix_Y() - 2);
	}
	else if(this->FirstLaneIsEmpty() )
	{
		this->SetAsix_Y(this->GetAsix_Y() - 1);
	}
}
