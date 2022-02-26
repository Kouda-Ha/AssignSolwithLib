#pragma once
#include "SOF.h"
#include "CubeLab11.h"
#include "FrameLab11.h"

class Lab11Q1App : public SOF::App
{

	FrameLab11* frame;


	GLfloat delay = 0;
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 10.0f);
	glm::vec3 cameraDir = glm::vec3(1.0f, 0.0f, 0.0f);

	float scale = 1.0;

public:
	virtual void Draw();
	virtual void Init();
	virtual void Update(float deltaT);
	virtual void KeyCallback(GLFWwindow*, int, int, int, int);
	virtual void MouseButtonCallback(GLFWwindow*, int, int, int) {};
};