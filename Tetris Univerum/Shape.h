#pragma once
#include "Point.h"

class Shape: public Point
{
private:
	int m_Size;
	int m_Arr[4][4];

public:
	Shape();
	Shape(int arr[][2]);
	Shape(int arr[][3]);
	Shape(int arr[][4]);
	Shape(Shape & obj);
	~Shape();

	Shape Random();
	bool FirstLaneIsEmpty();
	bool SecondLaneIsEmpty();
	bool PenultimateLaneIsEmpty();
	bool LatestLaneIsEmpty();

	bool FirstColumnIsEmpty();
	bool SecondColumnIsEmpty();
	bool PenultimateColumnIsEmpty();
	bool LatestColumnIsEmpty();

	char GetElementByPosition(int i, int j);

	void Rotate();

	void ToTopPosition();

	void SetSize(int size) { this->m_Size = size; }
	int  GetSize()         { return this->m_Size; }
};

