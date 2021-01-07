#pragma once
#include <iostream>
#include "Shape.h"
#include "AnimateManager.h"
using namespace std;

class Field
{
private:
	int m_Score;
	int m_Lines;
	int m_Level;
	int m_Width;
	int m_Height;
	AnimateManager* m_AnimateManager;
	int m_Field_Arr[20][10];

public:
	Field();
	Field(const Field & obj);
	~Field();

	void SetWidth(int w){this->m_Width = w;}
	void SetHeight(int h){this->m_Height = h;}

	int GetWight(){ return this->m_Width; }
	int GetHeight(){ return this->m_Height; }
	int GetScore() { return this->m_Score; }
	int GetLines() { return this->m_Lines; }
	int GetLevel() { return this->m_Level; }
	int GetElementByPosition(int i, int j);

	void ToTopPosition(Shape & obj);
	void Rotate(Shape &);
	void MoveLeft(Shape & );   
	void MoveRight(Shape &);  
	void MoveDown(Shape &, bool & EndGame, bool & EndCicle); 
	
	int  NumberFullLine();
	void CounterOfScores();
	bool IsFullLine();
	void DeleteFullLines();

	Point GetCoordOfLine(int lineNumber);
    bool AboveTheBottomEdgeOfField(Shape obj);
	bool IsNotActSymbol(Shape obj);
	bool IsNîtOverrideSymbol(Shape obj);
	void SaveFigureOnTheField(Shape obj);

	void Render();
	void Update(float dt);
};