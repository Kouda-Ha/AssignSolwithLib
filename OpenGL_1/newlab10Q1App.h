#pragma once
#include "SOF.h"
#include "CubeLab10.h"

enum {
	BASE,
	UPPER_ARM,
	ELBOW,
	FOREARM,
	COUNT
};

class NewLab10Q1App : public SOF::App
{

	std::vector<CubeLab10*> cubes;

	GLfloat delay = 0;
	glm::vec3 cameraDir = glm::vec3(1.0f, 0.0f, 0.0f);
	GLfloat cameraXAngle = 0.0f;
	GLfloat cameraYAngle = 0.0f;
	GLfloat cameraZAngle = 0.0f;
	GLint axis = 1;
	glm::vec3  theta = glm::vec3(0.0, 0.0, 0.0);
	GLfloat armMove = -0.025f;
	GLfloat count = 0;

public:
	virtual void Draw();
	virtual void Init();
	virtual void Update(float deltaT);
	virtual void KeyCallback(GLFWwindow*, int, int, int, int);
	virtual void MouseButtonCallback(GLFWwindow*, int, int, int); // mouse
};