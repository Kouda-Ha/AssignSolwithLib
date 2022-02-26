#include "stdafx.h"
#include "FrameLab11.h"


FrameLab11::FrameLab11()
{

	// build a set of 3 cubes
	for (int i = 0; i < 3; i++)
	{
		CubeLab11 cube = CubeLab11();
		cubeArray.push_back(cube);
	}

	// cube 0 is red and extends in x
	cubeArray[0].SetColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
	cubeArray[0].SetScale(glm::vec3(3.0, 0.1, 0.1));
	// cube 1 is green and extends in y
	cubeArray[1].SetColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
	cubeArray[1].SetScale(glm::vec3(0.1, 3.0, 0.1));
	// cube 2 is blue and extends in z
	cubeArray[2].SetColor(glm::vec4(0.0, 0.0, 1.0, 1.0));
	cubeArray[2].SetScale(glm::vec3(0.1, 0.1, 3.0));

	NullTransform(); // this just ensures we've got a base transform to manipulate

}


