#include "stdafx.h"
#include "newlab12Q1App.h"
#include <random>
#include <iostream>
/*
* Question 4:
*			 A demonstration of collision detection and interactive object control via a small 3D 
*			 dodging game. A "floor" should move towards the viewer, on which a player cube should 
*			 be located. At random intervals, "obstacles" (also cubes) should appear from behind a 
*			 back wall and move towards the viewer (as a consequence of the floor moving). The player 
*			 is required to move forward and get to the back wall without hitting any obstacles (it 
*			 is possible to dodge or jump them). 
*			 Additional marks will be awarded for the inclusion of collision detection, randomization 
*			 of the object shape, inclusion of a scoring mechanism (displayed via text) and 
*			 inclusion of speed-ups.
*/

void NewLab12Q1App::Init()
{
	fontPlot = new SOF::FontPlot("Fonts/lucida32");

	frame = new FrameLab12();

	floor = new MovingFloorLab12();
	floor->SetTranslate(glm::vec3(0.0, 0.0, -10.0));

	front = new CubeLab12();
	front->SetColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
	front->SetTranslate(glm::vec3(0.0, 0.0, 6.5));
	front->SetScale(glm::vec3(5.0, 1.0, 0.1));

	back = new CubeLab12();
	back->SetColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
	back->SetTranslate(glm::vec3(0.0, 0.0, -9.5));
	back->SetScale(glm::vec3(8.0, 8.0, 0.1));

	gun = new GunLab12();
	gun->SetTranslate(glm::vec3(0.0, 0.0, 5.8));

	obstacles = new ObstaclesLab12();
	obstacles->SetTranslate(glm::vec3(0.0, 0.0, -8.0));

	// some render states
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void NewLab12Q1App::Draw()
{
	//// camera and projection
	glm::mat4 view = glm::lookAt(cameraPos, cameraDir, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 proj = glm::perspective(glm::radians(70.0f), (float)SOF::Window::GetHeight() / SOF::Window::GetWidth(), 0.1f, 1000.0f);
	
	//frame->Draw(view, proj);

	floor->Draw(view, proj);
	floor->DrawLines(view, proj);
	front->Draw(view, proj);
	back->Draw(view, proj);

	gun->Draw(view, proj);
	obstacles->Draw(view, proj);
	fontPlot->DrawString(scoreXPos, scoreYPos, std::to_string(score), textColor);

	if (win)
	{
		fontPlot->DrawString(textXPos, textYPos, textToDraw, textColor);
	}
	if (lose)
	{
		fontPlot->DrawString(textXPos, textYPos, textToDrawLose, textColor);
	}
}

// responses to the passing of time. Called with before each draw()
void NewLab12Q1App::Update(float deltaT) { 
	if (win)
	{
		return; // If reach end of tredmill, game ends.
	}

	if (lose)
	{
		return;
	}

	floor->Update(deltaT);
	
	gun->Update(deltaT);
	
	glm::vec3 posOfGun = glm::vec3();
	glm::vec3 posOfPlayer = glm::vec3();
	
	gun->GunPosition(posOfGun);
	gun->PlayerPosition(posOfPlayer);
	
	obstacles->Update(deltaT);


	if (obstacles->CollidePlayer(posOfPlayer, glm::vec3(0.4, 0.4, 0.5)))
	{
		gun->Hit(); // if gun(player) collides with obstacle, reset gun(player) position to back of platform
		obstacles->Reset(); // obstacle destroy, respawn at the back (stops jittering Gun(player) until obstacle leaves hit area)
		score--;
		if (score <= -1)
		{
			lose = true;
		}
	}

	if (obstacles->Collided(posOfGun, glm::vec3(0.4, 0.4, 0.5)))
	{
		obstacles->Reset();
		gun->Reset();
		score++;
	}

	if (posOfPlayer[2] < -10) // If Gun(Player) reaches the back wall, game win
	{
		win = true;
	}

//	std::cout << cameraPos[0] << " " << cameraPos[1] << " " << cameraPos[2] << " " << std::endl; // cam position
}

void NewLab12Q1App::KeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
	if (win)
	{
		return; // If reach end of tredmill, game ends.
	}

	if (lose)
	{
		return;
	}

	// Moving camera angle
	switch (key) {
	case GLFW_KEY_A:
		cameraPos[0] += 0.5;
		break;
	case GLFW_KEY_S:
		cameraPos[1] += 0.5;
		break;
	case GLFW_KEY_D:
		cameraPos[2] += 0.5;
		break;
	case GLFW_KEY_Z:
		cameraPos[0] -= 0.5;
		break;
	case GLFW_KEY_X:
		cameraPos[1] -= 0.5;
		break;
	case GLFW_KEY_C:
		cameraPos[2] -= 0.5;
		break;
	case GLFW_KEY_H:
		cameraDir[0] += 0.5;
		break;
	case GLFW_KEY_J:
		cameraDir[1] += 0.5;
		break;
	case GLFW_KEY_K:
		cameraDir[2] += 0.5;
		break;
	case GLFW_KEY_N:
		cameraDir[0] -= 0.5;
		break;
	case GLFW_KEY_M:
		cameraDir[1] -= 0.5;
		break;
	case GLFW_KEY_COMMA:
		cameraDir[2] -= 0.5;
		break;

	// Gun(Player) controller (Arrow keys to move, Space to shoot bullet)
	case GLFW_KEY_LEFT:
		gun->SetTranslate(glm::vec3(-0.1, 0.0, 0.0));
		break;
	case GLFW_KEY_RIGHT:
		gun->SetTranslate(glm::vec3(0.1, 0.0, 0.0));
		break;
	case GLFW_KEY_DOWN:
		gun->SetTranslate(glm::vec3(0.0, 0.0, 0.1));
		break;
	case GLFW_KEY_UP:
		gun->SetTranslate(glm::vec3(0.0, 0.0, -0.1));
		break;

	// Fire gun bullet
	case GLFW_KEY_SPACE:
		gun->Fire();
		break;
	}
}