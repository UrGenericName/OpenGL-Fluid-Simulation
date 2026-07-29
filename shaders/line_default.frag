#version 430 core

out vec4 FragColor;

in vec3 color;

uniform vec3 u_tint;

void main(){
	
	FragColor = vec4(u_tint, 1.0f);

}