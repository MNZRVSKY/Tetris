#pragma once
#include "Hge.h"

#include "GameWindow.h"
#include "OptionsCheckbox.h"
#include <vector>


class OptionsWindow : public GameWindow
{

private:
	std::vector<OptionsCheckbox*> m_checkboxList;

	hgeSprite* m_background;
	hgeFont* m_font;

	WndEscapeCallback m_onEscapeCallback;

	void FocusPrevCombobox();
	void FocusNextCombobox();
	int GetFocusedComboboxIndex();
	void ChangeFocusedComboboxState();

public:
	OptionsWindow();
	virtual ~OptionsWindow();

	void OnEscape(WndEscapeCallback callback);
	WindowType GetType();

	bool KeyClick(int key, int chr);
	virtual void Render();
	virtual void Update(float dt);
};
