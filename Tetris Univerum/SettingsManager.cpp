#include "SettingsManager.h"
#include <fstream>
#include <stdint.h>
#include <sstream>


SettingsManager* SettingsManager::m_instance = 0;

SettingsManager* SettingsManager::GetInstance()
{
	if (!m_instance)
	{
		m_instance = new SettingsManager();
	}
    return m_instance;
}

SettingsManager::SettingsManager()
{
	m_settingsFilename = "settings.bin";
}

void SettingsManager::InitDefaults()
{
	std::stringstream firstFocusedBtnStr;
	firstFocusedBtnStr << MENU_BUTTON_NEW_GAME;
	m_instance->SetDynamicSetting(DYNAMIC_SETTING_LAST_PRESSED_BUTTON, firstFocusedBtnStr.str());

	m_instance->SetDynamicSetting(DYNAMIC_SETTING_GAME_PAUSED, "0");
	m_instance->SetDynamicSetting(DYNAMIC_SETTING_GAME_OVERED, "0");

	m_instance->LoadStaticSettingsFromFile();
}

void SettingsManager::SetDynamicSetting(DynamicSettingType type, std::string value)
{
	m_dynamicSettings[type] = value;
}

std::string SettingsManager::GetDynamicSetting(DynamicSettingType type)
{
	return m_dynamicSettings[type];
}

void SettingsManager::SetStaticSetting(StaticSettingType type, std::string value)
{
	m_staticSettings[type] = value;
	SaveStaticSettingsToFile();
}
	
std::string SettingsManager::GetStaticSetting(StaticSettingType type)
{
	return m_staticSettings[type];
}


void SettingsManager::SaveStaticSettingsToFile()
{
	std::ofstream ofile(m_settingsFilename.c_str(), std::ifstream::binary);
    if(ofile)
    {
		ofile.clear();
        for(StaticSettingMap::const_iterator iter = m_staticSettings.begin(); iter != m_staticSettings.end(); ++iter)
		{
			std::stringstream settingTypeStr;
			settingTypeStr << iter->first;

			std::string line(settingTypeStr.str());
			line += "|";
			line += iter->second;

			ofile.write(line.c_str(), line.size() + 1);
			ofile << "\n";
		}    
		ofile.close();
    }
}

void SettingsManager::LoadStaticSettingsFromFile()
{
	std::ifstream infile (m_settingsFilename.c_str());
	
	std::string line;
	while(std::getline(infile, line)) 
	{
		line = line.substr(0, line.size() - 1);
		int delimeterPos = line.find("|");
		std::string typeStr = line.substr(0, delimeterPos);
		std::string valueStr = line.substr(delimeterPos + 1, line.size());

		StaticSettingType type = (StaticSettingType)std::stoi(typeStr);
		m_staticSettings[type] = valueStr;
	}

	infile.close();
}