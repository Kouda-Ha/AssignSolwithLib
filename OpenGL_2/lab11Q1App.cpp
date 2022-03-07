#include "stdafx.h"
#include "lab11Q1App.h"
#include <random>


// You're in the wrong place, I did demonstration questions 3 (articulated motion) and 4 (dodging game), please see
// OpenGL_1 and OpenGL_3 for my solutions to the coursework, thank you :)


void Lab11Q1App::Init()
{
	frame = new FrameLab11();

	// some render states
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

// responses to the passing of time. Called with before each draw()
void Lab11Q1App::Update(float deltaT) { 

	if (delay >= 0.2f)
	{
		delay = 0.0f;
	}
	else
		delay += deltaT;

}

void Lab11Q1App::KeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods)
{

	switch (key) {
	case GLFW_KEY_A:
		cameraPos[0] += 1;
		break;
	case GLFW_KEY_S:
		cameraPos[1] += 1;
		break;
	case GLFW_KEY_D:
		cameraPos[2] += 1;
		break;
	case GLFW_KEY_Z:
		cameraPos[0] -= 1;
		break;
	case GLFW_KEY_X:
		cameraPos[1] -= 1;
		break;
	case GLFW_KEY_C:
		cameraPos[2] -= 1;
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
	}

	std::cout << cameraPos[0] << " " << cameraPos[1] << " " << cameraPos[2] << std::endl;
	std::cout << cameraDir[0] << " " << cameraDir[1] << " " << cameraDir[2] << std::endl;

}

void Lab11Q1App::Draw()
{
	//// camera and projectio
	glm::mat4 view = glm::lookAt(cameraPos, cameraDir, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 proj = glm::perspective(glm::radians(70.0f), (float)SOF::Window::GetHeight() / SOF::Window::GetWidth(), 0.1f, 1000.0f);

	frame->Draw(view, proj);
	
}
