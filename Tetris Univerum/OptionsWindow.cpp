#include "OptionsWindow.h"
#include "ResourcesManager.h"
#include "SettingsManager.h"
#include "SoundManager.h"

void OnSoundEffectsCheckBoxChanged(bool isChecked)
{
	SettingsManager* sn = SettingsManager::GetInstance();
	if (isChecked)
	{
		sn->SetStaticSetting(STATIC_SETTING_PLAY_SOUND_EFFECTS, "1");
	}
	else
	{
		sn->SetStaticSetting(STATIC_SETTING_PLAY_SOUND_EFFECTS, "0");
	}
}

void OnBackMusicCheckBoxChanged(bool isChecked)
{
	SoundManager* soundManager = SoundManager::GetInstance();
	SettingsManager* sn = SettingsManager::GetInstance();
	if (isChecked)
	{
		sn->SetStaticSetting(STATIC_SETTING_PLAY_BACKGROUND, "1");
		soundManager->PlayMenuBackGround();
	}
	else
	{
		sn->SetStaticSetting(STATIC_SETTING_PLAY_BACKGROUND, "0");
		soundManager->StopMenuBackGround();
	}
}


OptionsWindow::OptionsWindow(void)
{
	ResourcesManager* rm = ResourcesManager::GetInstance();
	m_font = rm->GetFont(FONT_MAIN_WND_MENU);
	m_background = new hgeSprite(rm->GetTexture(TEXTURE_BACKGROUND_OPTIONS_WND), 0, 0, 420, 700);

	SettingsManager* sn = SettingsManager::GetInstance();

	bool checkedSoundEffectsCheckbox = sn->GetStaticSetting(STATIC_SETTING_PLAY_SOUND_EFFECTS) == "1";
	OptionsCheckbox* soundEffectsCheckBox = new OptionsCheckbox("програвати звукові ефекти", 30, 250, true, checkedSoundEffectsCheckbox);
	soundEffectsCheckBox->OnCheckStateChanged(OnSoundEffectsCheckBoxChanged);
	m_checkboxList.push_back(soundEffectsCheckBox);

	bool checkedBackMusicCheckBox = sn->GetStaticSetting(STATIC_SETTING_PLAY_BACKGROUND) == "1";
	OptionsCheckbox* backMusicCheckBox = new OptionsCheckbox("програвати фонову музику", 30, 320, false, checkedBackMusicCheckBox);
	backMusicCheckBox->OnCheckStateChanged(OnBackMusicCheckBoxChanged);
	m_checkboxList.push_back(backMusicCheckBox);
}


OptionsWindow::~OptionsWindow(void)
{

}

void OptionsWindow::OnEscape(WndEscapeCallback callback)
{
	m_onEscapeCallback = callback;
}

WindowType OptionsWindow::GetType()
{
	return WINDOW_OPTIONS;
}

//=========================================================================

//				OVERLOADED METHODS

//=========================================================================

bool OptionsWindow::KeyClick(int key, int chr)
{
	if (key == HGEK_ESCAPE)
	{
		if (m_onEscapeCallback != NULL)
		{
			m_onEscapeCallback();
		}
		return false;
	} else if (key == HGEK_UP)
	{
		FocusPrevCombobox();
	}
	else if (key == HGEK_DOWN)
	{
		FocusNextCombobox();
	}
	else if (chr == 32)
	{
		ChangeFocusedComboboxState();
	}

	return false;
}

void OptionsWindow::Render()
{
	
	m_background->Render(0, 0);
	std::vector<OptionsCheckbox*>::iterator iter = m_checkboxList.begin();
	for (; iter != m_checkboxList.end(); ++iter)
	{
		(*iter)->Render();
	}
	m_font->SetColor(ARGB(255, 65, 131, 166));
	m_font->Render(130, 450, HGETEXT_LEFT, "SPACE - ЗМІНИТИ");
}

void OptionsWindow::Update(float dt)
{

}

void OptionsWindow::FocusPrevCombobox()
{
	 int focusedIndex = GetFocusedComboboxIndex();
	 m_checkboxList[focusedIndex]->UnsetFocus();

	 if (focusedIndex == 0)
	 {
		 int lastIndex = m_checkboxList.size() - 1;
		 m_checkboxList[lastIndex]->SetFocus();
	 }
	 else
	 {
		 int prevIndex = focusedIndex - 1;
		 m_checkboxList[prevIndex]->SetFocus();
	 }
}

void OptionsWindow::FocusNextCombobox()
{
	int focusedIndex = GetFocusedComboboxIndex();
	 m_checkboxList[focusedIndex]->UnsetFocus();
	 
	 if (focusedIndex == m_checkboxList.size() - 1)
	 {
		 (*m_checkboxList.begin())->SetFocus();
	 }
	 else
	 {
		 int nextIndex = focusedIndex + 1;
		 m_checkboxList[nextIndex]->SetFocus();
	 }
}

void OptionsWindow::ChangeFocusedComboboxState()
{
	int focusedIndex = GetFocusedComboboxIndex();

	if (m_checkboxList[focusedIndex]->IsChecked())
	{
		m_checkboxList[focusedIndex]->SetUnchecked();
	}
	else
	{
		m_checkboxList[focusedIndex]->SetChecked();
	}
}

int OptionsWindow::GetFocusedComboboxIndex()
{
	int index = -1;
	std::vector<OptionsCheckbox*>::iterator iter = m_checkboxList.begin();
	for (; iter != m_checkboxList.end(); ++iter)
	{
		if ((*iter)->IsFocused() == true)
		{
			index = iter - m_checkboxList.begin();
			break;
		}
	}
	return index;
}