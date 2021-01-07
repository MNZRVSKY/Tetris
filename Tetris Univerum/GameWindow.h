#pragma once
#include "Hge.h"
#include "TypeDefs.h"
#include "Enums.h"

class GameWindow : public hgeGUIObject
{
public:

	virtual ~GameWindow(){};

	virtual void OnEscape(WndEscapeCallback callback) = 0;
	virtual WindowType GetType() = 0;

	virtual void Render() = 0;
	virtual void Update(float dt) = 0;
};