#pragma once
#include "SOF.h"
#include "ObjectBaseLab12.h"

class GunLab12 : public ObjectBaseLab12
{
	GLfloat delay = 0;
	GLint count = 0;
	GLboolean fire = false;
	GLboolean animate = false;
	
public:
	GunLab12();

	void Fire();
	void Update(float deltaT);

	void SetTranslate(glm::vec3 trans);

};