#include "player.h"
using namespace std;

//constructor
player::player()
{
	cout << "should not be called";
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
	dead = false;
	updateBoundingRect();
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
rock* player::getRock()
{
	return &thrownRock;
}
string player::getInfo()
{
	stringstream output;
	output << "throws: " << throws << " health: " << health << " angle: " << angle+90 << " power: " << power;
	return output.str();
}

bool player::getDead()
{
	return dead;
}

//message methods
void player::messagePlayerWin(string name)
{
	output = name + " Killed " + playerName;
	showOutput = true;
	dead = true;
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
		output = name + " Hit " + playerName;
		showOutput = true;
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
	cTexture *playerArrow = new cTexture();
	playerArrow->createTexture("Images\\arrow texture.png");
	arrowSprite.setSpritePos(glm::vec2(getSpritePos().x, getSpritePos().y));
	arrowSprite.setTexture(playerArrow->getTexture(), playerArrow);
	arrowSprite.setTextureDimensions(playerArrow->getTWidth(), playerArrow->getTHeight());
	arrowSprite.setSpriteCentre();
}
void player::attatchFontmgr(cFontMgr* fontMgr)
{
	theFontMgr = fontMgr;
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

	updateBoundingRect();

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
	if (showOutput == true)
	{
		theFontMgr->getFont("micross")->printText(output.c_str(), FTPoint(400.0f, -45.0f, 0.0f));
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
	if (getSpritePos().x > minX)
	{
		setSpritePos(getSpritePos() - playerSpeed);
		arrowSprite.setSpritePos(arrowSprite.getSpritePos() - playerSpeed);
	}
	
}
void player::moveRight()
{
	if (getSpritePos().x < maxX)
	{
		setSpritePos(getSpritePos() + playerSpeed);
		arrowSprite.setSpritePos(arrowSprite.getSpritePos() + playerSpeed);
	}
}
void player::throwRock()
{
	throws++;
	rockThrown = true;
	showOutput = false;
	cTexture *playerRock = new cTexture();
	playerRock->createTexture("Images\\rock texture.png");
	thrownRock.setSpritePos(glm::vec2(getSpritePos().x, getSpritePos().y - (textureHeight / 2)));
	thrownRock.setTexture(playerRock->getTexture(), playerRock);
	thrownRock.setTextureDimensions(playerRock->getTWidth(), playerRock->getTHeight());
	thrownRock.setSpriteCentre();
	thrownRock.setMdlRadius();
	thrownRock.throwIt(angle, power, spritePos2D);
	active = false;
}

void player::reset()
{
	throws = 0;
	health = 3;
	angle = 0;
	power = 250;
	playerSpeed = glm::vec2(5.0f, 0.0f);
	playerRotation = 1.0f;
	rockThrown = false;
	dead = false;
	updateBoundingRect();
}

void player::setLimits(int min, int max)
{
	minX = min;
	maxX = max;
}