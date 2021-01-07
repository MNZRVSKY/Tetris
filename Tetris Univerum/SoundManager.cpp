#include "SoundMAnager.h"
#include "SettingsManager.h"
#include "ResourcesManager.h"


SoundManager* SoundManager::m_instance = 0;

SoundManager* SoundManager::GetInstance()
{
	if (!m_instance)
	{
		m_instance = new SoundManager();
	}
    return m_instance;
}

SoundManager::SoundManager()
{

}

void SoundManager::PlayBackground()
{
	SettingsManager* sm = SettingsManager::GetInstance();
	bool needPlayBackground = sm->GetStaticSetting(STATIC_SETTING_PLAY_BACKGROUND) == "1";

	if (needPlayBackground)
	{
		ResourcesManager* rm = ResourcesManager::GetInstance();
		HCHANNEL backEffect = rm->GetBackgroundMusic(BACK_MUSIC_HARDCORE);
		HGE* hge = Hge::GetInstance();
		hge->Stream_Play(backEffect, true, 50);
	}
}

void SoundManager::StopBackground()
{
	ResourcesManager* rm = ResourcesManager::GetInstance();
	HCHANNEL backEffect = rm->GetBackgroundMusic(BACK_MUSIC_HARDCORE);
	HGE* hge = Hge::GetInstance();
	hge->Channel_Pause(backEffect);
}

void SoundManager::PlayMenuBackGround()
{
	SettingsManager* sm = SettingsManager::GetInstance();
	bool needPlayBackground = sm->GetStaticSetting(STATIC_SETTING_PLAY_BACKGROUND) == "1";

	if (needPlayBackground)
	{
		ResourcesManager* rm = ResourcesManager::GetInstance();
		HCHANNEL backEffect = rm->GetBackgroundMusic(BACK_MUSIC_CHILLOUT);
		HGE* hge = Hge::GetInstance();
		hge->Stream_Play(backEffect, true, 50);
	}
}
void SoundManager::StopMenuBackGround()
{
	ResourcesManager* rm = ResourcesManager::GetInstance();
	HCHANNEL backEffect = rm->GetBackgroundMusic(BACK_MUSIC_CHILLOUT);
	HGE* hge = Hge::GetInstance();
	hge->Channel_Pause(backEffect);
}

void SoundManager::PlayEffect(SoundEffectType effectType)
{
	SettingsManager* sm = SettingsManager::GetInstance();
	bool needPlayEffect = sm->GetStaticSetting(STATIC_SETTING_PLAY_SOUND_EFFECTS) == "1";

	if (needPlayEffect)
	{
		ResourcesManager* rm = ResourcesManager::GetInstance();
		HMUSIC effect = rm->GetSoundEffect(effectType);
		HGE* hge = Hge::GetInstance();
		hge->Effect_PlayEx(effect, 100);
	}
}