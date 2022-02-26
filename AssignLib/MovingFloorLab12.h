#pragma once
#include "SOF.h"
#include "ObjectBaseLab12.h"

class MovingFloorLab12 : public ObjectBaseLab12
{
	GLfloat delay = 0;
	int count = 0;

public:
	MovingFloorLab12();

	void Update(float deltaT);

};