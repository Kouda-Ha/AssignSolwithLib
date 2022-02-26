#include "stdafx.h"
#include "ObjectBaseLab11.h"




ObjectBaseLab11::ObjectBaseLab11()
{
	baseTransform = glm::mat4();
}


void ObjectBaseLab11::Draw(const glm::mat4 &view, const glm::mat4 &proj )
{
	for (auto cube : cubeArray)
		if (cube.GetRender()) 
			cube.Draw(view, proj, baseTransform);
}

void ObjectBaseLab11::DrawLines(const glm::mat4 &view, const glm::mat4 &proj)
{
	for (auto cube : cubeArray)
		if (cube.GetRender()) 
			cube.DrawLines(view, proj, baseTransform);
}

void ObjectBaseLab11::SetTransform(glm::mat4 &transform)
{
	baseTransform = transform;
}

glm::mat4 ObjectBaseLab11::GetTransform()
{
	return baseTransform;
}

void ObjectBaseLab11::printBaseTransform()
{
	glm::mat4 bt = baseTransform;
	std::cout << bt[0][0] << " " << bt[1][0] << " " << bt[2][0] << " " << bt[3][0] << std::endl;
	std::cout << bt[0][1] << " " << bt[1][1] << " " << bt[2][1] << " " << bt[3][1] << std::endl;
	std::cout << bt[0][2] << " " << bt[1][2] << " " << bt[2][2] << " " << bt[3][2] << std::endl;
	std::cout << bt[0][3] << " " << bt[1][3] << " " << bt[2][3] << " " << bt[3][3] << std::endl;
}

void ObjectBaseLab11::NullTransform() 
{
	baseTransform = glm::mat4();
}

void ObjectBaseLab11::SetScale(const glm::vec3 &scale) 
{
	baseTransform = glm::scale(baseTransform, scale);
}


void ObjectBaseLab11::SetTranslate(const glm::vec3 &trans) 
{
	baseTransform = glm::translate(baseTransform, trans);
}

void ObjectBaseLab11::SetXRotation(float rot) 
{
	baseTransform = glm::rotate(baseTransform, (float)glm::radians(rot), glm::vec3(1.0f, 0.0f, 0.0f));
}

void ObjectBaseLab11::SetYRotation(float rot) 
{
	baseTransform = glm::rotate(baseTransform, (float)glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));
}

void ObjectBaseLab11::SetZRotation(float rot) 
{
	baseTransform = glm::rotate(baseTransform, (float)glm::radians(rot), glm::vec3(0.0f, 0.0f, 1.0f));
}