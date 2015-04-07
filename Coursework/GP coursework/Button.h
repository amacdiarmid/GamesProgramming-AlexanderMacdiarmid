#pragma once
#include "cSprite.h"
#include <functional>

class Button : public cSprite
{
private:
	bool pressed;

public:
	Button();
	~Button();

	void update(float deltaTime)override;
	bool getPressed();
};

