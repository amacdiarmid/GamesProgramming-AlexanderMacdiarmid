#pragma once
#include "cSprite.h"
class Button : public cSprite
{
private:
	bool pressed;

public:
	Button();
	~Button();

	void update(float deltaTime)override;
};

