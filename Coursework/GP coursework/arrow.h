#pragma once
#ifndef _ARROW_H
#define _ARROW_H
#include <string>
#include <iostream>
#include "cSprite.h"
#include <math.h>
class arrow : public cSprite
{
protected:
	glm::vec2 playerPos;
	float arrowLength = 0;

public:
	arrow();
	arrow(glm::vec2 playerCen);
	~arrow();
	void render()override;
	void setSpriteRotaion(float rotation, glm::vec2 playerCen);
	void setSpriteLength(float length);
	void reset();
	void setRotation(int angle);
};
#endif