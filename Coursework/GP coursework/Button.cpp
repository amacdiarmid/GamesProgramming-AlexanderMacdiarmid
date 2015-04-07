#include "Button.h"


Button::Button()
{
	pressed = false;
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
			cout << pressed << " clicked" << endl;
			pressed = true;
		}
	}
}

bool Button::getPressed()
{
	cout << pressed << endl;
	return pressed;
}
