#pragma once
#ifndef _ARROW_H
#define _ARROW_H
#include <string>
#include <iostream>
#include "cSprite.h"
class arrow : public cSprite
{
protected:
	glm::vec2 playerPos;

public:
	arrow();
	arrow(glm::vec2 playerCen);
	~arrow();
	void render();
	void setSpriteRotaion(float rotation, glm::vec2 playerCen);
};
#endif