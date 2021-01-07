#include "OptionsCheckbox.h"
#include "ResourcesManager.h"
#include "SoundManager.h"


OptionsCheckbox::OptionsCheckbox(std::string text, int posX, int posY, bool focused, bool checked)
{
	m_focused = focused;
	m_text = text;
	m_posX = posX;
	m_posY = posY;
	m_isChecked = checked;


	ResourcesManager* rm = ResourcesManager::GetInstance();
	m_font = rm->GetFont(FONT_MAIN_WND_MENU);
	m_font->SetScale((float)0.7);

	HGE* hge = Hge::GetInstance();

	m_checkedTexture = rm->GetTexture(TEXTURE_COMBOBOX_CHECKED);
	m_uncheckedTexture = rm->GetTexture(TEXTURE_COMBOBOX_UNCHECK);

	if (checked)
	{
		m_stateIco = new hgeSprite(m_checkedTexture, 0, 0, (float)hge->Texture_GetWidth(m_checkedTexture), (float)hge->Texture_GetHeight(m_checkedTexture));
	}
	else
	{
		m_stateIco = new hgeSprite(m_uncheckedTexture, 0, 0, (float)hge->Texture_GetWidth(m_uncheckedTexture), (float)hge->Texture_GetHeight(m_uncheckedTexture));
	}

	m_onStateChangeCallback = NULL;

	m_textFocusedColor = ARGB(255, 255, 255, 255);
	m_textUnfocusedColor = ARGB(255, 65, 131, 166);
}

OptionsCheckbox::~OptionsCheckbox()
{
	
}

void OptionsCheckbox::OnCheckStateChanged(OptionsCheckboxStateChangeCallback stateChangeCallback)
{
	m_onStateChangeCallback = stateChangeCallback;
}

void OptionsCheckbox::Render()
{
	if (m_focused)
	{
		m_font->SetColor(m_textFocusedColor);
	}
	else
	{
		m_font->SetColor(m_textUnfocusedColor);
	}

	m_font->Render((float)m_posX + 70, (float)m_posY + 6, HGETEXT_LEFT, m_text.c_str());

	m_stateIco->Render((float)m_posX, (float)m_posY);
}

void OptionsCheckbox::SetFocus(bool playEffect)
{
	m_focused = true;
	SoundManager* soundManager = SoundManager::GetInstance();
	soundManager->PlayEffect(SOUND_EFFECT_FIGURE_MOVE);
}

void OptionsCheckbox::UnsetFocus(bool playEffect)
{
	m_focused = false;
}

bool OptionsCheckbox::IsFocused()
{
	return m_focused;
}

void OptionsCheckbox::SetChecked(bool playEffect)
{
	m_isChecked = true;
	m_stateIco->SetTexture(m_checkedTexture);
	if (m_onStateChangeCallback != NULL)
	{
		m_onStateChangeCallback(true);
	}
	SoundManager* soundManager = SoundManager::GetInstance();
	soundManager->PlayEffect(SOUND_EFFECT_FIGURE_MOVE);
}

void OptionsCheckbox::SetUnchecked(bool playEffect)
{
	m_isChecked = false;
	m_stateIco->SetTexture(m_uncheckedTexture);
	if (m_onStateChangeCallback != NULL)
	{
		m_onStateChangeCallback(false);
	}
	SoundManager* soundManager = SoundManager::GetInstance();
	soundManager->PlayEffect(SOUND_EFFECT_FIGURE_MOVE);
}

bool OptionsCheckbox::IsChecked()
{
	return m_isChecked;
}

void OptionsCheckbox::Update(float dt)
{

}

bool OptionsCheckbox::KeyClick(int key, int chr)
{
	return true;
}
