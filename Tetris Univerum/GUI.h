#pragma once

#include "include/hde/hgegui.h"

class GUI
{
private:
	static hgeGUI* m_instance;
	GUI();

public:
	
	static hgeGUI* GetInstance();
};
