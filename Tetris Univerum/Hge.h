#pragma once

#include "include/hde/hge.h"
#include "include/hde/hgegui.h"
#include "include/hde/hgeparticle.h"

class Hge
{
private:
	static HGE* m_instance;
	Hge();
    


public:
	
	static HGE* GetInstance();
};
