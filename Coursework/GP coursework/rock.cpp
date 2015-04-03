#include "rock.h"
#include <iostream>
#include <cmath>

#define PI 3.14159265

//constructor
rock::rock()
{
	
}
void rock::throwIt(float Tangle, float Tpower, glm::vec2 TPlayerPos)
{
	angle = Tangle;
	power = Tpower;
	playerPos = TPlayerPos;
	calculateArc();
	updateBoundingRect();

	/*cout << endl;
	int width = getTextureSize().x;
	int height = getTextureSize().y;
	cout << width << " " << height << endl;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			cout << getTextPoint()->checkPixel(x, y) ? 1 : 0;
		}
		cout << endl;
	}*/
}

//destructor
rock::~rock()
{
	//remove gameobject
}

void rock::update(float deltaTime)
{
	setSpritePos(getSpritePos() + (displacement*deltaTime));
	setSpriteRotation(spriteRotation);
	displacement.y += 100 * deltaTime;
	spriteRotation += 0.0f;

	updateBoundingRect();
}

//method
void rock::calculateArc()
{
	displacement.y = -power;
	displacement.x = angle * -10;
}

bool rock::pixelCheck(cSprite *rock, cSprite *object)
{
	glm::mat4x4 rMat = rock->getWorldMatrix();
	glm::mat4x4 oMat = object->getWorldMatrix();

	glm::ivec2 rSizeHalf(rock->getTextureSize().x / 2, rock->getTextureSize().y / 2);
	glm::ivec2 oSizeHalf(object->getTextureSize().x / 2, object->getTextureSize().y / 2);
	for (int x = 0; x < rock->getTextureSize().x; x++)
	{
		for (int y = 0; y < rock->getTextureSize().y; y++)
		{
			bool solidA = rock->getTextPoint()->checkPixel(x, y);
			if (solidA)
			{
				glm::vec4 pos = rMat * glm::vec4(x, y, 0, 1) - glm::vec4(rSizeHalf.x, rSizeHalf.y, 0, 0);
				glm::vec4 positionB = glm::inverse(oMat) * pos + glm::vec4(oSizeHalf.x, oSizeHalf.y, 0, 0);

				if (positionB.x < 0 || positionB.y < 0 || positionB.x >= object->getTextureSize().x || positionB.y >= object->getTextureSize().y) continue;

				bool solidB = object->getTextPoint()->checkPixel(positionB.x, positionB.y);

				if (solidA && solidB) 
					return true;
			}
		}
	}
	return false;
}
