#pragma once
class Point
{
protected: 
	int m_Asix_X;
	int m_Asix_Y;

public:
	Point();
	Point(int x, int y);
	Point(const Point & obj);
	~Point();

	void SetAsix_X(int x) { this->m_Asix_X = x; }
	void SetAsix_Y(int y) { this->m_Asix_Y = y; }

	int GetAsix_X() { return this->m_Asix_X; }
	int GetAsix_Y() { return this->m_Asix_Y; }

	void OneElementToLeft();
	void OneElementToRight();

	Point GetPoint() { return *this; }


};


