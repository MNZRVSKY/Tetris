#pragma once
#include "Enums.h"

class SoundManager
{
private:
	static SoundManager* m_instance;
	SoundManager();

public:
	
	static SoundManager* GetInstance();

	void PlayBackground();
	void StopBackground();

	void PlayMenuBackGround();
	void StopMenuBackGround();

	void PlayEffect(SoundEffectType effectType);
};
