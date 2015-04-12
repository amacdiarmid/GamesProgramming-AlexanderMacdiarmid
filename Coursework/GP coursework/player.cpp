#include "player.h"
using namespace std;

#define XINPUT_GAMEPAD_TRIGGER_THRESHOLD    250
#define XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE  7849
#define PI 3.14159265

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
	output << "throws: " << throws << " health: " << health << " angle: " << angle +90 << " power: " << power;
	return output.str();
}

bool player::getDead()
{
	return dead;
}

//message methods
void player::messagePlayerWin(string name)
{
	m_InputMgr->Vibrate(1,1);
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
		m_InputMgr->Vibrate(1,1);
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
		if (m_InputMgr->isKeyDown('D') || m_InputMgr->getController().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
		{
			moveRight();
		}
		if (m_InputMgr->isKeyDown('A') || m_InputMgr->getController().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
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
		if (m_InputMgr->isKeyDown('Q') || m_InputMgr->getController().Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
		{
			powerUp();
		}
		if (m_InputMgr->isKeyDown('E') || m_InputMgr->getController().Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
		{
			powerDown();
		}
		//throw rock
		if (m_InputMgr->isKeyDown(VK_SPACE) || m_InputMgr->getController().Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		{
			throwRock();
		}
		//set the angle
		if (m_InputMgr->detectController() == true)
		{
			setRotation();
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
	angle++;
	arrowSprite.setSpriteRotaion(-1.0f, getSpriteCentre());
	if (angle == 361)
	{
		angle -= 360;
	}
}
void player::angleDown()
{
	angle--;
	arrowSprite.setSpriteRotaion(1.0f, getSpriteCentre());
	if (angle == -361)
	{
		angle += 360;
	}
}
void player::powerUp()
{
	if (power < 500)
	{
		power++;
		arrowSprite.setSpriteLength(-1.0f);
	}
}
void player::powerDown()
{
	if (power > 100)
	{
		power--;
		arrowSprite.setSpriteLength(1.0f);
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

void player::setRotation()
{
	XINPUT_STATE state = m_InputMgr->getController();

	float LX = state.Gamepad.sThumbLX;
	float LY = state.Gamepad.sThumbLY;

	float magnitude = sqrt(LX*LX + LY*LY);

	float normalisedLX = LX / magnitude;
	float normalisedLY = LY / magnitude;

	float normalisedMagnitude = 0;

	if (magnitude > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		int tAngle;
		tAngle = atan(normalisedLY / normalisedLX) * 180 / PI;
		
		if (normalisedLX > 0 && normalisedLY > 0)
		{
			//0-90
			angle = tAngle -90;
		}
		else if (normalisedLX > 0 && normalisedLY < 0)
		{
			//270-360
			angle = tAngle + 270;
		}
		else if (normalisedLX < 0 && normalisedLY < 0)
		{
			//180-270
			angle = tAngle + 90;
		}
		else if (normalisedLX < 0 && normalisedLY > 0)
		{
			//90-180
			angle = tAngle + 90;
		}

		cout << angle << endl;
		angle - 90;
		arrowSprite.setRotation(angle);
	}
	else
	{
		magnitude = 0;
		normalisedMagnitude = 0;
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
	m_InputMgr->Vibrate(65535/100, 65535/100);
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
	arrowSprite.reset();
	showOutput = false;
}

void player::setLimits(int min, int max)
{
	minX = min;
	maxX = max;
}