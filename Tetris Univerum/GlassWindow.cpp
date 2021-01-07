#include "GlassWindow.h"
#include "ResourcesManager.h"


GlassWindow::GlassWindow()
{
	ResourcesManager* rm = ResourcesManager::GetInstance();
	m_Font = rm->GetFont(FONT_MAIN_WND_MENU);

	Init();
}


GlassWindow::~GlassWindow()
{
	delete m_Background;
	
	for (int i = 0; i < 8; ++i)
	{
		delete m_Elements[i];
	}

	for (int i = 0; i < 8; ++i)
	{
		delete m_Mini_Elements[i];
	}
}

void GlassWindow::OnEscape(WndEscapeCallback callback)
{
	m_onEscapeCallback = callback;
}

WindowType GlassWindow::GetType()
{
	return WINDOW_GLASS;
}

//=========================================================================

//				OVERLOADED METHODS

//=========================================================================

bool GlassWindow::KeyClick(int key, int chr)
{
	float dt = hge->Timer_GetDelta ();

	if (key == HGEK_ESCAPE || m_EndGame == true)
	{
		if (m_onEscapeCallback != NULL)
		{
			
			m_onEscapeCallback();
		}
	}	
	else if(key == HGEK_SPACE && m_EndGame != true)
	{ 
		if(m_Pause == false){ StopPause(m_Pause); hge->Channel_Pause(m_Music);}
		else if(m_Pause == true){ StartPause(m_Pause); hge->Channel_Resume(m_Music);}
	}
	else if(key == HGEK_ENTER && m_EndGame != true)
	{
		if(m_Pause == false)
		{
			soundManager->PlayEffect(SOUND_EFFECT_FIGURE_MOVE);

			Shape tmp = m_Hold;
			if(m_Hold.GetSize() != 0 && m_UntouchedHold == true)
			{
				m_Hold = m_Curent;
				m_Curent = tmp;
				m_UntouchedHold = false;
				m_Curent.ToTopPosition();
			}
			else if(m_UntouchedHold == true)
			{
				m_Hold =  m_Curent;
				m_Curent = m_Shapes[0];
				for(int i = 0; i < m_SizeOfShapes - 1; i ++)
				{
					m_Shapes[i] = m_Shapes[i + 1];
				}
				m_Shapes[m_SizeOfShapes - 1].Random();
				m_UntouchedHold = false;
				m_Curent.ToTopPosition();
			}
		}
	}
	else if (key == HGEK_LEFT && m_EndGame != true)  
	{ 
		if(m_Pause == false)
			MoveToLeft(m_Field, m_Curent);
	}
	else if (key == HGEK_RIGHT && m_EndGame != true)
	{ 
		if(m_Pause == false)
			MoveToRight(m_Field, m_Curent);
	}
	else if (key == HGEK_UP && m_EndGame != true)    
	{ 
		if(m_Pause == false)
			ToRotate(m_Field, m_Curent);
	}
	else if (key == HGEK_DOWN && m_EndGame != true) 
	{ 
		if(m_Pause == false)
			MoveToDown(m_Field, m_Curent, m_EndGame, m_EndCicle);
	}
	else 
	{ 
		if(m_Pause == false)
			FreeFall(m_Field, m_Curent, dt, m_Field.GetLevel(), m_EndGame, m_EndCicle);
	}

	if(m_EndCicle == true)
	{
		soundManager->PlayEffect(SOUND_EFFECT_FIGURE_DOWN);
		m_UntouchedHold = true;
		m_Field.DeleteFullLines();
		m_Curent = m_Shapes[0];

		for(int i = 0; i < m_SizeOfShapes - 1; i++)
		{
			m_Shapes[i] = m_Shapes[i + 1];
		}

		m_Shapes[m_SizeOfShapes - 1].Random();
		m_EndCicle = false;
		m_Curent.ToTopPosition();
	}	
	return true;
}

void GlassWindow::Render()
{
	m_Background->Render(0, 0);
	
	RenderField(m_Field);
	RenderCurrentFigure(m_Curent, m_Elements);

	for(int i = 0; i < m_SizeOfShapes; i++)
	{
		RenderLittleFigures(m_Shapes[i], m_AsixX_nextFigures, m_AsixY_nextFigures + (i * 100), m_Mini_Elements);
	}

	RenderLittleFigures(m_Hold, m_AsixX_holdFigures, m_AsixY_holdFigures, m_Mini_Elements);

	if(m_Pause) m_Font->printf(167, 245, HGETEXT_CENTER, "PAUSE");
	m_Font->printf(345, 55, HGETEXT_RIGHT, "%d", (char*)m_Field.GetScore());
	m_Font->printf(385, 607, HGETEXT_CENTER, "%d", (char*)m_Field.GetLevel());
	m_Font->printf(35, 607, HGETEXT_CENTER, "%d", (char*)m_Field.GetLines());

	m_Field.Render();
}

