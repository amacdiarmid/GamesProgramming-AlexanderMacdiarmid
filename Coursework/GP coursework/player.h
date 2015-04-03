#pragma once
#ifndef _PLAYER_H
#define _PLAYER_H
#include <string>
#include <iostream>
#include "cSprite.h"
#include "arrow.h"
#include "cInputMgr.h"
#include "rock.h"
using namespace std;

class player : public cSprite
{
private:
	string playerName;			// name of the player
	int throws;					//the number of throws so far
	int health;					//the players current health
	float angle;				//the current set angle
	float power;				//the current set power
	glm::vec2 playerSpeed;
	float playerRotation;
	cInputMgr* m_InputMgr;
	arrow arrowSprite;
	rock thrownRock;
	bool active;
	bool rockThrown;

public:
	//constructor
	player();					//create default class
	player(string);				//create class with player name

	//destructor
	~player();					//destroy player class

	//accessor methods 
	string getName();			//get the player name
	void setActive(bool);
	bool getActive();
	bool getRockThrown();
	void setThrownRock(bool);
	rock* getRock();

	//message methods
	void messagePlayerWin(string);	//display message on player win
	void messagePlayerHit(string);	//display message on player hit

	//update
	void update(float deltaTime)override;			//the player Update
	void render()override;

	//attach
	void attachInputMgr(cInputMgr* inputMgr);
	void attachArrowSprite();

	//action methods
	void angleUp();			//change the current angle up/down
	void angleDown();
	void powerUp();			//change the current power higher/lower
	void powerDown();
	void moveLeft();		//move the player left/right
	void moveRight();			
	void throwRock();		//throw rocks
};
#endif