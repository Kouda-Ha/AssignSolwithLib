#pragma once
#include "SOF.h"
#include "CubeLab12.h"
#include "FrameLab12.h"
#include "MovingFloorLab12.h"
#include "GunLab12.h"
#include "ObstaclesLab12.h"

class NewLab12Q1App : public SOF::App
{
	SOF::FontPlot* fontPlot;
	FrameLab12* frame;
	MovingFloorLab12* floor;
	CubeLab12* front;
	CubeLab12* back;

	GunLab12* gun;
	ObstaclesLab12* obstacles;
	bool win = false;
	bool lose = false;
	int score = 0;
	GLfloat delay = 0;
	glm::vec3 cameraPos = glm::vec3(0.0f, 6.0f, 9.0f);
	glm::vec3 cameraDir = glm::vec3(0.0f, 0.0f, 0.0f);

	std::string textToDrawWin = "Congratulations! You reached the goal!";
	std::string textToDrawLose = "Minus points! You Lose!";

	std::string textToDrawScore = "Score: ";	float textXPos = 50.0f;
	float textYPos = 50.0f;
	float scoreXPos = 600.0f;
	float scoreYPos = 50.0f;
	glm::vec4 textColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

public:
	virtual void Draw();
	virtual void Init();
	virtual void Update(float deltaT);
	virtual void KeyCallback(GLFWwindow*, int, int, int, int);
	virtual void MouseButtonCallback(GLFWwindow*, int, int, int) {};
};