void GlassWindow::Update(float dt)
{

	m_Field.Update(dt);

}

void GlassWindow::Init()
{
	m_EndGame = false;
	m_EndCicle = false;
	m_Pause = false;

	m_moveDelay = 0.5;
	m_currentDelay = m_moveDelay;

	m_AsixX_nextFigures = 358;
	m_AsixY_nextFigures = 130;

	m_AsixX_holdFigures = 8;
	m_AsixY_holdFigures = 130;

	m_UntouchedHold = true;

	ResourcesManager* rm = ResourcesManager::GetInstance();

	m_Move = rm->GetSoundEffect(SOUND_EFFECT_FIGURE_MOVE);
	m_Rotate = rm->GetSoundEffect(SOUND_EFFECT_FIGURE_ROTATE);
	m_SaveFigure = rm->GetSoundEffect(SOUND_EFFECT_FIGURE_DOWN);
	m_CrashLine = rm->GetSoundEffect(SOUND_EFFECT_LINE_CRASH);

	soundManager = SoundManager::GetInstance();
	soundManager->StopMenuBackGround();
	soundManager->PlayBackground();

		
	m_Elements[FIGURE_COLOR_EMPTY] = new hgeSprite(rm->GetTexture(TEXTURE_BRIDGE_EMPTY) ,0, 0, 27, 27);
	m_Elements[FIGURE_COLOR_LIGHT_YELLOW] = new hgeSprite(rm->GetTexture(TEXTURE_BRIDGE_LIGHT_YELLOW) ,0, 0, 27, 27);
	m_Elements[FIGURE_COLOR_GREEN] = new hgeSprite(rm->GetTexture(TEXTURE_BRIDGE_GREEN) ,0, 0, 27, 27);
	m_Elements[FIGURE_COLOR_ORANGE] = new hgeSprite(rm->GetTexture(TEXTURE_BRIDGE_ORANGE) ,0, 0, 27, 27);
	m_Elements[FIGURE_COLOR_YELLOW] = new hgeSprite(rm->GetTexture(TEXTURE_BRIDGE_YELLO) ,0, 0, 27, 27);
	m_Elements[FIGURE_COLOR_PURPLE] = new hgeSprite(rm->GetTexture(TEXTURE_BRIDGE_PURPLE) ,0, 0, 27, 27);
	m_Elements[FIGURE_COLOR_BLUE] = new hgeSprite(rm->GetTexture(TEXTURE_BRIDGE_BLUE) ,0, 0, 27, 27);
	m_Elements[FIGURE_COLOR_LIGHT_BLUE] = new hgeSprite(rm->GetTexture(TEXTURE_BRIDGE_LIGHT_BLUE) ,0, 0, 27, 27);

		

		
	m_Mini_Elements[FIGURE_COLOR_EMPTY] = new hgeSprite(rm->GetTexture(TEXTURE_BRIDGE_EMPTY) ,0, 0, 12, 12);
	m_Mini_Elements[FIGURE_COLOR_LIGHT_YELLOW] = new hgeSprite(rm->GetTexture(TEXTURE_MINI_BRIDGE_LIGHT_YELLOW) ,0, 0, 12, 12);
	m_Mini_Elements[FIGURE_COLOR_GREEN] = new hgeSprite(rm->GetTexture(TEXTURE_MINI_BRIDGE_GREEN) ,0, 0, 12, 12);
	m_Mini_Elements[FIGURE_COLOR_ORANGE] = new hgeSprite(rm->GetTexture(TEXTURE_MINI_BRIDGE_ORANGE) ,0, 0, 12, 12);
	m_Mini_Elements[FIGURE_COLOR_YELLOW] = new hgeSprite(rm->GetTexture(TEXTURE_MINI_BRIDGE_YELLO) ,0, 0, 12, 12);
	m_Mini_Elements[FIGURE_COLOR_PURPLE] = new hgeSprite(rm->GetTexture(TEXTURE_MINI_BRIDGE_PURPLE) ,0, 0, 12, 12);
	m_Mini_Elements[FIGURE_COLOR_BLUE] = new hgeSprite(rm->GetTexture(TEXTURE_MINI_BRIDGE_BLUE) ,0, 0, 12, 12);
	m_Mini_Elements[FIGURE_COLOR_LIGHT_BLUE] = new hgeSprite(rm->GetTexture(TEXTURE_MINI_BRIDGE_LIGHT_BLUE) ,0, 0, 12, 12);
		
	m_Font = rm->GetFont(FONT_GLASS_WND_OUTPUTS);
	m_Background = new hgeSprite(rm->GetTexture(TEXTURE_BACKGROUND_GLASS_WND), 0, 0, 420, 700);

	Shape tmp;
	m_SizeOfShapes = 5;
	for(int i = 0; i < m_SizeOfShapes; i++)
	{
		m_Shapes[i] = tmp.Random();
	}
	m_Curent.Random();
}

