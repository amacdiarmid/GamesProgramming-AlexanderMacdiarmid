#include "arrow.h"

arrow::arrow()
{
}

arrow::~arrow()
{
}

void arrow::render()
{
	glPushMatrix();

	glTranslatef(spriteTranslation.x, spriteTranslation.y, 0.0f);
	glRotatef(spriteRotation, 0.0f, 0.0f, 1.0f);
	glScalef(spriteScaling.x, spriteScaling.y, 1.0f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, GLTextureID); // Binding of GLtexture name 

	glBegin(GL_QUADS);
	glColor3f(255.0f, 255.0f, 255.0f);
	glTexCoord2f(spriteTexCoordData[0].x, spriteTexCoordData[0].y);
	glVertex2f(playerPos.x - (textureWidth/2), playerPos.y+100.0f);
	glTexCoord2f(spriteTexCoordData[1].x, spriteTexCoordData[1].y);
	glVertex2f(playerPos.x + (textureWidth / 2), playerPos.y + 100.0f);
	glTexCoord2f(spriteTexCoordData[2].x, spriteTexCoordData[2].y);
	glVertex2f(playerPos.x - (textureWidth / 2), (playerPos.y + 100.0f) + textureHeight);
	glTexCoord2f(spriteTexCoordData[3].x, spriteTexCoordData[3].y);
	glVertex2f(playerPos.x + (textureWidth / 2), (playerPos.y + 100.0f) + textureHeight);

	glEnd();
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

void arrow::setSpriteRotaion(float rotation, glm::vec2 playerCen)
{
	spriteRotation += rotation;
	playerPos = playerCen;
}