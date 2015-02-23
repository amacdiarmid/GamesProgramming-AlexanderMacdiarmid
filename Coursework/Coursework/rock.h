#pragma once
#ifndef _ROCK_H
#define _ROCK_H
#include <string>;
using namespace std;

class rock
{
private:
	float angle;			//the angle the rock was launched at
	float power;			//the power the rock was launched at
	float maxHeight;		//the max height the rock will reach
	float range;			//the distance the rock will travel
	float time;				//the travel time for the rock
	void calculateArc();	//calculate the arc of the rock

public:
	//constructor
	rock();					//default constructor
	rock(float, float);		//constructor with the values for the arc

	//destructor
	~rock();

};
#endif