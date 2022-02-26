#pragma once
#include "ObjectBaseLab11.h"

class RandomCubesLab11 : public ObjectBaseLab11
{
	GLfloat delay = 0;

public:

	RandomCubesLab11(int num);

	void Update(float deltaT);

};