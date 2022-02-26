#pragma once
#include "SOF.h"
#include "CubeLab11.h"

class ObjectBaseLab11
{

protected:
	// hander class for a list cubes
	std::vector<CubeLab11> cubeArray;
	glm::mat4 baseTransform;

public:
	ObjectBaseLab11();
	
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