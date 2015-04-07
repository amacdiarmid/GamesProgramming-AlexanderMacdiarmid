#include "Button.h"


Button::Button()
{
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
			pressed == true;
		}
	}
}
