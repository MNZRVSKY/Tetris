#pragma once
#include "Hge.h"
#include "include/hde/hgefont.h"
#include <string>
#include <functional>
#include "TypeDefs.h"

class OptionsCheckbox : public hgeGUIObject
{

private:
	bool m_focused;
	hgeFont* m_font;
	std::string m_text;

	bool m_isChecked;
	hgeSprite* m_stateIco;

	HTEXTURE m_checkedTexture;
	HTEXTURE m_uncheckedTexture;

	OptionsCheckboxStateChangeCallback m_onStateChangeCallback;

	int m_posX;
	int m_posY;

	DWORD m_textFocusedColor;
	DWORD m_textUnfocusedColor;

public:
	OptionsCheckbox(std::string text, int posX, int posY, bool focused = false, bool checked = true);
	virtual ~OptionsCheckbox();

	void OnCheckStateChanged(OptionsCheckboxStateChangeCallback stateChangeCallback);

	virtual bool KeyClick(int key, int chr);
	virtual void Render();
	virtual void Update(float dt);

	void SetFocus(bool playEffect = true);
	void UnsetFocus(bool playEffect = true);

	void SetChecked(bool playEffect = true);
	void SetUnchecked(bool playEffect = true);

	bool IsFocused();
	bool IsChecked();
};

