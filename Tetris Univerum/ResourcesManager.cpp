
#include "ResourcesManager.h"
#include "Hge.h"
#include "include/hde/hgeresource.h"

ResourcesManager* ResourcesManager::m_instance = 0;

//===========================================================================================

//									PUBLIC METHODS

//===========================================================================================

ResourcesManager* ResourcesManager::GetInstance()
{
	if (!m_instance)
	{
		m_instance = new ResourcesManager();
	}
    return m_instance;
}

void ResourcesManager::Init()
{
	InitTextures();
	InitFonts();
	InitSoundEffects();
	InitBackgroundMusic();
}


HTEXTURE ResourcesManager::GetTexture(TextureType type)
{
	return m_texturesList[type];
}

hgeFont* ResourcesManager::GetFont(FontType type)
{
	return m_fontsList[type];
}

HMUSIC ResourcesManager::GetSoundEffect(SoundEffectType type)
{
	return m_effectSoundsList[type];
}

HCHANNEL ResourcesManager::GetBackgroundMusic(BackgroundMusicType type)
{
	return m_backgroundSound[type];
}

//===========================================================================================

//									PRIVATE METHODS

//===========================================================================================

ResourcesManager::ResourcesManager()
{
}

//TEXTURES

void ResourcesManager::InitTextures()
{
	HGE *hge = Hge::GetInstance();
	
	m_texturesList[TEXTURE_BRIDGE_EMPTY] = hge->Texture_Load("resources/textures/figures_color/empty.jpg");
	m_texturesList[TEXTURE_BRIDGE_BLUE] = hge->Texture_Load("resources/textures/figures_color/blue.jpg");
	m_texturesList[TEXTURE_BRIDGE_GREEN] = hge->Texture_Load("resources/textures/figures_color/green.jpg");
	m_texturesList[TEXTURE_BRIDGE_LIGHT_BLUE] = hge->Texture_Load("resources/textures/figures_color/light_blue.jpg");
	m_texturesList[TEXTURE_BRIDGE_LIGHT_YELLOW] = hge->Texture_Load("resources/textures/figures_color/light_yello.jpg");
	m_texturesList[TEXTURE_BRIDGE_ORANGE] = hge->Texture_Load("resources/textures/figures_color/orange.jpg");
	m_texturesList[TEXTURE_BRIDGE_PURPLE] = hge->Texture_Load("resources/textures/figures_color/purple.jpg");
	m_texturesList[TEXTURE_BRIDGE_YELLO] = hge->Texture_Load("resources/textures/figures_color/yello.jpg");


	m_texturesList[TEXTURE_MINI_BRIDGE_BLUE] = hge->Texture_Load("resources/textures/mini_figures_color/blue.jpg");
	m_texturesList[TEXTURE_MINI_BRIDGE_GREEN] = hge->Texture_Load("resources/textures/mini_figures_color/green.jpg");   
	m_texturesList[TEXTURE_MINI_BRIDGE_LIGHT_BLUE] = hge->Texture_Load("resources/textures/mini_figures_color/light_blue.jpg");   
	m_texturesList[TEXTURE_MINI_BRIDGE_LIGHT_YELLOW] = hge->Texture_Load("resources/textures/mini_figures_color/light_yello.jpg");   
	m_texturesList[TEXTURE_MINI_BRIDGE_ORANGE] = hge->Texture_Load("resources/textures/mini_figures_color/orange.jpg");  
	m_texturesList[TEXTURE_MINI_BRIDGE_PURPLE] = hge->Texture_Load("resources/textures/mini_figures_color/purple.jpg");   
	m_texturesList[TEXTURE_MINI_BRIDGE_YELLO] = hge->Texture_Load("resources/textures/mini_figures_color/yello.jpg");   

	m_texturesList[TEXTURE_BACKGROUND_GLASS_WND] = hge->Texture_Load("resources/textures/background/glass_wnd.jpg");
	m_texturesList[TEXTURE_BACKGROUND_MAIN_WND] = hge->Texture_Load("resources/textures/background/main_menu_wnd.png");
	m_texturesList[TEXTURE_BACKGROUND_OPTIONS_WND] = hge->Texture_Load("resources/textures/background/options_menu_wnd.png");
	m_texturesList[TEXTURE_BACKGROUND_ABOUT_WND] = hge->Texture_Load("resources/textures/background/about_wnd.png");
	m_texturesList[TEXTURE_BACKGROUND_HELP_WND] = hge->Texture_Load("resources/textures/background/help_wnd.png");

	m_texturesList[TEXTURE_COMBOBOX_CHECKED] = hge->Texture_Load("resources/textures/controls/checkbox/checked_state.png");
	m_texturesList[TEXTURE_COMBOBOX_UNCHECK] = hge->Texture_Load("resources/textures/controls/checkbox/unchecked_state.png");

	m_texturesList[TEXTURE_MENU_BTN_LINE] = hge->Texture_Load("resources/textures/menu/menu_button_line.png");

	m_texturesList[TEXTURE_PARTICLES] = hge->Texture_Load("resources/textures/particles/particles.png");
}

