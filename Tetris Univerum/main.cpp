#pragma once

#include "include/hde/hge.h"
#include "include/hde/hgegui.h"
#include "ResourcesManager.h"
#include "WindowsSwitcher.h"
#include "SettingsManager.h"
#include "SoundManager.h"
#include "GUI.h"
#include "Hge.h"
#include <vector>


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	hgeGUI* gui = GUI::GetInstance();
	HGE *hge = Hge::GetInstance();

	//������������ �������
	ResourcesManager::GetInstance()->Init();

	//������������ �������� ������������
	SettingsManager::GetInstance()->InitDefaults();
	
	gui->SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);
	gui->Enter();

	WindowsSwitcher* windowsSwitchwer = WindowsSwitcher::GetInstance();
	windowsSwitchwer->OpenWindow(WINDOW_MAIN_MENU);

	SoundManager* soundManager = SoundManager::GetInstance();
	soundManager->PlayMenuBackGround();
		
	hge->System_Start();

	delete gui;

	//���������� �������
	ResourcesManager::GetInstance()->Free();


	hge->System_Shutdown();
	hge->Release();

	return 0;
}
