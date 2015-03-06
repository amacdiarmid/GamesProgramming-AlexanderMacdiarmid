/*
=================
cSprite.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cSprite.h"
/*
=================
- Data constructor initializes the cSprite to the data passed to
- the constructor from the paramater sPosition.
- Is always called, thus ensures all sprite objects are in a consistent state.
=================
*/
cSprite::cSprite() 			// Default constructor
{

	cSprite::spritePos2D.x = 0.0f;
	cSprite::spritePos2D.y = 0.0f;
	cSprite::setSpriteTexCoordData();
	cSprite::spriteTranslation = glm::vec2(0.0f, 0.0f);
	cSprite::spriteScaling = glm::vec2(1.0f, 1.0f);
	cSprite::spriteRotation = 0.0f;
}
/*
cSprite::cSprite(D3DXVECTOR3 sPosition, LPDIRECT3DDEVICE9 pd3dDevice, LPCSTR theFilename) // Constructor
{
cSprite::setSpritePos(sPosition);
cSprite::setTexture(pd3dDevice, theFilename);
}
*/
/*
=================
- Destructor
=================
*/
cSprite::~cSprite()			// Destructor
{
}
/*
=================
- Return the sprites current position.
=================
*/

glm::vec2 cSprite::getSpritePos()  // Return the sprites current position
{
	return cSprite::spritePos2D;
}

/*
=================
- set the position of the sprite.
=================
*/

void cSprite::setSpritePos(glm::vec2 sPosition)  // set the position of the sprite
{
	cSprite::spritePos2D = sPosition;
}

/*
=================
- Return the sprites current image.
=================
*/

GLuint cSprite::getTexture()  // Return the sprites current image
{
	return GLTextureID;
}

/*
=================
- set the image of the sprite.
=================
*/

void cSprite::setTexture(GLuint GLtexID)  // set the image of the sprite
{
	GLTextureID = GLtexID;
}

/*
=================================================================================
set the amount of movement on the x & y axis
=================================================================================
*/
void cSprite::setSpriteTranslation(glm::vec2 translation)
{
	spriteTranslation = translation;
}

/*
=================================================================================
get the amount of movement on the x & y axis
=================================================================================
*/
glm::vec2 cSprite::getSpriteTranslation()
{
	return spriteTranslation;
}

void cSprite::render()
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
	glVertex2f(spritePos2D.x, spritePos2D.y);
	glTexCoord2f(spriteTexCoordData[1].x, spriteTexCoordData[1].y);
	glVertex2f(spritePos2D.x + textureWidth, spritePos2D.y);
	glTexCoord2f(spriteTexCoordData[2].x, spriteTexCoordData[2].y);
	glVertex2f(spritePos2D.x + textureWidth, spritePos2D.y + textureHeight);
	glTexCoord2f(spriteTexCoordData[3].x, spriteTexCoordData[3].y);
	glVertex2f(spritePos2D.x, spritePos2D.y + textureHeight);

	glEnd();
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}
void cSprite::setSpriteTexCoordData()
{
	spriteTexCoordData[0] = glm::vec2(0.0f, 0.0f);
	spriteTexCoordData[1] = glm::vec2(1.0f, 0.0f);
	spriteTexCoordData[2] = glm::vec2(1.0f, 1.0f);
	spriteTexCoordData[3] = glm::vec2(0.0f, 1.0f);
}

void cSprite::setTextureDimensions(int texWidth, int textHeight)
{
	textureWidth = texWidth;
	textureHeight = textHeight;
}

/*
=================================================================
Attach the input manager to the sprite
=================================================================
*/
void cSprite::attachInputMgr(cInputMgr* inputMgr)
{
	m_InputMgr = inputMgr;
}

/*
=================================================================
Attach the player object to the sprite
=================================================================
*/
void cSprite::attatchPlayerObject(player tPlayer)
{
	playerInfo = tPlayer;
}

/*
=================================================================
Update the sprite position
=================================================================
*/

void cSprite::update()
{
	if (m_InputMgr->isKeyDown(VK_RIGHT))
	{
		spritePos2D += spriteTranslation;
	}
	if (m_InputMgr->isKeyDown(VK_LEFT))
	{
		spritePos2D -= spriteTranslation;
	}
	if (m_InputMgr->isKeyDown(VK_UP))
	{
		spriteRotation += 5.0f;
	}
	if (m_InputMgr->isKeyDown(VK_DOWN))
	{
		spriteRotation -= 5.0f;
	}
	if (m_InputMgr->isKeyDown(int('A')))
	{
		spriteScaling += spriteScaling;
	}
	if (m_InputMgr->isKeyDown(int('S')))
	{
		spriteScaling -= spriteScaling;
	}
}