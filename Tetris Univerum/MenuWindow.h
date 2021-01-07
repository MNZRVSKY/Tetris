#pragma once
#include "Hge.h"
#include "WindowsSwitcher.h"
#include "GameWindow.h"
#include "MenuButton.h"
#include <map>


class MenuWindow : public GameWindow
{

private:
	hgeSprite* m_background;
	std::map<MenuButtonType, MenuButton*> m_buttons;

	WndEscapeCallback m_onEscapeCallback;
	MenuButtonPressedCallback m_btnPressedCallback;

	int m_buttonsLeftPadding;
	int m_buttonsStartDrawingY;

	void SelectPrevButton();
	void SelectNextButton();
	void InitButtons(MenuButtonType focusedButton);
	int GetFocusedButtonIndex();
public:
	MenuWindow(MenuButtonType focusedButton);
	virtual ~MenuWindow();

	void OnEscape(WndEscapeCallback callback);
	void OnMenuButtonPressed(MenuButtonPressedCallback callback);
	WindowType GetType();

	bool KeyClick(int key, int chr);
	virtual void Render();
	virtual void Update(float dt);
};

