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
	finalSpeed.x = pow((power*sin(angle)), 2);

	maxHeight = (0 - finalSpeed.x) / (2 * 9.8f);
	time = (0 - finalSpeed.x) / 9.8f;
	range = finalSpeed.x * time;

	displacement.x = (maxHeight - playerPos.x) / time;
	displacement.y = ((range / 2) - playerPos.y) / time;
}
