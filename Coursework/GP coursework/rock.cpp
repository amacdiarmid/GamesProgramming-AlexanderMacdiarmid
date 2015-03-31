#include "rock.h"
#include <iostream>
#include <cmath>

#define PI 3.14159265

//constructor
rock::rock()
{
	cout << "error the rock constructor shoud not be called" << endl;
}
rock::rock(float Tangle, float Tpower, glm::vec2 TPlayerPos)
{
	angle = Tangle;
	power = Tpower;
	playerPos = TPlayerPos;
	calculateArc();
	setBoundingRect(&boundingRect);
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
	spriteRotation += 5;

	setBoundingRect(&boundingRect);
}

void rock::render()
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
	glVertex2f(-(textureWidth / 2), -(textureHeight / 2));
	glTexCoord2f(spriteTexCoordData[1].x, spriteTexCoordData[1].y);
	glVertex2f((textureWidth / 2), -(textureHeight / 2));
	glTexCoord2f(spriteTexCoordData[2].x, spriteTexCoordData[2].y);
	glVertex2f((textureWidth / 2), (textureHeight / 2));
	glTexCoord2f(spriteTexCoordData[3].x, spriteTexCoordData[3].y);
	glVertex2f(-(textureWidth / 2), (textureHeight / 2));

	glEnd();
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

//method
void rock::calculateArc()
{
	displacement.y = -power;
	displacement.x = angle * -10;
}

bool rock::pixelCheck(cSprite rock, cSprite object)
{
	for (int i = 0; i < rock; i++)
	{

	}
}
