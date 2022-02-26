#version 330

uniform mat4 vpm;
uniform mat4 mdm;

uniform vec4 fixedColor;
uniform int useFixedColor = 0;

in vec3 vertexPos;
in vec4 vertexColor;

out vec4 fragColor;
out vec2 fragUV;

void main() {
    // Pass-through
	if (useFixedColor == 1)
		fragColor = fixedColor;
	else
		fragColor = vertexColor;
	// transform the vertex
    gl_Position = vpm * mdm * vec4(vertexPos, 1);
}
