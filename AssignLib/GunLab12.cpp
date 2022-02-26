#include "stdafx.h"
#include "GunLab12.h"




GunLab12::GunLab12()
{

	// build a set of 2 cubes
	float y = 0.0f;
	for (int i = 0; i < 2; i++)
	{
		CubeLab12 cube = CubeLab12();
		

		// cubes are red 
		cube.SetColor(glm::vec4(1.0, 0.0, 0.0, 1.0));
		// are also located at varying points in the z-axis
		cube.SetTranslate(glm::vec3(0, y, 0));
		// and are mostly cubic (but a bit extended in Z)
		cube.SetScale(glm::vec3(0.4, 0.4, 0.5));
		cubeArray.push_back(cube);
		y += 0.8f;

	}
	NullTransform(); // this just ensures we've got a base transform to manipulate

}

void GunLab12::Fire()
{
	if (!animate)
		fire = true;
}

void GunLab12::SetTranslate(glm::vec3 trans)
{
	if (!fire)
		ObjectBaseLab12::SetTranslate(trans);
	else
	{
		cubeArray[0].SetTranslate(trans);
	}

}

// responses to the passing of time. Called with before each draw()
void GunLab12::Update(float deltaT) {

	if (fire) {
		if (delay >= 0.05f)
		{
			animate = true;
			cubeArray[1].SetTranslate(glm::vec3(0.0, 0.0, -0.8f));
			count++;

			if (count > 40)
			{
				animate = false;
				fire = false;
				
				glm::mat4 transf = GetTransform();
				glm::mat4 c1transf = cubeArray[0].GetTransform();
				transf = glm::translate(transf, glm::vec3(c1transf[3][0], c1transf[3][1], c1transf[3][2]));
				SetTransform(transf);
				

				float y = 0.0f;
				for (int i = 0; i < 2; i++)
				{
					// reset their transform
					cubeArray[i].NullTransform();
					// are also located at varying points in the z-axis
					cubeArray[i].SetTranslate(glm::vec3(0, y, 0));
					// and are mostly cubic (but a bit extended in Z)
					cubeArray[i].SetScale(glm::vec3(0.4, 0.4, 0.5));
			
					y += 0.8f;

				}
				count = 0;
			}
			delay = 0.0f;
		}
		else
			delay += deltaT;
	}
}