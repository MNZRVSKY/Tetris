#include "Hge.h"
#include "GUI.h"
#include "WindowsSwitcher.h"
#include "ResourcesManager.h"

HGE* Hge::m_instance = 0;


bool FrameFunc()
{
	HGE* hge = Hge::GetInstance();
	hgeGUI* gui = GUI::GetInstance();

	float dt = hge->Timer_GetDelta();

	int key = hge->Input_GetKey();
	int chr = hge->Input_GetChar();

	WindowsSwitcher* wndSwitcher = WindowsSwitcher::GetInstance();
	
	if (wndSwitcher->GetProgramExitStatus() == true)
	{
		return true;
	}

	wndSwitcher->KeyClick(key, chr);
	wndSwitcher->Update(dt);

	return false;
}


bool RenderFunc()
{
	

	hgeGUI* gui = GUI::GetInstance();
	Hge::GetInstance()->Gfx_BeginScene();
	Hge::GetInstance()->Gfx_Clear(0);
	
	gui->Render();

	Hge::GetInstance()->Gfx_EndScene();

	return false;
}

HGE* Hge::GetInstance()
{
	if (!m_instance)
	{
		m_instance = hgeCreate(HGE_VERSION);

		m_instance->System_SetState(HGE_LOGFILE, "Test.log");
		m_instance->System_SetState(HGE_FRAMEFUNC, FrameFunc);
		m_instance->System_SetState(HGE_FPS, HGEFPS_VSYNC);
		m_instance->System_SetState(HGE_RENDERFUNC, RenderFunc);
		m_instance->System_SetState(HGE_SHOWSPLASH, false);
		m_instance->System_SetState(HGE_TITLE, "Test");
		m_instance->System_SetState(HGE_SCREENWIDTH, 420);
		m_instance->System_SetState(HGE_SCREENHEIGHT, 700);
		m_instance->System_SetState(HGE_SCREENBPP, 32);
		m_instance->System_SetState(HGE_WINDOWED, true);

		
		m_instance->System_Initiate();
	}

	
    return m_instance;
}

Hge::Hge()
{

}

