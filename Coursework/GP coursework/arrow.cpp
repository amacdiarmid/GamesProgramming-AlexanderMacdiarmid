#include "arrow.h"

//default constructor never called
arrow::arrow()
{
	cSprite::spritePos2D.x = 0.0f;
	cSprite::spritePos2D.y = 0.0f;
	cSprite::setSpriteTexCoordData();
	cSprite::spriteTranslation = glm::vec2(0.0f, 0.0f);
	cSprite::spriteScaling = glm::vec2(1.0f, 1.0f);
	cSprite::spriteRotation = 0.0f;
}

//custom constructor to set the position to the player
arrow::arrow(glm::vec2 playerCen)
{
	cSprite::spritePos2D.x = 0.0f;
	cSprite::spritePos2D.y = 0.0f;
	cSprite::setSpriteTexCoordData();
	cSprite::spriteTranslation = glm::vec2(0.0f, 0.0f);
	cSprite::spriteScaling = glm::vec2(1.0f, 1.0f);
	cSprite::spriteRotation = 0.0f;
	playerPos = playerCen;
	arrowLength = 0;
}

//default deconstructor
arrow::~arrow()
{
}

//custom renderer to set center at the players center
void arrow::render()
{
	glPushMatrix();

	glTranslatef(spritePos2D.x, spritePos2D.y, 0.0f);
	glRotatef(spriteRotation, 0.0f, 0.0f, 1.0f);
	glScalef(spriteScaling.x, spriteScaling.y, 1.0f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, GLTextureID); // Binding of GLtexture name 

	glBegin(GL_QUADS);
	glColor3f(255.0f, 255.0f, 255.0f);
	glTexCoord2f(spriteTexCoordData[0].x, spriteTexCoordData[0].y);
	glVertex2f(-(textureWidth / 2), -(textureHeight / 2)- 200 + arrowLength);
	glTexCoord2f(spriteTexCoordData[1].x, spriteTexCoordData[1].y );
	glVertex2f((textureWidth / 2), -(textureHeight / 2)- 200 + arrowLength);
	glTexCoord2f(spriteTexCoordData[2].x, spriteTexCoordData[2].y);
	glVertex2f((textureWidth / 2), (textureHeight / 2)- 200);
	glTexCoord2f(spriteTexCoordData[3].x, spriteTexCoordData[3].y);
	glVertex2f(-(textureWidth / 2), (textureHeight / 2)- 200);

	glEnd();
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

//set the rotation and position values to the player position and player angle
void arrow::setSpriteRotaion(float rotation, glm::vec2 playerCen)
{
	spriteRotation += rotation;
	playerPos = playerCen;
}

//change the length of the sprite 
void arrow::setSpriteLength(float length)
{
	arrowLength += length;
}

//reset the arrow to default
void arrow::reset()
{
	arrowLength = 0;
	spriteRotation = 0;
}

//set the arrows angle to the paramiter and invere it 
//called if using a controller
void arrow::setRotation(int angle)
{
	spriteRotation = -angle;
}

