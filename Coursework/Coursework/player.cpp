#include "player.h"
#include "rock.h"
#include <iostream>
using namespace std;

//constructor
player::player()
{
	playerName = "default";			
	throws = 0;					
	health = 3;				
	angle = 0;				
	power = 0;
}
player::player(string name)
{
	playerName = name;
	throws = 0;
	health = 3;
	angle = 0;
	power = 0;
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

//action methods
void player::adjustAngle()
{
	//if the input is positive add to the angle
	//else take away from the angle
}
void player::adjustPower()
{
	//if the input is posative then add to the power
	//else take away from the power
}
void player::throwRock()
{
	//create new rock object 
	//call the calculate arc method on rock
}
void player::movePlayer()
{
	//if input is posotive then move player right
	//else move player left
}
