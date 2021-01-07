#pragma once
#include "Point.h"
#include "Animation.h"
#include "Hge.h"
class CrashLineAnimation: public Animation
{
private:
	hgeSprite*			m_SpriteForOneAnimation;
	hgeParticleSystem*	m_oneAnimation;

	hgeSprite*          m_SpriteForTwoAnimation;
	hgeParticleSystem*  m_twoAnimation;

	HTEXTURE			m_tex;

	Point m_startCoord;
	Point m_currentCoord;

	bool m_isAnimateFinished;

public:
	CrashLineAnimation(Point coord);

	virtual void Update(float dt);
	virtual bool IsAnimationFinished();
	virtual void Render();
	virtual ~CrashLineAnimation();
};

