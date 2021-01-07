#include "HelpWindow.h"
#include "ResourcesManager.h"


HelpWindow::HelpWindow(void)
{
	ResourcesManager* rm = ResourcesManager::GetInstance();
	m_font = rm->GetFont(FONT_MAIN_WND_MENU);
	m_background = new hgeSprite(rm->GetTexture(TEXTURE_BACKGROUND_HELP_WND), 0, 0, 420, 700);
}


HelpWindow::~HelpWindow(void)
{

}

void HelpWindow::OnEscape(WndEscapeCallback callback)
{
	m_onEscapeCallback = callback;
}

WindowType HelpWindow::GetType()
{
	return WINDOW_HELP;
}

//=========================================================================

//				OVERLOADED METHODS

//=========================================================================

bool HelpWindow::KeyClick(int key, int chr)
{
	if (key == HGEK_ESCAPE)
	{
		if (m_onEscapeCallback != NULL)
		{
			m_onEscapeCallback();
		}
	}

	return true;
}

void HelpWindow::Render()
{
	m_background->Render(0, 0);
	m_font->SetScale((float)0.6);
	m_font->Render(200, 270, HGETEXT_LEFT, "ÂË²ÂÎ\nÂÏÐÀÂÎ\nÂÍÈÇ\nÏÎÂÎÐÎÒ Ô²ÃÓÐÈ\nÏÀÓÇÀ\nÓÒÐÈÌÀÒÈ ÔÈÃÓÐÓ");
	m_font->Render(100, 270, HGETEXT_LEFT, "LEFT\nRIGHT\nDOWN\nUP\nSPACE\nENTER");
}

void HelpWindow::Update(float dt)
{

}