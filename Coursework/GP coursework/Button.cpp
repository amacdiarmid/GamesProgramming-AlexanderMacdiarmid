#include "Button.h"


Button::Button(char tButton)
{
	pressed = false;
	controllerButton = tButton;
}


Button::~Button()
{
}

void Button::update(float deltaTime)
{
	if (m_InputMgr->getLeftMouseBtn())
	{
		glm::vec2 areaClicked = glm::vec2(m_InputMgr->getMouseXPos(), m_InputMgr->getMouseYPos());
		if (areaClicked.x > spritePos2D.x - (textureWidth / 2) && areaClicked.x < spritePos2D.x + (textureWidth / 2) && areaClicked.y > spritePos2D.y - (textureHeight / 2) && areaClicked.y < spritePos2D.y + (textureHeight / 2))
		{
			pressed = true;
		}
	}
	if (controllerButton == 'A')
	{
		
		if (m_InputMgr->getController().Gamepad.wButtons & XINPUT_GAMEPAD_A)
		{
			cout << "pressed A button";
			pressed = true;
		}
	}
	else if (controllerButton == 'B')
	{
		if (m_InputMgr->getController().Gamepad.wButtons & XINPUT_GAMEPAD_B)
		{
			cout << "pressed B button";
			pressed = true;
		}
	}
}

bool Button::getPressed()
{
	return pressed;
}