void ResourcesManager::FreeTextures()
{
	HGE *hge = Hge::GetInstance();

	TexturesMap::iterator iter = m_texturesList.begin();
	for (; iter != m_texturesList.end(); ++iter)
	{
		hge->Texture_Free(iter->second);
	}
}

//FONTS

void ResourcesManager::InitFonts()
{
	m_fontsList[FONT_GLASS_WND_OUTPUTS] = new hgeFont("resources/fonts/font2.fnt");
	m_fontsList[FONT_MAIN_WND_MENU] = new hgeFont("resources/fonts/font2.fnt");
}

void ResourcesManager::FreeFonts()
{
	FontsMap::iterator iter = m_fontsList.begin();
	for (; iter != m_fontsList.end(); ++iter)
	{
		delete iter->second;
	}
}

//SOUND EFFECTS

void ResourcesManager::InitSoundEffects()
{
	HGE *hge = Hge::GetInstance();
	
	m_effectSoundsList[SOUND_EFFECT_FIGURE_MOVE] =  hge->Effect_Load("resources/sound/sound_effect/figure_move.wav");
	m_effectSoundsList[SOUND_EFFECT_FIGURE_ROTATE] = hge->Effect_Load("resources/sound/sound_effect/figure_rotate.wav");
	m_effectSoundsList[SOUND_EFFECT_FIGURE_DOWN] = hge->Effect_Load("resources/sound/sound_effect/figure_down.wav");
	m_effectSoundsList[SOUND_EFFECT_LINE_CRASH] = hge->Effect_Load("resources/sound/sound_effect/crash_line.wav");
}

void ResourcesManager::FreeSoundEffects()
{
	HGE *hge = Hge::GetInstance();

	SoundEffectsMap::iterator iter = m_effectSoundsList.begin();
	for (; iter != m_effectSoundsList.end(); ++iter)
	{
		hge->Effect_Free(iter->second);
	}
}

//BACKGROUND SOUNDS

void ResourcesManager::InitBackgroundMusic()
{
	HGE *hge = Hge::GetInstance();

	m_backgroundSound[BACK_MUSIC_HARDCORE] = hge->Stream_Load("resources/sound/background/hardcore.wav");
	m_backgroundSound[BACK_MUSIC_CHILLOUT] = hge->Stream_Load("resources/sound/background/chillout.wav");
}

void ResourcesManager::FreeBackgroundMusic()
{
	HGE *hge = Hge::GetInstance();

	BackgroundMusicMap::iterator iter = m_backgroundSound.begin();
	for (; iter != m_backgroundSound.end(); ++iter)
	{
		hge->Stream_Free(iter->second);
	}
}

//destructor
void ResourcesManager::Free()
{
	FreeTextures();
	FreeFonts();
	FreeSoundEffects();
	FreeBackgroundMusic();
}