#pragma once
#include "cSprite.h"
#include <functional>

class Button : public cSprite
{
private:
	bool pressed;
	char controllerButton;

public:
	Button(char tButton);
	~Button();

	void update(float deltaTime)override;
	bool getPressed();
};

