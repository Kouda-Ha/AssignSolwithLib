// Example2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SOF.h"
#include "newlab12Q1App.h"

int main()
{
	NewLab12Q1App *app = new NewLab12Q1App();
	SOF::Window::CreateWindow(768, 768, "Lab 11 Q2", app);
	SOF::Window::SetBackground(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	SOF::Window::Run();

    return 0;
}

