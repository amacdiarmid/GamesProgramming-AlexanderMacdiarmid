#include "player.h"
using namespace std;

//constructor
player::player()
{
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
void player::attachArrowSprite(cSprite* sprite)
{
	arrowSprite = sprite;
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

//action methods
void player::angleUp()
{
	arrowSprite->setSpriteRotaion(5.0f);
}
void player::angleDown()
{
	arrowSprite->setSpriteRotaion(-5.0f);
}
void player::powerUp()
{
	//create new rock object 
	//call the calculate arc method on rock
}
void player::powerDown()
{
	//if input is posotive then move player right
	//else move player left
}
void player::moveLeft()
{
	setSpritePos(getSpritePos() - playerSpeed);
	arrowSprite->setSpritePos(arrowSprite->getSpritePos() - playerSpeed);
}
void player::moveRight()
{
	setSpritePos(getSpritePos() + playerSpeed);
	arrowSprite->setSpritePos(arrowSprite->getSpritePos() + playerSpeed);
}
void player::throwRock()
{

}