#include "GUI.h"

hgeGUI* GUI::m_instance = 0;

hgeGUI* GUI::GetInstance()
{
	if (!m_instance)
	{
		m_instance = new hgeGUI();
	}
    return m_instance;
}

GUI::GUI()
{

}