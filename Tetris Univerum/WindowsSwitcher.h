#pragma once
#include "Hge.h"
#include "GameWindow.h"
#include <map>

class WindowsSwitcher
{
public:
	static WindowsSwitcher* GetInstance();
	bool KeyClick(int key, int chr);

	GameWindow* GetCurrentWindow();

	void SetProgramExitStatus(bool needProgramExit);
	bool GetProgramExitStatus();
	void OpenWindow(WindowType type);
	void Update(float dt);
private:
	GameWindow* m_currentWindow;
	bool m_needProgramExit;

	static WindowsSwitcher* m_instance;
	WindowsSwitcher();
	~WindowsSwitcher();
};

