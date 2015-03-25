#include "rock.h"
#include <iostream>
#include <cmath>

//constructor
rock::rock()
{
	cout << "error the rock constructor shoud not be called" << endl;
}
rock::rock(float Tangle, float Tpower, glm::vec2 TPlayerPos)
{
	angle = Tangle;
	power = Tpower;
	playerPos = TPlayerPos;
	calculateArc();
}

//destructor
rock::~rock()
{
	//remove gameobject
}

void rock::update(float deltaTime)
{
	setSpritePos(getSpritePos() + displacement);
}

//method
void rock::calculateArc()
{
	//equations taken from a higher physics book and converted into C++ by Alexander MacDiarmid
	float v = 0;
	float vu = power*sin(angle);
	float a = 9.8;
	float vs = (pow(v, 2) - pow(vu, 2)) / -2 * a;
	float t = (v - vu) / -a;
	float hu = power*cos(angle);
	float hs = hu * (t * 2);
	float sintest = sin(90);

	displacement.x = (hs - playerPos.x) / (t * 100);
	displacement.y = (vs - playerPos.y) / (t * 100);
}
