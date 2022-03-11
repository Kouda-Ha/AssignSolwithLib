#pragma once
#include "SOF.h"
#include "ObjectBaseLab12.h"

class GunLab12 : public ObjectBaseLab12
{
public:
	// Using enum to make it more user friendly way naming things, "UP", "DOWN", etc
	enum Direction {
		UP, RIGHT, DOWN, LEFT
	};

private:
	GLfloat delay = 0;
	GLfloat delayMovement = 0;
	GLfloat dragFactorMovement = 0.05f;
	GLint count = 0;
	GLboolean fire = false;
	GLboolean animate = false;
	bool direction[4] = { false };

public:
	GunLab12();

	void Fire();
	void Hit();
	void Reset();
	void Update(float deltaT);
	void GunPosition(glm::vec3& trans);
	void PlayerPosition(glm::vec3& trans);
	void SetTranslate(glm::vec3 trans);
	void press(Direction dir, bool isKeyPress);
};