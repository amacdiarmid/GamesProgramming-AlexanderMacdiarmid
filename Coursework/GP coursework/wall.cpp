#include "wall.h"

//default wall constructor 
wall::wall()
{
	cSprite::spritePos2D.x = 0.0f;
	cSprite::spritePos2D.y = 0.0f;
	cSprite::setSpriteTexCoordData();
	cSprite::spriteTranslation = glm::vec2(0.0f, 0.0f);
	cSprite::spriteScaling = glm::vec2(1.0f, 1.0f);
	cSprite::spriteRotation = 0.0f;
	cSprite::spriteCentre = glm::vec2(0.0f, 0.0f);
}


wall::~wall()
{
}

void wall::update(float deltaTime)
{
	
}
