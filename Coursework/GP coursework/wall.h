#pragma once
#include "cSprite.h"
class wall : public cSprite
{
public:
	wall();
	~wall();
	void update(float deltaTime)override;
};

