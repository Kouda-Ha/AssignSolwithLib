#include "stdafx.h"
#include "MovingFloorLab12.h"




MovingFloorLab12::MovingFloorLab12()
{

	// build a set of 20 cubes
	float z = 0.0f;
	for (int i = 0; i < 20; i++)
	{
		CubeLab12 cube = CubeLab12();
		

		// cubes are yellow 
		cube.SetColor(glm::vec4(1.0, 1.0, 0.0, 1.0));
		// are also located at varying points in the z-axis
		cube.SetTranslate(glm::vec3(0, 0, z));
		// and extend in x
		cube.SetScale(glm::vec3(2.5, 0.2, 0.2));
		cubeArray.push_back(cube);
		z += 0.8f;

	}
	NullTransform(); // this just ensures we've got a base transform to manipulate

}



// responses to the passing of time. Called with before each draw()
void MovingFloorLab12::Update(float deltaT) {

	if (delay >= 0.05f)
	{
		SetTranslate(glm::vec3(0.0, 0.0, 0.08f));
		delay = 0.0f;
		count++;

		if (count > 9)
		{
			SetTranslate(glm::vec3(0.0, 0.0, -0.8f));
			count = 0;
			
		}
	}
	else
		delay += deltaT;
}