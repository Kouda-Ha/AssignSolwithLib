#pragma once
#include "SOF.h"
#include "CubeLab12.h"
#include "FrameLab12.h"
#include "MovingFloorLab12.h"
#include "GunLab12.h"
#include "ObstaclesLab12.h"

class NewLab12Q1App : public SOF::App
{

	FrameLab12* frame;
	MovingFloorLab12* floor;
	CubeLab12* front;
	CubeLab12* back;

	GunLab12* gun;
	ObstaclesLab12* obstacles;


	GLfloat delay = 0;
	glm::vec3 cameraPos = glm::vec3(-6.0f, 5.0f, 11.0f);
	glm::vec3 cameraDir = glm::vec3(1.0f, 0.0f, 0.0f);

public:
	virtual void Draw();
	virtual void Init();
	virtual void Update(float deltaT);
	virtual void KeyCallback(GLFWwindow*, int, int, int, int);
	virtual void MouseButtonCallback(GLFWwindow*, int, int, int) {};
};