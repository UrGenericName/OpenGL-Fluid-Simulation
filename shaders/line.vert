#version 430 core
layout (location = 0) in vec4 aPos;
layout (location = 1) in vec4 aColor;

out vec3 color;

uniform mat4 u_modelMatrix;
uniform mat4 u_camMatrix;

void main()
{
	gl_Position = u_camMatrix * u_modelMatrix * vec4(aPos.xyz, 1.0f);

	color = aColor.xyz;

}