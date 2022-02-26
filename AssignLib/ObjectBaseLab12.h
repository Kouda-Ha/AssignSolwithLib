#pragma once
#include "SOF.h"
#include "CubeLab12.h"

class ObjectBaseLab12
{

protected:
	// hander class for a list cubes
	std::vector<CubeLab12> cubeArray;
	glm::mat4 baseTransform;

public:
	ObjectBaseLab12();
	
	void SetTransform(glm::mat4 &transform);
	glm::mat4 GetTransform();

	void Draw(const glm::mat4 &view, const glm::mat4 &proj);
	void DrawLines(const glm::mat4 &view, const glm::mat4 &proj);

	void printBaseTransform();

	void NullTransform();
	void SetScale(const glm::vec3 &scale);
	void SetTranslate(const glm::vec3 &trans);
	void SetXRotation(float rot);
	void SetYRotation(float rot);
	void SetZRotation(float rot);
};