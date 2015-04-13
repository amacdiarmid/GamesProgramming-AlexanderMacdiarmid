#include "Button.h"

//custom constructor. the char sets what button on the controller will have to be pressed to use the button
Button::Button(char tButton)
{
	pressed = false;
	controllerButton = tButton;
}

//default destructor
Button::~Button()
{
}

//custom updated with deltatime
void Button::update(float deltaTime)
{
	//if ther is a click detected
	if (m_InputMgr->getLeftMouseBtn())
	{
		//get the click position
		glm::vec2 areaClicked = glm::vec2(m_InputMgr->getMouseXPos(), m_InputMgr->getMouseYPos());
		//if the click is within the bounds of the button texture
		if (areaClicked.x > spritePos2D.x - (textureWidth / 2) && areaClicked.x < spritePos2D.x + (textureWidth / 2) && areaClicked.y > spritePos2D.y - (textureHeight / 2) && areaClicked.y < spritePos2D.y + (textureHeight / 2))
		{
			//set the pressed to true
			pressed = true;
		}
	}
	//if the char is A
	if (controllerButton == 'A')
	{
		//if the buttons pressed is A
		if (m_InputMgr->getController().Gamepad.wButtons & XINPUT_GAMEPAD_A)
		{
			//set the pressed to true
			pressed = true;
		}
	}
	else if (controllerButton == 'B')
	{
		if (m_InputMgr->getController().Gamepad.wButtons & XINPUT_GAMEPAD_B)
		{
			//set the pressed to true
			pressed = true;
		}
	}
}

//set/get the state of the button
bool Button::getPressed()
{
	return pressed;
}

void  Button::setPressed(bool value)
{
	pressed = value;
}