void GlassWindow::StartPause(bool & pause)
{
	soundManager->PlayBackground();
	pause = false;
}
void GlassWindow::StopPause(bool & pause)
{
	soundManager->StopBackground();
	pause = true;
}

void GlassWindow::MoveToLeft(Field & field, Shape & current)
{
	field.MoveLeft(current);
	soundManager->PlayEffect(SOUND_EFFECT_FIGURE_MOVE);
}
void GlassWindow::MoveToRight(Field & field, Shape & current)
{
	field.MoveRight(current );
	soundManager->PlayEffect(SOUND_EFFECT_FIGURE_MOVE);
}
void GlassWindow::MoveToDown(Field & field, Shape & current, bool & EndGame, bool & EndCicle)
{
	field.MoveDown(current, EndGame, EndCicle);
	soundManager->PlayEffect(SOUND_EFFECT_FIGURE_MOVE);
}
void GlassWindow::ToRotate(Field & field, Shape & current)
{
	field.Rotate(current);
	soundManager->PlayEffect(SOUND_EFFECT_FIGURE_ROTATE);
}
void GlassWindow::FreeFall(Field & field, Shape & current, float DeltaTime, int level, bool & EndGame, bool & EndCicle)
{
	if(CanMove(DeltaTime * level / 2))
	{
		field.MoveDown(current, EndGame, EndCicle);
	}
}

float GlassWindow::IndentForLittleFigure(int size)
{
	int pixel = 48;
	return (float)(48 - size * 12) / 2;
}

void GlassWindow::RenderCurrentFigure(Shape & obj, hgeSprite* element[])
{
	for(int i = 0; i < obj.GetSize(); i ++)
	{
		for(int j = 0; j < obj.GetSize(); j ++)
		{
			if(obj.GetElementByPosition(i, j) != 0)
			{
				int value = obj.GetElementByPosition(i, j);
				float posX = 75 + (element[value]->GetHeight() * (float)obj.GetAsix_X() + j * element[value]->GetHeight());
				float posY = 102 + (element[value]->GetWidth() * (float)obj.GetAsix_Y() + i * element[value]->GetWidth());
				element[value]->Render( posX, posY);
			}
		}
	}
}
void GlassWindow::RenderLittleFigures(Shape & obj, float X, float Y, hgeSprite* mini_element[])
{
	for(int i = 0; i < obj.GetSize(); i ++)
	{
		for(int j = 0; j < obj.GetSize(); j ++)
		{
			if(obj.GetElementByPosition(i, j) != 0)
			{
				int value = obj.GetElementByPosition(i, j);
				float posX = X +((float)obj.GetAsix_X() + j * mini_element[value]->GetHeight());
				float posY = Y +((float)obj.GetAsix_Y() + i * mini_element[value]->GetWidth());
				mini_element[value]->Render(posX + IndentForLittleFigure(obj.GetSize()), posY);
			}
		}
	}
}
void GlassWindow::RenderField(Field & obj)
{
	float X = 75;
	float Y = 102;
	for(int i = 0; i < obj.GetHeight(); i ++)
	{
		for(int j = 0; j < obj.GetWight(); j ++)
		{
			int value = obj.GetElementByPosition(i, j);
			m_Elements[value]->Render( X + (m_Elements[value]->GetHeight() * j), 
									 Y + (m_Elements[value]->GetHeight() * i) );
		}
	}
}
bool GlassWindow::CanMove(float dt)
{
	m_currentDelay -= dt;
	if (m_currentDelay <= 0)
	{
		m_currentDelay = m_moveDelay;
		return true;
	}
	return false;
}