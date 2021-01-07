#pragma once
#include "Hge.h"
#include "include/hde/hgefont.h"
#include <string>
#include <functional>

class MenuButton : public hgeGUIObject
{

private:
	bool m_focused;
	hgeFont* m_font;
	hgeSprite* m_focusedLine;
	std::string m_text;
	int m_posX;
	int m_posY;
	int m_alignLeft;

	DWORD m_textFocusedColor;
	DWORD m_textUnfocusedColor;

	DWORD GetFontColor();

public:
	MenuButton(std::string text, int posX, int posY, bool focused = false);
	virtual ~MenuButton();

	virtual bool KeyClick(int key, int chr);
	virtual void Render();
	virtual void Update(float dt);

	void SetFocus(bool playEffect = true);
	void UnsetFocus(bool playEffect = true);
	bool IsFocused();
};

