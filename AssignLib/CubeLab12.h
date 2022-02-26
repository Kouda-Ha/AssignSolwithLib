#pragma once
#include "SOF.h"

class CubeLab12
{
	// a coloured cube

	// shared resources betweeen all instances
	static SOF::ShaderProgram *pShader;
	static SOF::Geometry *pGeometry;

	// per instance data
	glm::mat4 modelTransform;
	glm::vec4 cubeColor;
	GLboolean useColor = false;
	GLboolean render = true;

	void preDraw(const glm::mat4 &view, const glm::mat4 &proj);

public:
	CubeLab12();
	void SetTransform(const glm::mat4 &transform);
	glm::mat4 GetTransform();

	void Draw(const glm::mat4 &view, const glm::mat4 &proj);
	void Draw(const glm::mat4 &view, const glm::mat4 &proj, const glm::mat4 &base);

	void DrawLines(const glm::mat4 &view, const glm::mat4 &proj);
	void DrawLines(const glm::mat4 &view, const glm::mat4 &proj, const glm::mat4 &base);


	void SetColor(const glm::vec4 &color);
	void SetRender(const GLboolean r);
	GLboolean GetRender();

	void NullTransform();
	void SetScale(const glm::vec3 &scale);
	void SetTranslate(const glm::vec3 &trans);
	void SetXRotation(float rot);
	void SetYRotation(float rot);
	void SetZRotation(float rot);
};