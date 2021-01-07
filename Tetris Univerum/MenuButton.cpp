#include "MenuButton.h"
#include "ResourcesManager.h"


MenuButton::MenuButton(std::string text, int posX, int posY, bool focused)
{
	m_focused = focused;
	m_text = text;
	m_posX = posX;
	m_posY = posY;

	m_alignLeft = 20;

	ResourcesManager* rm = ResourcesManager::GetInstance();
	m_font = rm->GetFont(FONT_MAIN_WND_MENU);
	m_font->SetScale((float)0.8);

	HTEXTURE btnLineTexture = rm->GetTexture(TEXTURE_MENU_BTN_LINE);
	HGE* hge = Hge::GetInstance();
	m_focusedLine = new hgeSprite(btnLineTexture, 0, 0, (float)hge->Texture_GetWidth(btnLineTexture), (float)hge->Texture_GetHeight(btnLineTexture));

	m_textFocusedColor = ARGB(255, 255, 255, 255);
	m_textUnfocusedColor = ARGB(255, 65, 131, 166);
}

MenuButton::~MenuButton()
{
	delete m_focusedLine;
}

bool MenuButton::KeyClick(int key, int chr)
{
	return true;
}

void MenuButton::Render()
{
	m_font->SetColor(GetFontColor());
	m_font->Render((float)m_posX + m_alignLeft, (float)m_posY + 7, HGETEXT_LEFT, m_text.c_str());

	if (m_focused)
	{
		m_focusedLine->Render((float)m_posX, (float)m_posY);
	}
}

void MenuButton::Update(float dt)
{

}

void MenuButton::SetFocus(bool playEffect)
{
	m_focused = true;
}

void MenuButton::UnsetFocus(bool playEffect)
{
	m_focused = false;
}

bool MenuButton::IsFocused()
{
	return m_focused;
}

DWORD MenuButton::GetFontColor()
{
	if (m_focused)
	{
		return m_textFocusedColor;
	}
	else
	{
		return m_textUnfocusedColor;
	}
}