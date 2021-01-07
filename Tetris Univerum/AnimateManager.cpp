#include "AnimateManager.h"
#include <algorithm>

AnimateManager::AnimateManager(void)
{

}

void AnimateManager::PlayCrachLine(Point coord)
{
	CrashLineAnimation* crashLine = new CrashLineAnimation(coord);
	m_animations.push_back(crashLine);
}
void AnimateManager::Update(float dt)
{
	m_deletedIndexes.clear();

	//оновлюємо анімації і отримуємо індекси анімацій, які закінчилися, щоб їх видалити
	std::vector<Animation*>::iterator it = m_animations.begin();
	for(; it != m_animations.end(); it++)
	{
		if ((*it))
		{
			(*it)->Update(dt);
			if((*it)->IsAnimationFinished())
			{
				int index = it - m_animations.begin();
				m_deletedIndexes.push_back(index);
			}
		}
	}

	//видаляємо анімації, які завершилися
	std::vector<int>::iterator it2 = m_deletedIndexes.begin();
	for(;it2 != m_deletedIndexes.end(); it2++)
	{
		int index = (*it2);
		delete m_animations[index];
		m_animations[index] = NULL;
	}

	m_animations.erase(
    std::remove_if(m_animations.begin(), m_animations.end(),
        [](const Animation* o) { return o == NULL; }),
    m_animations.end());
}

void AnimateManager::Render()
{
	std::vector<Animation*>::iterator it = m_animations.begin();
	for(; it != m_animations.end(); it++)
	{
		if ((*it))
		{
			(*it)->Render();
		}
	}
}

AnimateManager::~AnimateManager(void)
{

}
