#include "stdafx.h"
#include "newlab10Q1App.h"
#include <random>
/*
* Unit: 6G5Z2102 Computer Graphics (1CWK100 Portfolio)
* Student Name: Owen Clifford Park (MMU-ID: 19095713)
* Question 3: 
*			A demonstration of the nature of articulated motion.As a minimum, this will display a composite object built
*			of two components, a baseand arm.It is acceptable that these be simple coloured boxes.At a minimum, the
*			base should translateand both should both rotate, so that the arms is moved relative to the base.Additional
*			marks will be awarded for the inclusion of additional components(so an upper and lower arm, with the upper
*			arm connected to the lower arm with an \elbow"), and for the presence of interactive movement (preferably via
*			the mouse).
*/
void NewLab10Q1App::Init()
{
	// build a set of 4 cubes (Base, Upper arm, Elbow, Lower arm)
	for (int i = 0; i < 4; i++)
	{
		CubeLab10 *cube = new CubeLab10();
		cubes.push_back(cube);
	}

	// set up the relative shapes - use matrix tranforms internally
	// model matrix - Base cube (red)
	// This sits at the origin, so we just need to sort out its size and aspect ratio
	cubes[BASE]->SetScale(glm::vec3(0.6, 0.6, 0.6), false);
	cubes[BASE]->setColor(glm::vec4(1.0, 0.0, 0.0, 0.2));

	// model matrix - Lower Arm Cube (blue)
	cubes[UPPER_ARM]->SetScale(glm::vec3(0.5, 2.5, 0.5));
	cubes[UPPER_ARM]->SetTranslate(glm::vec3(0, 0, 0));
	cubes[UPPER_ARM]->setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));

	// model matrix - Upper Arm Cube (green)
	cubes[FOREARM]->SetScale(glm::vec3(0.5, 2.5, 0.5));
	cubes[FOREARM]->SetTranslate(glm::vec3(0, 0, 0));
	cubes[FOREARM]->setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));

	// model matrix - Elbow Cube (orange)
	cubes[ELBOW]->SetScale(glm::vec3(0.6, 0.6, 0.6), false);
	cubes[ELBOW]->SetTranslate(glm::vec3(0, 5, 0));
	cubes[ELBOW]->setColor(glm::vec4(1.0, 0.5, 0.0, 1.0));

	// some render states
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

// responses to the passing of time. Called with before each draw()
void NewLab10Q1App::Update(float deltaT)
{
	count += deltaT;
	constexpr float pi = glm::pi<float>();
	if (upperarmAnimate == true && upperarmTime < pi) {
		upperarmTime += deltaT;
	}
	else if (upperarmAnimate == false && upperarmTime > 0) {
		upperarmTime -= deltaT;
	}

	if (forearmAnimate == true && forearmTime < pi) {
		forearmTime += deltaT;
	}
	else if (forearmAnimate == false && forearmTime > 0) {
		forearmTime -= deltaT;
	}

	cubes[BASE]->NullTransform();
	cubes[BASE]->SetYRotation(count * 10);

	cubes[UPPER_ARM]->NullTransform();
	cubes[UPPER_ARM]->SetZRotation(glm::cos(upperarmTime) * 90);

	cubes[ELBOW]->NullTransform();
	cubes[ELBOW]->SetTranslate(glm::vec3(0, 5, 0));
	cubes[ELBOW]->SetZRotation((1 + glm::cos(forearmTime)) / 2 * 180 / 4);
	cubes[FOREARM]->NullTransform();
	cubes[FOREARM]->SetTranslate(glm::vec3(0, 0, 0));
	cubes[FOREARM]->SetZRotation((1 + glm::cos(forearmTime)) /2 * 180 / 2);

}

void NewLab10Q1App::KeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
	std::cout << key << std::endl;
	if (key == GLFW_KEY_A)
		cameraXAngle += 5;
	if (key == GLFW_KEY_S)
		cameraYAngle += 5;
	if (key == GLFW_KEY_D)
		cameraZAngle += 5;
	if (key == GLFW_KEY_Z)
		cameraXAngle -= 5;
	if (key == GLFW_KEY_X)
		cameraYAngle -= 5;
	if (key == GLFW_KEY_C)
		cameraZAngle -= 5;
	
	if (key == GLFW_KEY_U)
		axis = 0;
	if (key == GLFW_KEY_I)
		axis = 1;
	if (key == GLFW_KEY_O)
		axis = 2;

}

// processes keyboard events
void NewLab10Q1App::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) 
{
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	std::cout << button << " " << action << " " << mods << " " << xpos << " " << ypos << std::endl;
	if (button == 0 && action == 0) // left mouse click
	{
		std::cout << "hit L button" << std::endl;
		upperarmAnimate = !upperarmAnimate;
	}

	if (button == 1 && action == 0) // right mouse click
	{
		forearmAnimate = !forearmAnimate;
		std::cout << "hit R button" << std::endl;
	}
}

void NewLab10Q1App::Draw()
{
	//// camera and projection 
	glm::vec3 cameraPos = glm::vec3(0.0f, 5.0f, 10.0f);
	cameraDir[0] = glm::radians(cameraXAngle);
	cameraDir[1] = glm::radians(cameraYAngle);
	cameraDir[2] = glm::radians(cameraZAngle);
	glm::mat4 view = glm::lookAt(cameraPos, cameraDir, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 proj = glm::perspective(glm::radians(70.0f), (float)SOF::Window::GetHeight() / SOF::Window::GetWidth(), 0.1f, 1000.0f);
	// model matrix (rotate the whole thing)
	glm::mat4 model = glm::mat4();
	model = glm::translate(model, glm::vec3(0.0f, -5.0, -10.0f));
	model = glm::scale(model, glm::vec3(1.5, 1.5, 1.5));
	cubes[0]->SetBaseTransform(model);
	
	// draw the cubes
	glm::mat4 cubeTrans;
	glm::mat4 compoundTrans;
	for (auto cube : cubes) {
		cubeTrans = cube->getTransform();
		compoundTrans *= cubeTrans;
		cube->SetTransform(compoundTrans);
		cube->Draw(view, proj);
		cube->SetTransform(cubeTrans);
	}
}
