#include "Field.h"
#include <iostream>
#include <windows.h>
#include <fstream>
#include "SoundManager.h"



using namespace std;


Field::Field()
{
	this->m_Score = 0;
	this->m_Width = 10;
	this->m_Height = 20;
	this->m_Level = 1;
	this->m_Lines = 0;
	this->m_AnimateManager	 = new AnimateManager();
	for(int i = 0; i < this->m_Height; i ++)
	{
		for(int j = 0; j < this->m_Width; j ++)
		{
			this->m_Field_Arr[i][j] = 0;
		}
	}
}
Field::Field(const Field & obj)
{
	this->m_Score = obj.m_Score;
	this->m_Width = obj.m_Width;
	this->m_Height = obj.m_Height;
	this->m_Level = obj.m_Level;
	this->m_Lines = obj.m_Lines;
	for(int i = 0; i < this->m_Height; i ++)
	{
		for(int j = 0; j < this->m_Width; j ++)
		{
			this->m_Field_Arr[i][j] = obj.m_Field_Arr[i][j];
		}
	}
}
Field::~Field(){}

void Field::Rotate(Shape & Current)
{
	int OneElement = 1, TwoElement = 2, FourElement = 4;
	Shape tmp(Current);
	tmp.Rotate();

	Shape ShiftToRigft(tmp);
	ShiftToRigft.SetAsix_X(tmp.GetAsix_X() + OneElement);

	Shape ShiftToLeft(tmp);
	ShiftToLeft.SetAsix_X(tmp.GetAsix_X() - OneElement);

	if(this->IsNîtOverrideSymbol(tmp) && this->IsNotActSymbol(tmp))
	{
		Current.Rotate();
	}
	else if(Current.GetAsix_X() < 0 && this->IsNîtOverrideSymbol(ShiftToRigft) )
	{
		if(Current.GetSize() == FourElement && Current.SecondColumnIsEmpty())
		{Current.SetAsix_X(Current.GetAsix_X() + TwoElement);}
		else Current.SetAsix_X (Current.GetAsix_X() + OneElement);
		Current.Rotate();
	}
	else if(Current.GetAsix_X() == 0 && this->IsNîtOverrideSymbol(tmp) )
	{
		Current.Rotate();
	}
	else if(Current.GetAsix_X() + Current.GetSize() > this->m_Width && this->IsNîtOverrideSymbol(ShiftToLeft) )
	{
		if(Current.GetSize() == FourElement && Current.PenultimateColumnIsEmpty() && Current.LatestColumnIsEmpty())
		{
			Current.SetAsix_X(Current.GetAsix_X() - TwoElement);
		}
		else 
		{
			Current.SetAsix_X(Current.GetAsix_X() - OneElement);
		}
		Current.Rotate();
	}
}
void Field::MoveLeft(Shape & Current)
{
	int OneElement = 1;
	Shape tmp(Current);
	tmp.SetAsix_X(tmp.GetAsix_X() - OneElement);
	if(this->IsNotActSymbol(Current)  && this->IsNîtOverrideSymbol(tmp) )
	{
		Current.SetAsix_X(Current.GetAsix_X() - OneElement);
	}
}
void Field::MoveRight(Shape & Current)
{
	int OneElement = 1;
	Shape tmp(Current);
	tmp.SetAsix_X(tmp.GetAsix_X() + OneElement);
	if(this->IsNotActSymbol(tmp)  && this->IsNîtOverrideSymbol(tmp) )
	{
		Current.SetAsix_X(Current.GetAsix_X() + OneElement);
	}
}
void Field::MoveDown(Shape & Current, bool & EndGame, bool & EndCicle)
{
	int OneElement = 1;
	Shape tmp(Current);
	tmp.SetAsix_Y(Current.GetAsix_Y() + OneElement);
	if(this->AboveTheBottomEdgeOfField(tmp)  && 
		this->IsNîtOverrideSymbol(tmp) )
	{
		Current.SetAsix_Y(Current.GetAsix_Y() + OneElement);
	}
	else if(Current.GetAsix_Y() <= 0 && this->IsNîtOverrideSymbol(tmp) != true)
	{
		EndGame = true;
	}
	else 
	{
		this->SaveFigureOnTheField(Current);
		EndCicle = true;
	}
}

bool Field::AboveTheBottomEdgeOfField(Shape obj)
{
	int res = 0;
	for(int i = 0; i < obj.GetSize(); i ++)
	{
		for(int j = 0; j < obj.GetSize(); j ++)
		{
			if(obj.GetElementByPosition(i, j) != 0 && obj.GetAsix_Y() + i >= this->m_Height)
			{
				res++;
			}
		}
	}
	return(res == 0)? true : false;
	
}

