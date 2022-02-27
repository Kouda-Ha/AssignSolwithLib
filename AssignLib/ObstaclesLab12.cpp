#include "stdafx.h"
#include "ObstaclesLab12.h"
#include <random>

ObstaclesLab12::ObstaclesLab12()
{

	// build a set of 3 cubes
	for (int i = 0; i < 3; i++)
	{
		CubeLab12 cube = CubeLab12();
		cubeArray.push_back(cube);
	}
	SetUp();
	
}

void ObstaclesLab12::SetUp()
{
	// make some cubes, with random sizes and positions
	// random number generator
	std::random_device device;
	std::mt19937 rand_gen(device());
	std::uniform_real_distribution<> rand_dist1(-1.0f, 1.0f);
	std::uniform_real_distribution<> rand_dist2(0.0f, 1.0f);

	// build a set of 3 cubes
	for (int i = 0 ; i < 3 ; i++)
	{
		cubeArray[i].NullTransform();
		// cubes are green 
		cubeArray[i].SetColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		// are also located at varying points in the z-axis
		cubeArray[i].SetTranslate(glm::vec3(2.0 * rand_dist1(rand_gen), 0.4,  4.0 *  rand_dist1(rand_gen)));
		// and are mostly cubic (but a bit extended in Z)
		cubeArray[i].SetScale(glm::vec3(1.0 * rand_dist2(rand_gen), 0.4 * rand_dist2(rand_gen), 0.5 * rand_dist2(rand_gen)));
		// but we won't initally draw them
		cubeArray[i].SetRender(false);

	}
	NullTransform(); // this just ensures we've got a base transform to manipulate
}

void ObstaclesLab12::Reset() {
	SetUp();
	SetTranslate(glm::vec3(0.0, 0.0, -8.0f));
	count = 0;
}
// Checking if the bullet collided with an obstacle,
// we assume here there is no rotation.
bool ObstaclesLab12::Collided(glm::vec3 posOfGun, glm::vec3 sizeOfGun)
{
	bool retVal = false;
	glm::mat4 trans1 = GetTransform();
	for (int i = 0; i < 3; i++)
	{
		glm::mat4 trans2 = cubeArray[i].GetTransform();
		glm::mat4 trans3 = trans1 + trans2;
		glm::vec3 pos = glm::vec3(trans3[3][0], trans3[3][1], trans3[3][2]);
		glm::vec3 size = glm::vec3(trans2[0][0], trans2[1][1], trans2[2][2]);

		int flags = 0;
		const int hit = 7;
		for (int a = 0; a < 3; a++) // 3 axies, x, y and z
		{
			if (pos[a] - posOfGun[a] < sizeOfGun[a] + size[a] &&
				pos[a] - posOfGun[a] > -sizeOfGun[a] - size[a])
			{
				flags |= 1 << a;
			}
		}
		if (flags == hit) 
		{
			cubeArray[i].SetColor(glm::vec4(0.0, 0.0, 0.0, 1.0));
			retVal = true;
		}
		else 
		{
			cubeArray[i].SetColor(glm::vec4(0.0, 1.0, 0.0, 1.0));
		}
	}
	return retVal;
}

// Checking if the Player has collided with an obstacle
bool ObstaclesLab12::CollidePlayer(glm::vec3 posOfGun, glm::vec3 sizeOfGun)
{
	glm::mat4 trans1 = GetTransform();
	for (int i = 0; i < 3; i++)
	{
		glm::mat4 trans2 = cubeArray[i].GetTransform();
		glm::mat4 trans3 = trans1 + trans2;
		glm::vec3 pos = glm::vec3(trans3[3][0], trans3[3][1], trans3[3][2]);
		glm::vec3 size = glm::vec3(trans2[0][0], trans2[1][1], trans2[2][2]);

		int flags = 0;
		const int hit = 7;
		for (int a = 0; a < 3; a++) // 3 axies, x, y and z
		{
			if (pos[a] - posOfGun[a] < sizeOfGun[a] + size[a] &&
				pos[a] - posOfGun[a] > -sizeOfGun[a] - size[a])
			{
				flags |= 1 << a;
			}
		}
		if (flags == hit)
		{
			return true;
		}
	}
	return false;
}

// responses to the passing of time. Called with before each draw()
void ObstaclesLab12::Update(float deltaT) {
		if (delay >= 0.05f)
		{
			SetTranslate(glm::vec3(0.0, 0.0, 0.08f));
			delay = 0.0f;
			count++;

			if (count > 259)
			{
				Reset();
			}

			int i = 0;
			glm::mat4 trans1 = GetTransform();
			for (int i = 0; i < 3; i++)
			{
				glm::mat4 trans2 = cubeArray[i].GetTransform();
				double x = trans1[3][0] + trans2[3][0];
				double z = trans1[3][2] + trans2[3][2];
				
				if (x >= -2.5 && x <= 2.5 && z >= -9.0 && z <= 6.0)
					cubeArray[i].SetRender(true);
				else
					cubeArray[i].SetRender(false);	
			}
		}
		else
			delay += deltaT;

}