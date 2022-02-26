#include "stdafx.h"
#include "newlab12Q1App.h"
#include <random>


void NewLab12Q1App::Init()
{

	frame = new FrameLab12();

	floor = new MovingFloorLab12();
	floor->SetTranslate(glm::vec3(0.0, 0.0, -10.0));


	front = new CubeLab12();
	front->SetColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
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
	//// camera and projectio

	glm::mat4 view = glm::lookAt(cameraPos, cameraDir, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 proj = glm::perspective(glm::radians(70.0f), (float)SOF::Window::GetHeight() / SOF::Window::GetWidth(), 0.1f, 1000.0f);


	//frame->Draw(view, proj);

	floor->Draw(view, proj);
	floor->DrawLines(view, proj);

	front->Draw(view, proj);
	back->Draw(view, proj);

	gun->Draw(view, proj);

	obstacles->Draw(view, proj);

}


// responses to the passing of time. Called with before each draw()
void NewLab12Q1App::Update(float deltaT) { 


	floor->Update(deltaT);
	gun->Update(deltaT);
	obstacles->Update(deltaT);
}

void NewLab12Q1App::KeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods)
{

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


	case GLFW_KEY_R:
		gun->SetTranslate(glm::vec3(-0.1, 0.0, 0.0));
		break;
	case GLFW_KEY_T:
		gun->SetTranslate(glm::vec3(0.1, 0.0, 0.0));
		break;
	case GLFW_KEY_SPACE:
		gun->Fire();
		break;
	}

	

	//std::cout << cameraPos[0] << " " << cameraPos[1] << " " << cameraPos[2] << std::endl;
	//std::cout << cameraDir[0] << " " << cameraDir[1] << " " << cameraDir[2] << std::endl;

}



