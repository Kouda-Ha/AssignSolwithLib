#include "stdafx.h"
#include "RandomCubesLab11.h"
#include <time.h>




RandomCubesLab11::RandomCubesLab11(int num)
{

	// build a set of num cubes

	srand((int)time(nullptr));
	double r = rand(); // an extra call improves randomness! We don't use r.

	for (int i = 0; i < num; i++)
	{
		CubeLab11 cube = CubeLab11();
		

		// cubes are yellow 
		cube.SetColor(glm::vec4(1.0, 1.0, 0.0, 1.0));


		// are also located at varying points in the three-axes

		double x = ((rand() % 101) / 10.0) - 5.0;
		double y = ((rand() % 101) / 10.0) - 5.0;
		double z = ((rand() % 101) / 10.0) - 5.0;

		cube.SetTranslate(glm::vec3(x, y, z));

		double s = ((rand() % 100) / 20.0) ;
		cube.SetScale(glm::vec3(s*0.2, s*0.2, s*0.2));


		cubeArray.push_back(cube);
	

	}
	NullTransform(); // this just ensures we've got a base transform to manipulate

}



// responses to the passing of time. Called with before each draw()
void RandomCubesLab11::Update(float deltaT) {

	if (delay >= 0.05f)
	{
		
		for (int i = 0; i < (int) cubeArray.size(); i++)
		{
			double x = ((rand() % 100) / 1000.0) - 0.05;
			double y = ((rand() % 100) / 1000.0) - 0.05;
			double z = ((rand() % 100) / 1000.0) - 0.05;
			cubeArray[i].SetTranslate(glm::vec3(x, y, z));
		}
		delay = 0.0f;
		
	}
	else
		delay += deltaT;
}