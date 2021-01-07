#include "AboutWindow.h"
#include "ResourcesManager.h"


AboutWindow::AboutWindow(void)
{
	ResourcesManager* rm = ResourcesManager::GetInstance();
	m_font = rm->GetFont(FONT_MAIN_WND_MENU);
	m_background = new hgeSprite(rm->GetTexture(TEXTURE_BACKGROUND_ABOUT_WND), 0, 0, 420, 700);
}


AboutWindow::~AboutWindow(void)
{

}

void AboutWindow::OnEscape(WndEscapeCallback callback)
{
	m_onEscapeCallback = callback;
}

WindowType AboutWindow::GetType()
{
	return WINDOW_ABOUT;
}

//=========================================================================

//				OVERLOADED METHODS

//=========================================================================

bool AboutWindow::KeyClick(int key, int chr)
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

void AboutWindow::Render()
{
	m_background->Render(0, 0);
	m_font->SetScale((float)0.6);
	m_font->Render(50, 280, HGETEXT_LEFT, "Манжеровський Роман");
	m_font->Render(50, 310, HGETEXT_LEFT, "e-mail: manzherovskyi.roma@gmail.com");
	m_font->Render(50, 340, HGETEXT_LEFT, "skype: x07770x");
	m_font->Render(50, 370, HGETEXT_LEFT, "tel: 097 869 74 24");
}

void AboutWindow::Update(float dt)
{
}