/*
	
*/
bool Field::IsNotActSymbol(Shape obj)
{
	int lich = 0;
	for(int i = 0; i < obj.GetSize(); i ++)
	{
		for(int j = 0; j < obj.GetSize(); j ++)
		{
			if(obj.GetElementByPosition(i, j) != 0 && obj.GetAsix_X() + j >= this->m_Width|| 
			   obj.GetElementByPosition(i, j) != 0 && obj.GetAsix_X() + j <= 0 ||
			   obj.GetElementByPosition(i, j) != 0 && obj.GetAsix_Y() + i < 0 ||
			   obj.GetElementByPosition(i, j) != 0 && obj.GetAsix_Y() + i >= this->m_Height)
			{ 
				lich ++; 
			}
		}
	}
	return(lich == 0)? true: false;
}
bool Field::IsNîtOverrideSymbol(Shape obj)
{
	int lich = 0;
	for(int i = 0; i < obj.GetSize(); i ++)
	{
		for(int j = 0; j < obj.GetSize(); j ++)
		{
			if(obj.GetElementByPosition(i, j) != 0 &&
				this->m_Field_Arr[obj.GetAsix_Y() + i][obj.GetAsix_X() + j] != 0 )
			{
				lich ++;
			}
		}
	}
	return(lich == 0)? true : false;
}

void Field::SaveFigureOnTheField(Shape obj)
{
	for(int i = 0; i < obj.GetSize(); i ++)
	{
		for(int j = 0; j < obj.GetSize(); j ++)
		{
			if(obj.GetElementByPosition(i, j) != 0)
			{
				this->m_Field_Arr[obj.GetAsix_Y() + i][obj.GetAsix_X() + j] = obj.GetElementByPosition(i, j);
			}
		}
	}
}
int  Field::GetElementByPosition(int i, int j)
{
	if(i < this->m_Height && j < this->m_Width) { return this->m_Field_Arr[i][j]; }
	else{ return -1; }
}

void Field::CounterOfScores()
{
	this->m_Lines ++;
	this->m_Score += 100;
	if     (this->m_Lines == 10){ this->m_Level = 2; }
	else if(this->m_Lines == 20){ this->m_Level = 3; }
	else if(this->m_Lines == 30){ this->m_Level = 4; }
	else if(this->m_Lines == 40){ this->m_Level = 5; }
	else if(this->m_Lines == 50){ this->m_Level = 6; }
	else if(this->m_Lines == 60){ this->m_Level = 7; }
	else if(this->m_Lines == 70){ this->m_Level = 8; }
	else if(this->m_Lines == 80){ this->m_Level = 9; }
}
int  Field::NumberFullLine()
{
	int element = 0;
	int Mark = -1;
	for(int i = 0; i < this->m_Height; i ++)
	{
		for(int j = 0; j < this->m_Width; j ++)
		{
			if(this->m_Field_Arr[i][j] != 0) { element ++; }
		}
		if(element == this->m_Width) {return Mark = i; }
		element = 0;
	}
	return Mark;
}
bool Field::IsFullLine()
{
	int element = 0;
	int line = 0;
	for(int i = 0; i < this->m_Height; i ++)
	{
		for(int j = 0; j < this->m_Width; j ++)
		{
			if(this->m_Field_Arr[i][j] != 0)
			{
				element ++;
			}
		}
		if(element == this->m_Width)
		{
			line ++;
		}
		element = 0;
	}
	return (line != 0) ?true :false;
}
void Field::DeleteFullLines()
{
	int element = 0;
	
	while(this->IsFullLine())
	{
		int numberOfFullLine = this->NumberFullLine();
		if(numberOfFullLine != -1)
		{
			SoundManager* soundManager = SoundManager::GetInstance();
			soundManager->PlayEffect(SOUND_EFFECT_LINE_CRASH);

			
			Point crashLineCoord = this->GetCoordOfLine(numberOfFullLine);
			m_AnimateManager->PlayCrachLine(crashLineCoord);
			this->CounterOfScores();

			for(int i = this->m_Height; i > numberOfFullLine; i --)
			{
				for(int j = 0; j < this->m_Width; j ++)
				{
					this->m_Field_Arr[i][j] = this->m_Field_Arr[i][j];
				}
			}
			for(int i = numberOfFullLine; i > 1; i --)
			{
				for(int j = 0; j < this->m_Width; j ++)
				{
					this->m_Field_Arr[i][j] = this->m_Field_Arr[i - 1][j];
				}
			}
			for(int i = 1; i > 0; i --)
			{
				for(int j = 0; j < this->m_Width; j ++)
				{
					this->m_Field_Arr[i][j] = 0;
				}
			}
		}
	}
}

Point Field::GetCoordOfLine(int lineNumber)
{
	int padding =  this->GetHeight() -  lineNumber;
	return Point(75 + lineNumber * 32 - (this->GetHeight() - padding * 5) , 102);
}

void Field::Update(float dt)
{
	m_AnimateManager->Update(dt);
}
void Field::Render()
{
	m_AnimateManager->Render();
}