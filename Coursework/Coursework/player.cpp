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
void player::attachPlayerSprite(cSprite sprite)
{
	playerSprite = sprite;
}
void player::attatchArrowSprite(cSprite sprite)
{
	arrowSprite = sprite;
}

//update
void player::update()
{
	//move left and right 
	if (m_InputMgr->isKeyDown(VK_RIGHT))
	{
		moveRight();
	}
	if (m_InputMgr->isKeyDown(VK_LEFT))
	{
		moveLeft();
	}
	//adjust angle
	if (m_InputMgr->isKeyDown(VK_UP))
	{
		angleUp();
	}
	if (m_InputMgr->isKeyDown(VK_DOWN))
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
	//if the input is positive add to the angle
	//else take away from the angle
}
void player::angleDown()
{
	//if the input is posative then add to the power
	//else take away from the power
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
	playerSprite.setSpritePos(playerSprite.getSpritePos() -= playerSpeed);
}
void player::moveRight()
{
	playerSprite.setSpritePos(playerSprite.getSpritePos() += playerSpeed);
}
void player::throwRock()
{

}
