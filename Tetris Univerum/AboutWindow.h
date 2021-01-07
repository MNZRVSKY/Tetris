#pragma once
#include "Hge.h"
#include "GameWindow.h"


class AboutWindow : public GameWindow
{

private:
	hgeSprite* m_background;
	hgeFont* m_font;
	
	WndEscapeCallback m_onEscapeCallback;

public:
	AboutWindow();
	virtual ~AboutWindow();

	void OnEscape(WndEscapeCallback callback);
	WindowType GetType();

	bool KeyClick(int key, int chr);
	virtual void Render();
	virtual void Update(float dt);
};
