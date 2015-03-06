#include "rock.h"
#include <iostream>
#include <cmath>

//constructor
rock::rock()
{
	cout << "error the rock constructor shoud not be called" << endl;
}
rock::rock(float Tangle, float Tpower)
{
	angle = Tangle;
	power = Tpower;
	calculateArc();
}

//destructor
rock::~rock()
{
	//remove gameobject
}

//method
void rock::calculateArc()
{
	//equations taken from a higher physics book and converted into C++ by Alexander MacDiarmid
	float finalSpeed = pow((power*sin(angle)),2);

	maxHeight = (0 - finalSpeed) / (2 * 9.8f);
	time = (0 - finalSpeed) / 9.8f;
	range = finalSpeed * time;
}
