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
	rockThrown = false;
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
	power = 250;
	playerSpeed = glm::vec2(5.0f, 0.0f);
	playerRotation = 1.0f;
	rockThrown = false;
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

void player::setActive(bool value)
{
	active = value;
}

bool player::getActive()
{
	return active;
}
bool player::getRockThrown()
{
	return rockThrown;
}
void player::setThrownRock(bool value)
{
	rockThrown = value;
}
rock player::getRock()
{
	return thrownRock;
}

//message methods
void player::messagePlayerWin(string name)
{
	cout << name << " killed " << playerName << endl;
}
void player::messagePlayerHit(string name)
{
	health--;
	if (health <= 0)
	{
		messagePlayerWin(name);
	}
	else
	{
		cout << name << " hit " << playerName << endl;
	}
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
	playerArrow.createTexture("Images\\arrow texture.png");
	arrow arrowP1;
	arrowP1.setSpritePos(glm::vec2(getSpritePos().x, getSpritePos().y));
	arrowP1.setTexture(playerArrow.getTexture());
	arrowP1.setTextureDimensions(playerArrow.getTWidth(), playerArrow.getTHeight());
	arrowP1.setSpriteCentre();
	arrowSprite = arrowP1;
}

//update
void player::update(float deltaTime)
{
	if (active == true)
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

	if (rockThrown == true)
	{
		thrownRock.update(deltaTime);

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
	if (rockThrown == true)
	{
		thrownRock.render();
	}
}

//action methods
void player::angleUp()
{
	if (angle < 90)
	{
		angle++;
		arrowSprite.setSpriteRotaion(-1.0f, getSpriteCentre());
	}
}
void player::angleDown()
{
	if (angle > -90)
	{
		angle--;
		arrowSprite.setSpriteRotaion(1.0f, getSpriteCentre());
	}
}
void player::powerUp()
{
	if (power < 10)
	{
		power++;
		arrowSprite.setSpriteLength(-5.0f);
	}
}
void player::powerDown()
{
	if (power > 1)
	{
		power--;
		arrowSprite.setSpriteLength(5.0f);
	}
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
	throws++;
	rockThrown = true;
	cTexture playerRock;
	playerRock.createTexture("Images\\rock texture.png");
	rock RockP1 = rock::rock(angle, power, spritePos2D);
	RockP1.setSpritePos(glm::vec2(getSpritePos().x, getSpritePos().y - (textureHeight/2)));
	RockP1.setTexture(playerRock.getTexture());
	RockP1.setTextureDimensions(playerRock.getTWidth(), playerRock.getTHeight());
	RockP1.setSpriteCentre();
	RockP1.setMdlRadius();
	thrownRock = RockP1;
	active = false;
}