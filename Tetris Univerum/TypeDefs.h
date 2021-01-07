#pragma once
#include "Enums.h"
#include "Hge.h"
#include "include/hde/hgefont.h"
#include <map>

typedef void (*WndEscapeCallback)();
typedef void (*MenuButtonPressedCallback)(MenuButtonType);
typedef void (*OptionsCheckboxStateChangeCallback)(bool);

typedef std::map<TextureType, HTEXTURE> TexturesMap;

typedef std::map<FontType, hgeFont*> FontsMap;
typedef std::map<SoundEffectType, HMUSIC> SoundEffectsMap;
typedef std::map<BackgroundMusicType, HCHANNEL> BackgroundMusicMap;

typedef std::map<DynamicSettingType, std::string> DynamicSettingMap;
typedef std::map<StaticSettingType, std::string> StaticSettingMap;