#include "MenuWindow.h"
#include "ResourcesManager.h"
#include "SoundManager.h"

MenuWindow::MenuWindow(MenuButtonType focusedButton)
{
	ResourcesManager* rm = ResourcesManager::GetInstance();

	m_background = new hgeSprite(rm->GetTexture(TEXTURE_BACKGROUND_MAIN_WND), 0, 0, 420, 700);
	m_onEscapeCallback = NULL;
	m_btnPressedCallback = NULL;

	m_buttonsLeftPadding = 130;
	m_buttonsStartDrawingY = 250;

	InitButtons(focusedButton);
}


MenuWindow::~MenuWindow()
{
	delete m_background;

	std::map<MenuButtonType, MenuButton*>::iterator iter = m_buttons.begin();
	for (; iter != m_buttons.end(); ++iter)
	{
		delete iter->second;
	}
}


void MenuWindow::OnEscape(WndEscapeCallback callback)
{
	m_onEscapeCallback = callback;
}

void MenuWindow::OnMenuButtonPressed(MenuButtonPressedCallback callback)
{
	m_btnPressedCallback = callback;
}

void MenuWindow::SelectPrevButton()
{
	SoundManager* soundManager = SoundManager::GetInstance();
	soundManager->PlayEffect(SOUND_EFFECT_FIGURE_MOVE);

	int index = GetFocusedButtonIndex();
	m_buttons[(MenuButtonType)index]->UnsetFocus();

	if (index == 0)
	{
		int lastIndex = m_buttons.size() - 1;
		m_buttons[(MenuButtonType)lastIndex]->SetFocus();
	}
	else
	{
		m_buttons[(MenuButtonType)(index - 1)]->SetFocus();
	}
}

void MenuWindow::SelectNextButton()
{
	SoundManager* soundManager = SoundManager::GetInstance();
	soundManager->PlayEffect(SOUND_EFFECT_FIGURE_MOVE);

	int index = GetFocusedButtonIndex();
	m_buttons[(MenuButtonType)index]->UnsetFocus();

	int lastIndex = m_buttons.size() - 1;
	if (index == lastIndex)
	{
		int firstIndex = 0;
		m_buttons[(MenuButtonType)firstIndex]->SetFocus();
	}
	else
	{
		m_buttons[(MenuButtonType)(index + 1)]->SetFocus();
	}
}

int MenuWindow::GetFocusedButtonIndex()
{
	std::map<MenuButtonType, MenuButton*>::iterator iter = m_buttons.begin();
	for (; iter != m_buttons.end(); ++iter)
	{
		if (iter->second->IsFocused())
		{
			return iter->first;
		}
	}

	return -1;
}

void MenuWindow::InitButtons(MenuButtonType focusedMenu)
{
	m_buttons[MENU_BUTTON_NEW_GAME] = new MenuButton("ÍÎÂÀ ÃÐÀ", m_buttonsLeftPadding, m_buttonsStartDrawingY);
	m_buttons[MENU_BUTTON_OPTIONS] = new MenuButton("ÎÏÖ²¯", m_buttonsLeftPadding, m_buttonsStartDrawingY + 50);
	m_buttons[MENU_BUTTON_HELP] = new MenuButton("ÄÎÏÎÌÎÃÀ", m_buttonsLeftPadding, m_buttonsStartDrawingY + 100);
	m_buttons[MENU_BUTTON_ABOUT] = new MenuButton("ÏÐÎ ÀÂÒÎÐÀ", m_buttonsLeftPadding, m_buttonsStartDrawingY + 150);
	m_buttons[MENU_BUTTON_EXIT] = new MenuButton("ÂÈÕ²Ä", m_buttonsLeftPadding, m_buttonsStartDrawingY + 200);

	m_buttons[focusedMenu]->SetFocus(false);
}

//=========================================================================

//				OVERLOADED METHODS

//=========================================================================

bool MenuWindow::KeyClick(int key, int chr)
{
	if (key == HGEK_ESCAPE)
	{
		if (m_onEscapeCallback != NULL)
		{
			m_onEscapeCallback();
		}
	}

	if (key == HGEK_UP)
	{
		SelectPrevButton();
	}

	if (key == HGEK_DOWN)
	{
		SelectNextButton();
	}

	std::map<MenuButtonType, MenuButton*>::iterator iter = m_buttons.begin();
	for (; iter != m_buttons.end(); ++iter)
	{
		iter->second->KeyClick(key, chr);
	}

	if ((key == HGEK_ENTER || key == HGEK_SPACE) && m_btnPressedCallback != NULL)
	{
		MenuButtonType buttonType = (MenuButtonType)GetFocusedButtonIndex();
		m_btnPressedCallback(buttonType);
	}

	return true;
}

void MenuWindow::Render()
{
	m_background->Render(0, 0);

	
	std::map<MenuButtonType, MenuButton*>::iterator iter = m_buttons.begin();
	for (; iter != m_buttons.end(); ++iter)
	{
		iter->second->Render();
	}
}

void MenuWindow::Update(float dt)
{

}

WindowType MenuWindow::GetType()
{
	return WINDOW_MAIN_MENU;
}


//=========================================================================