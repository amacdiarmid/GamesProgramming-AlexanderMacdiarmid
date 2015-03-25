#pragma once
#ifndef _ROCK_H
#define _ROCK_H
#include <string>
#include "cSprite.h"
using namespace std;

class rock : public cSprite
{
private:
	glm::vec2 finalSpeed;	//speed of the rock
	float angle;			//the angle the rock was launched at
	float power;			//the power the rock was launched at
	float maxHeight;		//the max height the rock will reach
	float range;			//the distance the rock will travel
	float time;				//the travel time for the rock
	void calculateArc();	//calculate the arc of the rock
	glm::vec2 displacement;
	glm::vec2 playerPos;

public:
	//constructor
	rock();					//default constructor
	rock(float, float, glm::vec2);		//constructor with the values for the arc

	//destructor
	~rock();

	void update(float deltaTime);

};
#endif