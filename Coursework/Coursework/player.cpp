#include "player.h"
using namespace std;

//constructor
player::player()
{
	cSprite::spritePos2D.x = 0.0f;
	cSprite::spritePos2D.y = 0.0f;
	cSprite::setSpriteTexCoordData();
	cSprite::spriteTranslation = glm::vec2(0.0f, 0.0f);
	cSprite::spriteScaling = glm::vec2(1.0f, 1.0f);
	cSprite::spriteRotation = 0.0f;
	playerName = "default";			
	throws = 0;					
	health = 3;				
	angle = 0;				
	power = 0;
	playerSpeed = glm::vec2(1.0f, 0.0f);
	playerRotation = 1.0f;
}
player::player(string name)
{
	cSprite::spritePos2D.x = 0.0f;
	cSprite::spritePos2D.y = 0.0f;
	cSprite::setSpriteTexCoordData();
	cSprite::spriteTranslation = glm::vec2(0.0f, 0.0f);
	cSprite::spriteScaling = glm::vec2(1.0f, 1.0f);
	cSprite::spriteRotation = 0.0f;
	playerName = name;
	throws = 0;
	health = 3;
	angle = 0;
	power = 0;
	playerSpeed = glm::vec2(5.0f, 0.0f);
	playerRotation = 1.0f;
}

//destructor
player::~player()
{
	cout << "destructor for the " << playerName << " object"<<endl;
}

//accessor methods 
string player::getName()
{
	return playerName;
}

//message methods
void player::messagePlayerWin(string name)
{
	cout << playerName << " killed " << name << endl;
}
void player::messagePlayerHit(string name)
{
	cout << playerName << " hit " << name << endl;
}

//attach
void player::attachInputMgr(cInputMgr* inputMgr)
{
	m_InputMgr = inputMgr;
}
void player::attachArrowSprite()
{
	//arrow
	cTexture playerArrow;
	playerArrow.createTexture("arrow texture.png");
	arrow arrowP1;
	arrowP1.setSpritePos(glm::vec2(getSpritePos().x, getSpritePos().y));
	arrowP1.setTexture(playerArrow.getTexture());
	arrowP1.setTextureDimensions(playerArrow.getTWidth(), playerArrow.getTHeight());
	arrowP1.setSpriteCentre();
	arrowSprite = arrowP1;
}

//update
void player::update()
{
	//move left and right 
	if (m_InputMgr->isKeyDown('D'))
	{
		moveRight();
	}
	if (m_InputMgr->isKeyDown('A'))
	{
		moveLeft();
	}
	//adjust angle
	if (m_InputMgr->isKeyDown('W'))
	{
		angleUp();
	}
	if (m_InputMgr->isKeyDown('S'))
	{
		angleDown();
	}
	//adjust power
	if (m_InputMgr->isKeyDown('Q'))
	{
		powerUp();
	}
	if (m_InputMgr->isKeyDown('E'))
	{
		powerDown();
	}
	//throw rock
	if (m_InputMgr->isKeyDown(VK_SPACE))
	{
		throwRock();
	}
}

void player::render()
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

	arrowSprite.render();
}

//action methods
void player::angleUp()
{
	arrowSprite.setSpriteRotaion(-1.0f, getSpriteCentre());
}
void player::angleDown()
{
	arrowSprite.setSpriteRotaion(1.0f, getSpriteCentre());
}
void player::powerUp()
{
	arrowSprite.setSpriteLength(2.0f);
}
void player::powerDown()
{
	arrowSprite.setSpriteLength(-2.0f);
}
void player::moveLeft()
{
	setSpritePos(getSpritePos() - playerSpeed);
	arrowSprite.setSpritePos(arrowSprite.getSpritePos() - playerSpeed);
}
void player::moveRight()
{
	setSpritePos(getSpritePos() + playerSpeed);
	arrowSprite.setSpritePos(arrowSprite.getSpritePos() + playerSpeed);
}
void player::throwRock()
{

}