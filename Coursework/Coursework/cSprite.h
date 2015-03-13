/*
=================
cSprite.h
- Header file for class definition - SPECIFICATION
- Header file for the Sprite class
=================
*/
#ifndef _CSPRITE_H
#define _CSPRITE_H
#include "cInputMgr.h"
#include "GameConstants.h"

class cSprite
{
private:
	static cSprite* pInstance;
	// position, rotation, scalling
	glm::vec2 spritePos2D;
	glm::vec2 spriteTranslation;
	glm::vec2 spriteCentre;
	glm::vec2 spriteScaling;
	float spriteRotation;
	float spriteScalingRotation;	
	glm::mat4x4 spriteTransformMatrix;
	RECT boundingRect;

	//texturing
	glm::vec2 spriteVertexData[4];
	glm::vec2 spriteTexCoordData[4];

	// Texture width & Height
	int textureWidth;
	int textureHeight;
	GLuint GLTextureID;

public:
	static cSprite* getInstance(); //constructor from pointer
	cSprite();			// Default constructor
	//cSprite(glm::vec3 sPosition, LPDIRECT3DDEVICE9 pd3dDevice, LPCSTR theFilename); // Constructor
	~cSprite();			// Destructor
	void render();
	void setSpriteTexCoordData();
	glm::vec2 getSpritePos();  // Return the sprites current position
	void setSpritePos(glm::vec2 sPosition); // set the position of the sprite
	GLuint getTexture();  // Return the sprites current image
	void setTexture(GLuint GLtexID);  // set the image of the sprite
	void setTextureDimensions(int texWidth, int textHeight);
	void setSpriteTranslation(glm::vec2 translation); // Set the amount of movement on the x & y axis
	glm::vec2 getSpriteTranslation();  // return the amount of movement on the x & y axis
	void setSpriteCentre(); // Set the sprites centre point
	glm::vec2 getSpriteCentre();  // return the sprites centre point
	void setSpriteRotaion(float rotation); //rotate the sprite 

};
#endif