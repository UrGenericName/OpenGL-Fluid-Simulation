#version 430 core

out vec4 FragColor;

in vec3 color;

uniform vec3 u_backgroundColor;

#define CAGE_ALPHA 0.2f

void main(){
	
	FragColor = vec4(1.0f, 1.0f, 1.0f, CAGE_ALPHA); 

}