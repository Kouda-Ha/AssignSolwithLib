#pragma once
#include "SOF.h"

class CubeLab10
{
	// a coloured cube

	// shared resources betweeen all instances
	static SOF::ShaderProgram *pShader;
	static SOF::Geometry *pGeometry;
	static glm::mat4 *baseTransform;

	// per instance data
	glm::mat4 modelTransform;
	glm::vec4 cubeColor;
	GLboolean useColor = false;

public:
	CubeLab10();
	void SetBaseTransform(glm::mat4 &transform);
	void SetTransform(const glm::mat4 &transform);
	void Draw(const glm::mat4 &view, const glm::mat4 &proj);
	void setColor(const glm::vec4 &color);

	void NullTransform();
	void SetScale(const glm::vec3 &scale);
	void SetTranslate(const glm::vec3 &trans);
	void SetXRotation(float rot);
	void SetYRotation(float rot);
	void SetZRotation(float rot);
};