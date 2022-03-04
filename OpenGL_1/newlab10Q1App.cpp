#include "stdafx.h"
#include "newlab10Q1App.h"
#include <random>


void NewLab10Q1App::Init()
{
	// build a set of 4 cubes (Base, Upper arm, Elbow, Lower arm)
	for (int i = 0; i < 4; i++)
	{
		CubeLab10 *cube = new CubeLab10();
		cubes.push_back(cube);
	}

	// if we wanted to move the object, we'd make a call to baseTransform here
	// but we can wait until the draw() for that.

	// set up the relative shapes - use matrix tranforms internally
	// model matrix - Base cube (red)
	// This sits at the origin, so we just need to sort out its size and aspect ratio
//	cubes[0]->SetScale(glm::vec3(5.0, 0.25, 5.0));
	cubes[0]->setColor(glm::vec4(1.0, 0.0, 0.0, 1.0));

	// model matrix - Lower Arm Cube (blue)
	cubes[1]->SetTranslate(glm::vec3(2, 5.0, 0));
	cubes[1]->SetScale(glm::vec3(2.5, 0.5, 0.5));
	cubes[1]->setColor(glm::vec4(0.0, 0.0, 1.0, 1.0));

	// model matrix - Upper Arm Cube (green)
	cubes[2]->SetTranslate(glm::vec3(4.5, 2.5, 0));
	cubes[2]->SetScale(glm::vec3(0.5, 2.5, 0.5));
	cubes[2]->setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));

	// model matrix - Elbow Cube (orange)
	cubes[3]->SetTranslate(glm::vec3(4.5, 5.0, 0));
	cubes[3]->SetScale(glm::vec3(0.6, 0.3, 0.3));
	cubes[3]->setColor(glm::vec4(1.0, 0.5, 0.0, 1.0));
	/*
	// model matrix - left leg
	cubes[4]->SetTranslate(glm::vec3(0.6, -1.0, 0));
	cubes[4]->SetScale(glm::vec3(0.3, 1.0, 0.3));
	cubes[4]->setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));

	// model matrix - right leg
	cubes[5]->SetTranslate(glm::vec3(-0.6, -1.0, 0));
	cubes[5]->SetScale(glm::vec3(0.3, 1.0, 0.3));
	cubes[5]->setColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
	*/

	// some render states
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}


// responses to the passing of time. Called with before each draw()
void NewLab10Q1App::Update(float deltaT)
{
	if (delay >= 0.01f)
	{
		theta[axis] += 0.5f;

		if (theta[axis] > 360.0) {
			theta[axis] -= 360.0;
		}
		delay = 0.0f;

		if (count < 50)
			armMove += 0.001f;
		else
			armMove -= 0.001f;
		count++;
		if (count >= 100)
		{
			count = 0;
			armMove = -0.025f;
			
			cubes[1]->NullTransform();
			cubes[1]->SetXRotation(45);
			cubes[1]->SetYRotation(45);
			cubes[1]->SetZRotation(45);
		//	cubes[1]->SetTranslate(glm::vec3(2, 5.0, 0));
		//	cubes[1]->SetScale(glm::vec3(2.5, 0.5, 0.5));
			
			/*
			cubes[5]->NullTransform();
			cubes[5]->SetTranslate(glm::vec3(-0.6, -1.0, 0));
			cubes[5]->SetScale(glm::vec3(0.3, 1.0, 0.3));
			*/
		}
	}
	else
		delay += deltaT;
}

void NewLab10Q1App::KeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
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
	model = glm::rotate(model, (float)glm::radians(theta[0]), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, (float)glm::radians(theta[1]), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, (float)glm::radians(theta[2]), glm::vec3(0.0f, 0.0f, 1.0f));
	cubes[0]->SetBaseTransform(model);
	
	
	// internal animation (move the legs...)
//	cubes[1]->SetTranslate(glm::vec3(0, +armMove, 0));
//	cubes[3]->SetTranslate(glm::vec3(0, -armMove, 0));
	
	
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
