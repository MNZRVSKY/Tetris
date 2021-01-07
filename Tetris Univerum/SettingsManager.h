#pragma once
#include "Enums.h"
#include <string>
#include <map>
#include "TypeDefs.h"


class SettingsManager
{
private:
	static SettingsManager* m_instance;
	SettingsManager();

	DynamicSettingMap m_dynamicSettings;
	StaticSettingMap m_staticSettings;

	std::string m_settingsFilename;

	void SaveStaticSettingsToFile();
	void LoadStaticSettingsFromFile();
public:
	
	static SettingsManager* GetInstance();
	static void InitDefaults();

	void SetDynamicSetting(DynamicSettingType type, std::string value);
	std::string GetDynamicSetting(DynamicSettingType type);

	void SetStaticSetting(StaticSettingType type, std::string value);
	std::string GetStaticSetting(StaticSettingType type);
};

