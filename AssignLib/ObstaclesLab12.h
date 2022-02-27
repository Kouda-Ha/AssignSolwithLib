#pragma once
#include "SOF.h"
#include "ObjectBaseLab12.h"

class ObstaclesLab12 : public ObjectBaseLab12
{
	GLfloat delay = 0;
	GLint count = 0;
//	GLboolean fire = false;
	GLboolean animate = false;
	glm::vec3 translate;


	void SetUp();

public:
	ObstaclesLab12();
	void Reset();
	bool Collided(glm::vec3 posOfGun, glm::vec3 sizeOfGun);
	bool CollidePlayer(glm::vec3 posOfGun, glm::vec3 sizeOfGun);
	void Update(float deltaT);
};