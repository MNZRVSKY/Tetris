#pragma once

#include "include/hde/hge.h"
#include "include/hde/hgefont.h"
#include <string>
#include <map>
#include "Enums.h"
#include "TypeDefs.h"

class ResourcesManager
{

private:
	//std::map<MenuButtonType, MenuButton*> m_buttons;

	TexturesMap m_texturesList;
	FontsMap m_fontsList;
	SoundEffectsMap m_effectSoundsList;
	BackgroundMusicMap m_backgroundSound;

	
	static ResourcesManager* m_instance;
	
	ResourcesManager();

	void InitTextures();
	void InitFonts();
	void InitSoundEffects();
	void InitBackgroundMusic();

	void FreeTextures();
	void FreeFonts();
	void FreeSoundEffects();
	void FreeBackgroundMusic();
public:
	static ResourcesManager* GetInstance();

	void Init();

	HTEXTURE  GetTexture(TextureType type);
	hgeFont* GetFont(FontType type);
	HMUSIC GetSoundEffect(SoundEffectType type);
	HCHANNEL GetBackgroundMusic(BackgroundMusicType type);
	
	void Free();
};

