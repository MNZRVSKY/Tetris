#include "CrashLineAnimation.h"
#include "ResourcesManager.h"


CrashLineAnimation::CrashLineAnimation(Point coord)
{
	m_startCoord = Point(coord.GetAsix_Y() - 20, coord.GetAsix_X() - 40);
	m_currentCoord = Point(coord.GetAsix_Y() - 20, coord.GetAsix_X()  - 40);
	m_isAnimateFinished = false;

	ResourcesManager* rm = ResourcesManager::GetInstance();
	m_tex  = rm->GetTexture(TEXTURE_PARTICLES);	

	m_SpriteForOneAnimation = new hgeSprite(m_tex, 32, 64, 32, 32);
	m_SpriteForOneAnimation->SetBlendMode(BLEND_COLORMUL | BLEND_ALPHAADD | BLEND_NOZWRITE);
	m_SpriteForOneAnimation->SetHotSpot(16,16);
	m_oneAnimation = new hgeParticleSystem("resources/textures/particles/particle7.psi",m_SpriteForOneAnimation);

	m_SpriteForTwoAnimation = new hgeSprite(m_tex, 64, 96, 32, 32);
	m_SpriteForTwoAnimation->SetBlendMode(BLEND_COLORMUL | BLEND_ALPHAADD | BLEND_NOZWRITE);
	m_SpriteForTwoAnimation->SetHotSpot(16,16);
	m_twoAnimation = new hgeParticleSystem("resources/textures/particles/particle4.psi",m_SpriteForTwoAnimation);

	m_oneAnimation->FireAt((float)m_startCoord.GetAsix_X(), (float)m_startCoord.GetAsix_Y());
	m_twoAnimation->FireAt((float)m_startCoord.GetAsix_X(), (float)m_startCoord.GetAsix_Y());	
}

void CrashLineAnimation::Render()
{
	m_oneAnimation->Render();
	m_twoAnimation->Render();	
}

void CrashLineAnimation::Update(float dt)
{
	m_oneAnimation->MoveTo((float)m_currentCoord.GetAsix_X(), (float)m_currentCoord.GetAsix_Y());
	m_twoAnimation->MoveTo((float)m_currentCoord.GetAsix_X(), (float)m_currentCoord.GetAsix_Y());

	m_oneAnimation->Update(dt);
	m_twoAnimation->Update(dt);

	m_currentCoord.SetAsix_X(m_currentCoord.GetAsix_X() + 20);

	if(m_currentCoord.GetAsix_X() >= m_startCoord.GetAsix_X() + 32 * 10 - 16)
	{
		m_twoAnimation->Stop(false);
		m_oneAnimation->Stop(false);
		m_isAnimateFinished = true;
	}
}

bool CrashLineAnimation::IsAnimationFinished()
{
	return m_isAnimateFinished;
}

CrashLineAnimation::~CrashLineAnimation()
{
	delete m_oneAnimation;
	delete m_twoAnimation;
	
	delete m_SpriteForOneAnimation;
	delete m_SpriteForTwoAnimation;
}
