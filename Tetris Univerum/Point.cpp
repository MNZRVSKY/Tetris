#include "Point.h"
#include <iostream>
using namespace std;

Point::Point()
{
	this->m_Asix_X = 0;
	this->m_Asix_Y = 0;
}
Point::Point(int x, int y)
{
	this->m_Asix_X = x;
	this->m_Asix_Y = y;
}
Point::Point(const Point & obj)
{
	this->m_Asix_X = obj.m_Asix_X;
	this->m_Asix_Y = obj.m_Asix_Y;
}
Point::~Point(){}

void Point::OneElementToLeft()
{
	this->m_Asix_X -= 32;
}
void Point::OneElementToRight()
{
	this->m_Asix_X += 32;
}
