#pragma once
#include "Point.h"
 class Animation
{
public:
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	virtual bool IsAnimationFinished() = 0;
	virtual ~Animation() {};
};

