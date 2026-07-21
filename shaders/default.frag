#version 430 core

out vec4 FragColor;

in vec3 color;
in vec3 intersectionPoint;

uniform vec3 u_camPos;

#define CAGE_ALPHA 0.2f

void main(){
	
	FragColor = vec4(1.0f, 1.0f, 1.0f, CAGE_ALPHA);

}