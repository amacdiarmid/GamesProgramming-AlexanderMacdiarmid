/*
=================
cSprite.h
- Header file for class definition - SPECIFICATION
- Header file for the Sprite class
=================
*/
#pragma once

#include "GameConstants.h"

class cSprite
{
private:
	// position, rotation, scalling
	glm::ivec2 spritePos2D;
	glm::ivec2 spriteTranslation;
	glm::ivec2 spriteCentre;
	glm::ivec2 spriteScaling;
	float spriteScalingRotation;
	float spriteRotation;
	glm::mat4x4 spriteTransformMatrix;
	RECT boundingRect;

	//texturing
	glm::ivec2 spriteVertexData[4];
	glm::ivec2 spriteTexCoordData[4];

	// Texture width & Height
	int textureWidth;
	int textureHeight;
	GLuint GLTextureID;

	//cD3DXTexture spriteTexture;
public:
	cSprite();			// Default constructor
	//cSprite(glm::vec3 sPosition, LPDIRECT3DDEVICE9 pd3dDevice, LPCSTR theFilename); // Constructor
	~cSprite();			// Destructor
	void render();
	void setSpriteTexCoordData();
	glm::ivec2 getSpritePos();  // Return the sprites current position
	void setSpritePos(glm::ivec2 sPosition); // set the position of the sprite
	//LPDIRECT3DTEXTURE9 getTexture();  // Return the sprites current image
	void setTexture(GLuint GLtexID);  // set the image of the sprite
	void setTextureDimensions(int texWidth, int textHeight);

};