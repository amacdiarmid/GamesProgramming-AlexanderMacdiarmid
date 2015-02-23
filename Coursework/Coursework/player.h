#pragma once
#ifndef _PLAYER_H
#define _PLAYER_H
#include <string>;
using namespace std;

class player
{
private:
	string playerName;			// name of the player
	int throws;					//the number of throws so far
	int health;					//the players current health
	float angle;				//the current set angle
	float power;				//the current set power

public:
	//constructor
	player();					//create default class
	player(string);				//create class with player name

	//destructor
	~player();					//destroy player class

	//accessor methods 
	string getName();			//get the player name

	//message methods
	void messagePlayerWin(string);	//display message on player win
	void messagePlayerHit(string);	//display message on player hit

	//action methods
	void adjustAngle();			//change the current angle up/down
	void adjustPower();			//change the current power higher/lower
	void throwRock();			//throw the rock
	void movePlayer();			//move the player left/right
	
};
#endif