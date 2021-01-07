#pragma once
#include "Hge.h"
#include "Field.h"
#include <vector>
#include "GameWindow.h"
#include "SoundManager.h"
#include "SettingsManager.h"


class GlassWindow : public GameWindow
{

private:
	SoundManager* soundManager;
	SettingsManager* settingsManager;

	WndEscapeCallback m_onEscapeCallback;

	hgeSprite* m_Background;
	hgeFont* m_Font;
	hgeSprite* m_Elements[8];
	hgeSprite* m_Mini_Elements[8];
	hgeSprite* m_Element;

	HEFFECT m_Move;
	HEFFECT m_Rotate;
	HEFFECT m_SaveFigure;
	HEFFECT m_CrashLine;
	HEFFECT m_BackgroundMusic;
	HCHANNEL m_Music;

	bool  m_EndGame, m_EndCicle, m_Pause;

	float m_moveDelay;
	float m_currentDelay;


	Field m_Field;
	Shape m_Curent;
	Shape m_Hold;
	Shape m_Shapes[5];

	int m_SizeOfShapes;

	float m_AsixX_nextFigures;
	float m_AsixY_nextFigures;

	float m_AsixX_holdFigures;
	float m_AsixY_holdFigures;

	bool m_UntouchedHold;

	void Init();

	//======================================

	void StartPause(bool & pause);
	void StopPause(bool & pause);

	void MoveToLeft(Field & field, Shape & current);
	void MoveToRight(Field & field, Shape & current);
	void MoveToDown(Field & field, Shape & current, bool & EndGame, bool & EndCicle);
	void ToRotate(Field & field, Shape & current);
	void FreeFall(Field & field, Shape & current, float DeltaTime, int level, bool & EndGame, bool & EndCicle);
	void ToHold();

	float IndentForLittleFigure(int size);
	void RenderCurrentFigure(Shape & obj, hgeSprite* element[]);
	void RenderLittleFigures(Shape & obj, float X, float Y, hgeSprite* mini_element[]);
	void RenderField(Field & obj);

	bool CanMove(float dt);

public:
	GlassWindow();
	virtual ~GlassWindow();

	void OnEscape(WndEscapeCallback callback);
	WindowType GetType();

	bool KeyClick(int key, int chr);
	virtual void Render();
	virtual void Update(float dt);
};