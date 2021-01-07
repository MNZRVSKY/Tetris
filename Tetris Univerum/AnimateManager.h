#pragma once
#include <vector>
#include "Animation.h"
#include "Point.h"
#include "CrashLineAnimation.h"
class AnimateManager
{
private:
	std::vector<Animation*> m_animations;
	std::vector<int> m_deletedIndexes;

public:
	AnimateManager(void);

	void PlayCrachLine(Point coord);
	void Update(float dt);
	void Render();

	~AnimateManager(void);
};

