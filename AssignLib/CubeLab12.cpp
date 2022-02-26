#include "stdafx.h"
#include "CubeLab12.h"

// statics

SOF::ShaderProgram *CubeLab12::pShader = nullptr;
SOF::Geometry *CubeLab12::pGeometry = nullptr;

CubeLab12::CubeLab12()
{
	// load the shared resources, if this has not already been done
	if (pGeometry == nullptr)
	{
		pShader = new SOF::ShaderProgram("shaders/lab12_vertex-shader.glsl","shaders/lab12_fragment-shader.glsl");
		int nVertex = 6 * 2 * 3; // 6 faces * 2 triangles * 3 vertices each	
		pGeometry = new SOF::Geometry(nVertex);
		// make a cube, centred on the origin
		glm::vec3 vertexPositions[] = {
			glm::vec3(-1.0f, -1.0f, -1.0f),
			glm::vec3(-1.0f,  1.0f, -1.0f),
			glm::vec3(1.0f,  1.0f, -1.0f),
			glm::vec3(1.0f, -1.0f, -1.0f),
			glm::vec3(-1.0f, -1.0f,  1.0f),
			glm::vec3(-1.0f,  1.0f,  1.0f),
			glm::vec3(1.0f,  1.0f,  1.0f),
			glm::vec3(1.0f, -1.0f,  1.0f)
		};

		glm::vec4 vertexColors[] = {
			glm::vec4(0.0, 0.0, 0.0, 1.0),  // black
			glm::vec4(1.0, 0.0, 0.0, 1.0),  // red
			glm::vec4(1.0, 1.0, 0.0, 1.0),  // yellow
			glm::vec4(0.0, 1.0, 0.0, 1.0),  // green
			glm::vec4(0.0, 0.0, 1.0, 1.0),  // blue
			glm::vec4(1.0, 0.0, 1.0, 1.0),  // magenta
			glm::vec4(1.0, 1.0, 1.0, 1.0),  // white
			glm::vec4(0.0, 1.0, 1.0, 1.0)   // cyan
		};

		int triangles[] = { 0,4,5,0,5,1, 1,5,6,1,6,2, 2,6,7,2,7,3, 3,7,4,3,4,0, 4,7,6,4,6,5, 3,0,1,3,1,2 };

		std::vector<glm::vec3> vertexPos;
		std::vector<glm::vec4> vertexColor;
		for (int i = 0; i < nVertex; i++)
		{
			vertexPos.push_back(vertexPositions[triangles[i]]);	
			vertexColor.push_back(vertexColors[triangles[i]]);
		}


		pGeometry->AddAttribute(vertexPos, "vertexPos");
		pGeometry->AddAttribute(vertexColor, "vertexColor");
		pGeometry->Finalize(pShader);

	}

}

void CubeLab12::SetRender(const GLboolean r)
{
	render = r;
}
GLboolean CubeLab12::GetRender()
{
	return render;
}

void CubeLab12::preDraw(const glm::mat4 &view, const glm::mat4 &proj)
{
	
	// set the shader uniforms
	// enable the shader
	pShader->Use();

	if (useColor)
	{
		pShader->SetUniformVec4("fixedColor", cubeColor);
		pShader->SetUniformInt("useFixedColor", 1);
	}
	else
		pShader->SetUniformInt("useFixedColor", 0);


	// camera
	glm::vec3 cameraPosition = (glm::vec3)(glm::inverse(view)[3]);
	pShader->SetUniformMat4("vpm", proj*view);
}

void CubeLab12::Draw(const glm::mat4 &view, const glm::mat4 &proj)
{
	glm::mat4 b = glm::mat4();
	Draw(view, proj, b);
}



void CubeLab12::Draw(const glm::mat4 &view, const glm::mat4 &proj, const glm::mat4 &base)
{

	preDraw(view, proj);

	// model
	glm::mat4 combTrans = base * modelTransform;
	pShader->SetUniformMat4("mdm", combTrans);

	// draw the geometry
	pGeometry->DrawPrimitives();
}


void CubeLab12::DrawLines(const glm::mat4 &view, const glm::mat4 &proj)
{
	glm::mat4 b = glm::mat4();
	DrawLines(view, proj, b);
}

void CubeLab12::DrawLines(const glm::mat4 &view, const glm::mat4 &proj, const glm::mat4 &base)
{
	preDraw(view, proj);

	// model
	glm::mat4 combTrans = base * modelTransform;
	pShader->SetUniformMat4("mdm", combTrans);

	// draw the geometry
	pShader->SetUniformInt("useFixedColor", 1);
	// set the colour of the lines drawn in wire-frame mode to black
	pShader->SetUniformVec4("fixedColor", glm::vec4(0.0, 0.0, 0.0, 1.0));
	pGeometry->DrawLines();
	pShader->SetUniformInt("useFixedColor", 0);
	// set the colour of the lines drawn in wire-frame mode to black
	pShader->SetUniformVec4("fixedColor", cubeColor);

}


void CubeLab12::SetColor(const glm::vec4 &color)
{
	cubeColor = color;
	useColor = true;
}

void CubeLab12::SetTransform(const glm::mat4 &transform)
{ 
	modelTransform = transform; 
}

glm::mat4 CubeLab12::GetTransform()
{
	return modelTransform;
}

void CubeLab12::NullTransform()
{
	modelTransform = glm::mat4();
}

void CubeLab12::SetScale(const glm::vec3 &scale)
{
	modelTransform = glm::scale(modelTransform, scale);
}


void CubeLab12::SetTranslate(const glm::vec3 &trans)
{
	modelTransform = glm::translate(modelTransform, trans);
}
void CubeLab12::SetXRotation(float rot)
{
	modelTransform = glm::rotate(modelTransform, (float) glm::radians(rot), glm::vec3(1.0f, 0.0f, 0.0f));
}
void CubeLab12::SetYRotation(float rot)
{
	modelTransform = glm::rotate(modelTransform, (float)glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));
}
void CubeLab12::SetZRotation(float rot)
{
	modelTransform = glm::rotate(modelTransform, (float)glm::radians(rot), glm::vec3(0.0f, 0.0f, -1.0f));
}