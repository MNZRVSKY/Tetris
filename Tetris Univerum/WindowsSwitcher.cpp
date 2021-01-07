#include "WindowsSwitcher.h"
#include "MenuWindow.h"
#include "AboutWindow.h"
#include "HelpWindow.h"
#include "OptionsWindow.h"
#include "GlassWindow.h"
#include "SettingsManager.h"
#include "SoundManager.h"
#include "GUI.h"
#include <sstream>


WindowsSwitcher* WindowsSwitcher::m_instance = 0;


//>>>>>>>>>>>>>> CALLBACKS

void OnEscapeMainMenuWindow()
{
	WindowsSwitcher* wndSwitcher = WindowsSwitcher::GetInstance();
	GameWindow* currentWindow = wndSwitcher->GetCurrentWindow();
	SoundManager* soundManager = SoundManager::GetInstance();

	switch(currentWindow->GetType())
	{
		case WINDOW_MAIN_MENU:
				wndSwitcher->SetProgramExitStatus(true);
			break;

		
		case WINDOW_GLASS:
				soundManager->PlayMenuBackGround();
				soundManager->StopBackground();
				wndSwitcher->OpenWindow(WINDOW_MAIN_MENU);
			break;

		case WINDOW_OPTIONS:
		case WINDOW_HELP:
		case WINDOW_ABOUT:
				wndSwitcher->OpenWindow(WINDOW_MAIN_MENU);
			break;
	}
}

void OnButtonPressedMainMenuWindow(MenuButtonType btnType)
{
	SettingsManager* settingsManager = SettingsManager::GetInstance();
	WindowsSwitcher* windowsSwicher = WindowsSwitcher::GetInstance();

	std::stringstream btnTypeStr;
	btnTypeStr << btnType;
	settingsManager->SetDynamicSetting(DYNAMIC_SETTING_LAST_PRESSED_BUTTON, btnTypeStr.str());

	switch(btnType)
	{
		case MENU_BUTTON_NEW_GAME:
			windowsSwicher->OpenWindow(WINDOW_GLASS);
			break;

		case MENU_BUTTON_OPTIONS:
			windowsSwicher->OpenWindow(WINDOW_OPTIONS);
			break;

		case MENU_BUTTON_HELP:
			windowsSwicher->OpenWindow(WINDOW_HELP);
			break;

		case MENU_BUTTON_ABOUT:
			windowsSwicher->OpenWindow(WINDOW_ABOUT);
			break;

		case MENU_BUTTON_EXIT:
			windowsSwicher->SetProgramExitStatus(true);
			break;

		default:
			throw new std::exception("Cann't processs MenuButtonType = " + btnType);
	}
}

//<<<<<<<<<<<<<< CALLBACKS

WindowsSwitcher* WindowsSwitcher::GetInstance()
{
	if (!m_instance)
	{
		m_instance = new WindowsSwitcher();
	}
    return m_instance;
}

bool WindowsSwitcher::KeyClick(int key, int chr)
{
	if (m_currentWindow != NULL)
	{
		return m_currentWindow->KeyClick(key, chr);
	}
	return false;
}

void WindowsSwitcher::Update(float dt)
{
	m_currentWindow->Update(dt);
}

GameWindow* WindowsSwitcher::GetCurrentWindow()
{
	return m_currentWindow;
}

void WindowsSwitcher::OpenWindow(WindowType type)
{
	if (m_currentWindow != NULL)
	{
		GUI::GetInstance()->EnableCtrl(m_currentWindow->id, false);
		GUI::GetInstance()->DelCtrl(m_currentWindow->id);
		GUI::GetInstance()->Reset();
	}

	switch(type)
	{
		case WINDOW_MAIN_MENU:
			{
				SettingsManager* settingsManager = SettingsManager::GetInstance();

				std::string focusedButtonStr = settingsManager->GetDynamicSetting(DYNAMIC_SETTING_LAST_PRESSED_BUTTON);
				MenuButtonType type = (MenuButtonType)std::stoi(focusedButtonStr);

				MenuWindow* menuWindow = new MenuWindow(type);
				menuWindow->OnEscape(OnEscapeMainMenuWindow);
				menuWindow->OnMenuButtonPressed(OnButtonPressedMainMenuWindow);
				m_currentWindow = menuWindow;
			}
			break;
			
		case WINDOW_OPTIONS:
			{
				OptionsWindow* optionsWindow = new OptionsWindow();
				optionsWindow->OnEscape(OnEscapeMainMenuWindow);
				m_currentWindow = optionsWindow;
			}
			break;

		case WINDOW_GLASS:
			{
				GlassWindow* glassWindow = new GlassWindow();
				glassWindow->OnEscape(OnEscapeMainMenuWindow);
				m_currentWindow = glassWindow;
			}
			break;
			
		case WINDOW_HELP:
			{
				HelpWindow* helpWindow = new HelpWindow();
				helpWindow->OnEscape(OnEscapeMainMenuWindow);
				m_currentWindow = helpWindow;
			}
			break;
			
		case WINDOW_ABOUT:
			{
				AboutWindow* aboutWindow = new AboutWindow();
				aboutWindow->OnEscape(OnEscapeMainMenuWindow);
				m_currentWindow = aboutWindow;
			}
			break;
	}
	
	
	GUI::GetInstance()->AddCtrl(m_currentWindow);
}

void WindowsSwitcher::SetProgramExitStatus(bool needProgramExit)
{
	m_needProgramExit = needProgramExit;
}

bool WindowsSwitcher::GetProgramExitStatus()
{
	return m_needProgramExit;
}

WindowsSwitcher::WindowsSwitcher()
{
	m_needProgramExit = false;
	m_currentWindow = NULL;
}

WindowsSwitcher::~WindowsSwitcher(void)
{

}